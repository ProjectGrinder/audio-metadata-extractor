#include "extractor.h"
#include "fileref.h"
#include "tbytevector.h"
#include "tbytevectorstream.h"
#include "tpropertymap.h"
#include <unordered_map>

namespace Extension {
auto extract_metadata(const char *byte, uint32_t size)
    -> std::unordered_map<std::string, std::string> {
    if (!byte || size == 0)
        return {};

    TagLib::ByteVector vec{byte, size};
    TagLib::ByteVectorStream stream{vec};
    TagLib::FileRef fr{&stream};

    if (fr.isNull() || !fr.file())
        return {};

    std::unordered_map<std::string, std::string> result{};

    for (const auto &[k, v] : fr.properties())
        result.insert({k.toCString(true), v.toString(", ").toCString(true)});

    return std::move(result);
}

auto extract_audio_properties(const char *byte, uint32_t size)
    -> AudioProperties {
    if (!byte || size == 0)
        return {};

    TagLib::ByteVector vec{byte, size};
    TagLib::ByteVectorStream stream{vec};
    TagLib::FileRef fr{&stream};

    if (fr.isNull() || !fr.file())
        return {};

    auto properties = fr.audioProperties();

    if (!properties)
        return {};

    return {
        properties->lengthInMilliseconds() / 1000.0,
        properties->bitrate(),
        properties->sampleRate(),
        properties->channels(),
    };
}

auto extract_image(const char *byte, uint32_t size) -> ImageData {
    if (!byte || size == 0)
        return {};

    TagLib::ByteVector vec{byte, size};
    TagLib::ByteVectorStream stream{vec};
    TagLib::FileRef fr{&stream};

    if (fr.isNull() || !fr.file())
        return {};

    auto pics = fr.complexProperties("PICTURE");
    if (pics.isEmpty())
        return {};

    auto map = pics.front();
    if (!map.contains("data"))
        return {};

    auto bv = map["data"].toByteVector();
    std::vector<uint8_t> bytes(bv.data(), bv.data() + bv.size());
    std::string mime = map.contains("mimeType")
                           ? map["mimeType"].toString().toCString(true)
                           : "image/jpeg";

    return {std::move(bytes), std::move(mime)};
}
} // namespace Extension
