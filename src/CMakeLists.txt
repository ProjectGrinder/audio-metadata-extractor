add_library(audio_metadata_extension
    STATIC
    extractor.h
    extractor.cpp
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

add_subdirectory(godot)
add_subdirectory(native)
