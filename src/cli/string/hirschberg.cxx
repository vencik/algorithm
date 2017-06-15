/**
 *  \file
 *  \brief  Hirschberg's string alignment: CLI
 *
 *  \date   2017/06/15
 *  \author Vaclav Krpec  <vencik@razdva.cz>
 *
 *
 *  LEGAL NOTICE
 *
 *  Copyright (c) 2017, Vaclav Krpec
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the distribution.
 *
 *  3. Neither the name of the copyright holder nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER
 *  OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include "algorithm/string/hirschberg.hxx"

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <climits>


/** Convert cmd. line argument to integer */
static int arg2int(const char * arg) {
    static char inv_arg[] = "Invalid argument: syntax error at 'X'";
    static constexpr size_t inv_arg_pos = sizeof(inv_arg) / sizeof(char) - 3;

    char * err;
    long i = strtol(arg, &err, 10);
    if ('\0' != *err) {
        inv_arg[inv_arg_pos] = *err;
        throw std::runtime_error(inv_arg);
    }

    if (!(INT_MIN <= i && i <= INT_MAX))
        throw std::runtime_error(
            "Invalid argument: (absolute) value too great");

    return i;
}


/** CLI wrapper */
static int main_impl(int argc, char * const argv[]) {
    int del_cost = -2;  // Cost of deletion
    int ins_cost = -2;  // Cost of insertion
    int sub_cost = -1;  // Cost of substitution
    int eql_cost =  2;  // Cost of character match

    if (!(argc < 6 || 7 == argc)) {
        std::cerr
            << "Usage: " << argv[0] << " [del] [ins] [sub] [eql] "
               "[string1 string2]"
            << std::endl
            << std::endl
            << "Hirschberg's strings alignment computation."
            << std::endl
            << std::endl
            << "The del (" << del_cost << "), ins (" << ins_cost << "), "
               "sub (" << sub_cost << ") and eql (" << eql_cost << ")"
            << std::endl
            << "parameters are the costs of deletion, insertion, substitution"
            << std::endl
            << "and equality of characters, respectively (defaults shown)."
            << std::endl
            << "Negative number means penalisation, match should be positive."
            << std::endl
            << std::endl
            << "If the strings are specified via cmd. line arguments,"
            << std::endl
            << "the process will print their alignment."
            << std::endl
            << "Otherwise, it expects the strings on its std. input"
            << std::endl
            << "(one per each line) and prints the result per each 2 lines."
            << std::endl
            << std::endl;

        return 1;
    }

    // Read character operation costs
    if (argc > 1) del_cost = arg2int(argv[1]);
    if (argc > 2) ins_cost = arg2int(argv[2]);
    if (argc > 3) sub_cost = arg2int(argv[3]);
    if (argc > 4) eql_cost = arg2int(argv[4]);

    // Instantiate Hirschberg's algorithm
    auto del = [del_cost](char c) -> int { return del_cost; };
    auto ins = [ins_cost](char c) -> int { return ins_cost; };
    auto sub = [sub_cost, eql_cost](char a, char b) -> int {
        return a == b ? eql_cost : sub_cost;
    };

    algorithm::string::hirschberg<
        decltype(del), decltype(ins), decltype(sub)>
            hirschberg(del, ins, sub);

    // Strings passed as cmd. line arguments
    if (7 == argc) {
        auto align = hirschberg(argv[5], argv[6]);

        std::cout
            << std::get<0>(align) << std::endl
            << std::get<1>(align) << std::endl;

        return 0;
    }

    // Strings from input
    for (std::string arg1, arg2; ;) {
        if (std::getline(std::cin, arg1).eof()) break;
        if (std::getline(std::cin, arg2).eof()) break;

        auto align = hirschberg(arg1, arg2);

        std::cout
            << std::get<0>(align) << std::endl
            << std::get<1>(align) << std::endl;
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
