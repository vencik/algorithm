#include "algorithm/string/levenshtein.hxx"

#include <iostream>
#include <stdexcept>


/** CLI wrapper */
static int main_impl(int argc, char * const argv[]) {
    if (argc != 4) {
        std::cerr
            << "Usage: " << argv[0] << " {dist|simi} <string> <another string>"
            << std::endl;

        return 1;
    }

    const std::string what(argv[1]);

    // Levenshtein distance
    if ("dist" == what) {
        std::cout
            << algorithm::string::levenshtein_dist(argv[2], argv[3])
            << std::endl;
    }

    // Levenshtein similarity
    else if ("simi" == what) {
        std::cout
            << algorithm::string::levenshtein_simi(argv[2], argv[3])
            << std::endl;
    }

    // Unsupported computation
    else {
        std::cerr
            << "Unsupported computation: " << what
            << std::endl;

        return 2;
    }

    return 0;
}


/** Exception-safe wrapper */
int main(int argc, char * const argv[]) {
    int exit_code = 127;

    try {
        exit_code = main_impl(argc, argv);
    }
    catch (const std::exception & x) {
        std::cerr
            << "Standard exception caught: "
            << x.what()
            << std::endl;
    }
    catch (...) {
        std::cerr
            << "Unhandled non-standard exception caught"
            << std::endl;
    }

    return exit_code;
}
