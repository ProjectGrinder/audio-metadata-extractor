#pragma once

#if defined(_MSC_VER)
#define EXPORT __declspec(dllexport)
#define IMPORT __declspec(dllimport)
#elif defined(__GNUC__) || defined(__clang__)
#define EXPORT __attribute__((visibility("default")))
#define IMPORT
#else
#define EXPORT
#define IMPORT
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
#if defined(AUDIO_METADATA_BUILD_DLL)
#define AUDIO_API EXPORT
#elif defined(AUDIO_METADATA_STATIC)
#define AUDIO_API
#else
#define AUDIO_API IMPORT
#endif
#else
#define AUDIO_API EXPORT
#endif

#ifdef __cplusplus
#include <cstdint>
extern "C" {
#else
#include <stdbool.h>
#include <stdint.h>
#endif

typedef struct AudioProperties {
    double duration;
    int32_t bitrate;
    int32_t sample_rate;
    int32_t channels;
} AudioProperties;

typedef struct ImageData {
    uint8_t *image_data;
    char *mime;
    uint32_t image_size;
    uint32_t mime_size;
} ImageData;

typedef void (*MetadataCallback)(const char *key, const char *value,
                                 void *user_data);

AUDIO_API void extract_metadata(const char *byte, uint32_t size,
                                MetadataCallback callback, void *user_data);

AUDIO_API AudioProperties extract_audio_properties(const char *byte,
                                                   uint32_t size);

AUDIO_API ImageData extract_image(const char *byte, uint32_t size);

AUDIO_API void free_image(ImageData *image);

#ifdef __cplusplus
}
#endif
