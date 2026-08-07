#include "extract_metadata.h"
#include "fileref.h"
#include "tbytevector.h"
#include "tbytevectorstream.h"

namespace Extension {
auto extract_metadata(const char *byte, uint32_t size) -> TagLib::PropertyMap {
    if (!byte || size == 0)
        return {};

    TagLib::ByteVector vec{byte, size};
    TagLib::ByteVectorStream stream{vec};
    TagLib::FileRef fr{&stream};

    if (fr.isNull())
        return {};

    return fr.properties();
}
} // namespace Extension
