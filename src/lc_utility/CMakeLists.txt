set(FILES
    binary_file.cpp key_value_file.cpp get_file_paths.cpp file_path.cpp)

add_library(lc_utility STATIC ${FILES})
target_include_directories(lc_utility PUBLIC include/)
