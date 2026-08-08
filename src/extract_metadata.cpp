#include "extract_metadata.h"
#include "fileref.h"
#include "tbytevector.h"
#include "tbytevectorstream.h"
#include "tpropertymap.h"

namespace Extension {
auto extract_metadata(const char *byte, uint32_t size) -> TagLib::PropertyMap {
    if (!byte || size == 0)
        return {};

    TagLib::ByteVector vec{byte, size};
    TagLib::ByteVectorStream stream{vec};
    TagLib::FileRef fr{&stream};

    if (fr.isNull() || !fr.file())
        return {};

    return fr.properties();
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

    return {map["data"].toByteVector(), map.contains("mimeType")
                                            ? map["mimeType"].toString()
                                            : TagLib::String("image/jpeg")};
}
} // namespace Extension
