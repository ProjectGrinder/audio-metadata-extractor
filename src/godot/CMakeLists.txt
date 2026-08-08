add_library(audio_metadata_extension-godot
    SHARED
    godot_export.cpp
    godot_export.h
    godot_extension.h
    godot_extension.cpp
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

set_target_properties(audio_metadata_extension-godot PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/godot"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/godot"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/godot"
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
