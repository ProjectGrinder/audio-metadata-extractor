#pragma once
#include <cstdint>

#include "tpropertymap.h"
#include "tstring.h"

namespace Extension {

struct ImageData {
    TagLib::ByteVector data;
    TagLib::String mime;
};

struct AudioProperties {
    double duration;
    int bitrate;
    int sample_rate;
    int channels;
};

auto extract_metadata(const char *byte, uint32_t size) -> TagLib::PropertyMap;
auto extract_audio_properties(const char *byte, uint32_t size)
    -> AudioProperties;
auto extract_image(const char *byte, uint32_t size) -> ImageData;
} // namespace Extension
