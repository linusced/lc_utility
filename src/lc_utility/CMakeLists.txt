set(FILES
    binary_file.cpp key_value_file.cpp filesystem.cpp)

add_library(lc_utility STATIC ${FILES})
target_include_directories(lc_utility PUBLIC include/)
