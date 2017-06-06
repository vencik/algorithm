# Levenshtein distance etc
add_library(algorithm_string_levenshtein levenshtein.cxx)

target_include_directories(algorithm_string_levenshtein
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../..")
