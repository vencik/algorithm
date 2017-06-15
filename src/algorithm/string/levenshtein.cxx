/**
 *  \file
 *  \brief  Levenshtein distance (and its derivatives)
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


#include <string>


namespace algorithm {
namespace string {

namespace impl {

template <typename T>
inline T min(T a) { return a; }

template <typename T, typename... Ts>
inline T min(T a1, Ts... args) {
    T min_args = min(args...);
    return a1 < min_args ? a1 : min_args;
}

}  // end of namespace impl


size_t levenshtein_dist(const std::string & s1, const std::string & s2) {
    const size_t s1_size = s1.size();
    const size_t s2_size = s2.size();

    // Corner cases
    if (0  == s1_size) return s2_size;
    if (0  == s2_size) return s1_size;
    if (s1 == s2)      return 0;

    // Last 2 dist. matrix rows
    size_t   ra[s2_size + 1];
    size_t   rb[s2_size + 1];
    size_t * r0 = ra;
    size_t * r1 = rb;

    // Initialize r0 (the previous row of distances)
    // by edit distance for empty s1 (i.e. length of s2 prefix)
    for (size_t i = 0; i < s2_size + 1; i++)
        r0[i] = i;

    // Calculate next row r1 (done at least once)
    for (size_t i = 0; i < s1_size; i++) {
        r1[0] = i + 1;  // delete i + 1 chars to match empty string

        // Rest of the row
        for (size_t j = 0; j < s2_size; j++)
            r1[j + 1] = impl::min(
                r1[j] + 1,
                r0[j + 1] + 1,
                r0[j] + (s1[i] == s2[j] ? 0 : 1));

        // Swap rows for next iteration
        size_t * rs = r0;
        r0 = r1;
        r1 = rs;
    }

    return r0[s2_size];
}


double levenshtein_simi(const std::string & s1, const std::string & s2) {
    const size_t dist = levenshtein_dist(s1, s2);
    if (0 == dist) return 1.0;  // identical strings

    const size_t smax = -impl::min(-(long)s1.size(), -(long)s2.size());
    return 1.0 - (double)dist / smax;  // note that surely, smax > 0
}

}}  // end of namespaces string algorithm
