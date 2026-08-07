#include "export.h"
#include "extension.h"
#include "gdextension_interface.h"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/godot.hpp"

auto initialize_extension(godot::ModuleInitializationLevel level) -> void {
    if (level != godot::MODULE_INITIALIZATION_LEVEL_SCENE)
        return;

    GDREGISTER_CLASS(godot::AudioMetadataExtension);
}

auto uninitialize_extension(godot::ModuleInitializationLevel level) -> void {
    if (level != godot::MODULE_INITIALIZATION_LEVEL_SCENE)
        return;
}

auto EXPORT initialize_library(
    ::GDExtensionInterfaceGetProcAddress p_get_proc_address,
    const ::GDExtensionClassLibraryPtr p_library,
    ::GDExtensionInitialization *r_initialization) -> ::GDExtensionBool {

    godot::GDExtensionBinding::InitObject obj{p_get_proc_address, p_library,
                                              r_initialization};
    obj.register_initializer(initialize_extension);
    obj.register_terminator(uninitialize_extension);
    obj.set_minimum_library_initialization_level(
        godot::MODULE_INITIALIZATION_LEVEL_SCENE);

    return obj.init();
}
