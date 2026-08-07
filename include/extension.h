#pragma once

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>

#if defined(_MSC_VER) || defined(__clang__)
#pragma pointers_to_members(full_generality, virtual_inheritance)
#endif

#ifdef __cplusplus
namespace godot {
class AudioMetadataExtension : public RefCounted {
    GDCLASS(AudioMetadataExtension, RefCounted);

  protected:
    static auto _bind_methods() -> void;

  public:
    AudioMetadataExtension();
    ~AudioMetadataExtension();

    auto extract_metadata(const PackedByteArray &buffer) -> Dictionary;
};
} // namespace godot
#endif
