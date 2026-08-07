#pragma once
#include <cstdint>

#include "tpropertymap.h"

namespace Extension {
auto extract_metadata(const char *byte, uint32_t size) -> TagLib::PropertyMap;
} // namespace Extension
