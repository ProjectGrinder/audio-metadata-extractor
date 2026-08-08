#ifdef __cplusplus
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace Extension {
struct ImageData {
    std::vector<uint8_t> data;
    std::string mime;
};

struct AudioProperties {
    double duration;
    int32_t bitrate;
    int32_t sample_rate;
    int32_t channels;
};

auto extract_metadata(const char *byte, uint32_t size)
    -> std::unordered_map<std::string, std::string>;
auto extract_audio_properties(const char *byte, uint32_t size)
    -> AudioProperties;
auto extract_image(const char *byte, uint32_t size) -> ImageData;
} // namespace Extension
#endif
