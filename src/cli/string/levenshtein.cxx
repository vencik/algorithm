#include "algorithm/string/levenshtein.hxx"

#include <iostream>
#include <stdexcept>


/** Computation implementation */
class computer {
    public:

    virtual void operator () (
        std::ostream      & out,
        const std::string & s1,
        const std::string & s2)
    const = 0;

};  // end of class computer


/** Levenshtein distance computer */
class levenshtein_dist: public computer {
    public:

    void operator () (
        std::ostream      & out,
        const std::string & s1,
        const std::string & s2)
    const {
        out << algorithm::string::levenshtein_dist(s1, s2);
    }

};  // end of class levenshtein_dist_computer


/** Levenshtein similarity computer */
class levenshtein_simi: public computer {
    public:

    void operator () (
        std::ostream      & out,
        const std::string & s1,
        const std::string & s2)
    const {
        out << algorithm::string::levenshtein_simi(s1, s2);
    }

};  // end of class levenshtein_dist_computer


/**
 *  \brief  Computer resolver
 *
 *  Throws an exception if computer identification is faulty
 *
 *  \param  cid  Computer identification ("dist" | "simi")
 *
 *  \return Computer
 */
static const computer & resolve_computer(const std::string & cid) {
    static const levenshtein_dist dist;
    static const levenshtein_simi simi;

    if ("dist" == cid) return dist;
    if ("simi" == cid) return simi;

    throw std::runtime_error("Unsupported computation requested");
}


/** CLI wrapper */
static int main_impl(int argc, char * const argv[]) {
    if (!(2 == argc || 4 == argc)) {
        std::cerr
            << "Usage: " << argv[0] << " {dist|simi} [<string_1> <string_2>]"
            << std::endl
            << std::endl
            << "If the strings are specified via cmd. line arguments,"
            << std::endl
            << "the process will print their Levenshtein distance and finish."
            << std::endl
            << "If omitted, the process expects the strings on input"
            << std::endl
            << "(one per each line) and prints the dist. per each 2 lines."
            << std::endl
            << std::endl;

        return 1;
    }

    const computer & comp = resolve_computer(argv[1]);

    // Computation arguments passed as cmd. line arguments
    if (4 == argc) {
        comp(std::cout, argv[2], argv[3]);
        std::cout << std::endl;

        return 0;
    }

    // Computation arguments from input
    for (std::string arg1, arg2; ;) {
        if (std::getline(std::cin, arg1).eof()) break;
        if (std::getline(std::cin, arg2).eof()) break;

        comp(std::cout, arg1, arg2);
        std::cout << std::endl;
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
