# Levenshtein distance etc
add_test(
    NAME    Levenshtein
    COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/levenshtein.sh"
        "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}")


# Hirschberg's string alignment algorithm
add_test(
    NAME    Hirschberg
    COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/hirschberg.sh"
        "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}")
