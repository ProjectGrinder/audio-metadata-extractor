#include "extension.h"
#include "extract_metadata.h"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/variant/string.hpp"
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>

namespace godot {
auto AudioMetadataExtension::_bind_methods() -> void {
    ClassDB::bind_method(D_METHOD("extract_metadata", "buffer"),
                         &AudioMetadataExtension::extract_metadata);
}

AudioMetadataExtension::AudioMetadataExtension() {}
AudioMetadataExtension::~AudioMetadataExtension() {}

auto AudioMetadataExtension::extract_metadata(const PackedByteArray &buffer)
    -> Dictionary {

    auto properties = Extension::extract_metadata(
        reinterpret_cast<const char *>(buffer.ptr()), buffer.size());

    Dictionary result = {};
    for (const auto &[k, v] : properties) {
        String info{k.toCString(true)};
        String value{v.toString(", ").toCString(true)};

        result.set(info, value);
    }

    return result;
}
} // namespace godot
