cmake_minimum_required(VERSION 3.20)
project(audio-library)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(external)
add_subdirectory(src)

add_custom_target(
    copy-compile-commands ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_CURRENT_LIST_DIR}
)

add_custom_target(
    godot-binding ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/bin/godot
        ${PROJECT_SOURCE_DIR}/binding/godot/addons/audio_metadata_extension/bin
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${PROJECT_SOURCE_DIR}/LICENSE.md
        ${PROJECT_SOURCE_DIR}/binding/godot/addons/audio_metadata_extension/LICENSE.md
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${PROJECT_SOURCE_DIR}/README.md
        ${PROJECT_SOURCE_DIR}/binding/godot/addons/audio_metadata_extension/README.md
)
add_dependencies(godot-binding audio_metadata_extension-godot)

add_custom_target(
    native-binding ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/bin/native
        ${PROJECT_SOURCE_DIR}/binding/native/bin
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${PROJECT_SOURCE_DIR}/include/audio_metadata_extension.h
        ${PROJECT_SOURCE_DIR}/binding/native/include/audio_metadata_extension.h
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${PROJECT_SOURCE_DIR}/LICENSE.md
        ${PROJECT_SOURCE_DIR}/binding/native/LICENSE.md
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${PROJECT_SOURCE_DIR}/README.md
        ${PROJECT_SOURCE_DIR}/binding/native/README.md
)
add_dependencies(native-binding audio_metadata_extension-native)

add_custom_target(
    unity-binding ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/bin/native
        ${PROJECT_SOURCE_DIR}/binding/unity/Runtime/Plugins
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${PROJECT_SOURCE_DIR}/LICENSE.md
        ${PROJECT_SOURCE_DIR}/binding/unity/LICENSE.md
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${PROJECT_SOURCE_DIR}/README.md
        ${PROJECT_SOURCE_DIR}/binding/unity/README.md
)
add_dependencies(unity-binding audio_metadata_extension-native)
