add_library(audio_metadata_extension
    STATIC
    extract_metadata.cpp
    extract_metadata.h
)

set_target_properties(audio_metadata_extension PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

target_link_libraries(audio_metadata_extension
    PRIVATE
    tag
)

target_include_directories(audio_metadata_extension
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/external/taglib
        ${PROJECT_SOURCE_DIR}/external/taglib/taglib
        ${PROJECT_SOURCE_DIR}/external/taglib/taglib/toolkit
        ${PROJECT_BINARY_DIR}/external/taglib
        ${PROJECT_BINARY_DIR}/external/taglib/taglib
)

add_library(audio_metadata_extension-godot
    SHARED
    godot_export.cpp
    godot_export.h
    extension.cpp
)

target_link_libraries(audio_metadata_extension-godot
    PRIVATE
    godot-cpp
    audio_metadata_extension
)

target_include_directories(audio_metadata_extension-godot PRIVATE
    ${PROJECT_SOURCE_DIR}/external/godot-cpp/include
    ${PROJECT_SOURCE_DIR}/external/godot-cpp/gen/include
    ${PROJECT_SOURCE_DIR}/external/godot-cpp/gdextension
)

if(WIN32)
    set_target_properties(audio_metadata_extension-godot PROPERTIES
        OUTPUT_NAME "audio_metadata_extension-godot.windows.x86_64"
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    if(CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
        set_target_properties(audio_metadata_extension-godot PROPERTIES
            OUTPUT_NAME "audio_metadata_extension-godot.linux.arm64"
        )
    else()
        set_target_properties(audio_metadata_extension-godot PROPERTIES
            OUTPUT_NAME "audio_metadata_extension-godot.linux.x86_64"
        )
    endif()
elseif(APPLE)
    set_target_properties(audio_metadata_extension-godot PROPERTIES
        OUTPUT_NAME "audio_metadata_extension-godot.macos"
    )
endif()
