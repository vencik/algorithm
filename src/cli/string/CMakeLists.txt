# Levenshtein distance etc
add_executable(levenshtein levenshtein.cxx)

target_link_libraries(levenshtein
    LINK_PUBLIC algorithm_string_levenshtein)
