#include "godot_extension.h"
#include "../extractor.h"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/variant/string.hpp"
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>

namespace godot {
auto AudioMetadataExtension::_bind_methods() -> void {
    ClassDB::bind_static_method("AudioMetadataExtension",
                                D_METHOD("extract_metadata", "buffer"),
                                &AudioMetadataExtension::extract_metadata);

    ClassDB::bind_static_method(
        "AudioMetadataExtension",
        D_METHOD("extract_audio_properties", "buffer"),
        &AudioMetadataExtension::extract_audio_properties);

    ClassDB::bind_static_method("AudioMetadataExtension",
                                D_METHOD("extract_image", "buffer"),
                                &AudioMetadataExtension::extract_image);
}

AudioMetadataExtension::AudioMetadataExtension() {}
AudioMetadataExtension::~AudioMetadataExtension() {}

auto AudioMetadataExtension::extract_metadata(const PackedByteArray &buffer)
    -> Dictionary {
    auto res = Extension::extract_metadata(
        reinterpret_cast<const char *>(buffer.ptr()), buffer.size());

    Dictionary dict = {};
    for (const auto &[k, v] : res) {
        auto info = String::utf8(k.c_str());
        auto value = String::utf8(v.c_str());

        dict.set(info, value);
    }

    return dict;
}

auto AudioMetadataExtension::extract_audio_properties(
    const PackedByteArray &buffer) -> Dictionary {
    auto res = Extension::extract_audio_properties(
        reinterpret_cast<const char *>(buffer.ptr()), buffer.size());

    Dictionary dict{};
    dict["DURATION"] = res.duration;
    dict["BITRATE"] = res.bitrate;
    dict["SAMPLE_RATE"] = res.sample_rate;
    dict["CHANNELS"] = res.channels;
    return dict;
}

auto AudioMetadataExtension::extract_image(const PackedByteArray &buffer)
    -> Dictionary {
    auto res = Extension::extract_image(
        reinterpret_cast<const char *>(buffer.ptr()), buffer.size());

    if (res.data.empty())
        return {};

    Dictionary dict{};
    PackedByteArray cover_bytes{};
    cover_bytes.resize(res.data.size());
    memcpy(cover_bytes.ptrw(), res.data.data(), res.data.size());

    dict["IMAGE_DATA"] = cover_bytes;
    dict["MIME"] = String::utf8(res.mime.c_str());
    return dict;
}
} // namespace godot
