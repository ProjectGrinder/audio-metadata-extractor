add_library(audio_metadata_extension-native
    SHARED
    native_export.cpp
)

target_link_libraries(audio_metadata_extension-native
    PRIVATE
    audio_metadata_extension
)

target_compile_definitions(audio_metadata_extension-native
    PRIVATE
        AUDIO_METADATA_BUILD_DLL
)

if(WIN32)
    set_target_properties(audio_metadata_extension-native PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/native/Windows/x86_64"
        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/native/Windows/x86_64"
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/native/Windows/x86_64"
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    if(CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
        set_target_properties(audio_metadata_extension-native PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/native/Linux/arm64"
            LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/native/Linux/arm64"
            RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/native/Linux/arm64"
        )
    else()
        set_target_properties(audio_metadata_extension-native PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/native/Linux/x86_64"
            LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/native/Linux/x86_64"
            RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/native/Linux/x86_64"
        )
    endif()
elseif(APPLE)
    set_target_properties(audio_metadata_extension-native PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/native/macOS"
        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/native/macOS"
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/native/macOS"
    )
endif()

set_target_properties(audio_metadata_extension-native PROPERTIES
    OUTPUT_NAME "audio_metadata_extension-native"
)
