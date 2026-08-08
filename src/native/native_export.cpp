#include "../extractor.h"
#include "audio_metadata_extension.h"
#include <cstring>
extern "C" {
void extract_metadata(const char *byte, uint32_t size,
                      MetadataCallback callback, void *user_data) {
    if (!byte || size == 0 || !callback)
        return;

    auto map = Extension::extract_metadata(byte, size);
    for (const auto &[key, val] : map) {
        callback(key.c_str(), val.c_str(), user_data);
    }
}

AudioProperties extract_audio_properties(const char *byte, uint32_t size) {
    auto props = Extension::extract_audio_properties(byte, size);
    return {props.duration, props.bitrate, props.sample_rate, props.channels};
}

ImageData extract_image(const char *byte, uint32_t size) {
    auto img = Extension::extract_image(byte, size);
    if (img.data.empty())
        return {};

    ImageData result{};
    result.image_size = static_cast<uint32_t>(img.data.size());
    result.image_data = new uint8_t[result.image_size];
    std::memcpy(result.image_data, img.data.data(), result.image_size);

    result.mime_size = static_cast<uint32_t>(img.mime.size());
    result.mime = new char[result.mime_size + 1];
    std::memcpy(result.mime, img.mime.c_str(), result.mime_size + 1);

    return result;
}

void free_image(ImageData *image) {
    if (!image)
        return;
    delete[] image->image_data;
    delete[] image->mime;
    image->image_data = nullptr;
    image->mime = nullptr;
    image->image_size = 0;
    image->mime_size = 0;
}
}
