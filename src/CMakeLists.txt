file(GLOB_RECURSE MAIN_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_library(audio_metadata_extension
    SHARED
    ${MAIN_FILES}
)

target_link_libraries(audio_metadata_extension
    PRIVATE
    godot-cpp
    tag
)

target_include_directories(audio_metadata_extension PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/external/taglib
    ${PROJECT_SOURCE_DIR}/external/taglib/taglib
    ${PROJECT_SOURCE_DIR}/external/taglib/taglib/toolkit
    ${PROJECT_BINARY_DIR}/external/taglib
    ${PROJECT_BINARY_DIR}/external/taglib/taglib
    ${PROJECT_SOURCE_DIR}/external/godot-cpp/include
    ${PROJECT_SOURCE_DIR}/external/godot-cpp/gen/include
    ${PROJECT_SOURCE_DIR}/external/godot-cpp/gdextension
)

if(WIN32)
    set_target_properties(audio_metadata_extension PROPERTIES
        OUTPUT_NAME "audio_metadata_extension.windows.x86_64"
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    if(CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
        set_target_properties(audio_metadata_extension PROPERTIES
            OUTPUT_NAME "audio_metadata_extension.linux.arm64"
        )
    else()
        set_target_properties(audio_metadata_extension PROPERTIES
            OUTPUT_NAME "audio_metadata_extension.linux.x86_64"
        )
    endif()
elseif(APPLE)
    set_target_properties(audio_metadata_extension PROPERTIES
        OUTPUT_NAME "audio_metadata_extension.macos"
    )
endif()
