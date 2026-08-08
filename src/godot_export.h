#include "gdextension_interface.h"
#include "godot_cpp/godot.hpp"

#if defined(_MSC_VER)
#define EXPORT __declspec(dllexport)
#define IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
#define EXPORT __attribute__((visibility("default")))
#define IMPORT
#else
#define EXPORT
#define IMPORT
#pragma warning Unknown dynamic link import / export semantics.

#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus

auto EXPORT initialize_library(::GDExtensionInterfaceGetProcAddress,
                               const ::GDExtensionClassLibraryPtr,
                               ::GDExtensionInitialization *)
    -> ::GDExtensionBool;
#else
GDExtensionBool EXPORT initialize_library(GDExtensionInterfaceGetProcAddress,
                                          const GDExtensionClassLibraryPtr,
                                          GDExtensionInitialization *);
#endif
#ifdef __cplusplus
}
#endif
