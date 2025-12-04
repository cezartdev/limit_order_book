add_library(generate_data STATIC
    generate_data.cpp
    generate_data.hpp
)

target_include_directories(generate_data
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(generate_data
    PUBLIC
        cxx_std_20
)