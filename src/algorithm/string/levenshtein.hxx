#ifndef algorithm__string__levenshtein_hxx
#define algorithm__string__levenshtein_hxx

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

/**
 *  \brief  Levenshtein distance of strings
 *
 *  See https://en.wikipedia.org/wiki/Levenshtein_distance
 *
 *  \param  s1  A string
 *  \param  s2  Another string
 *
 *  \return Levenshtein distance of \c s1 from \c s2
 */
size_t levenshtein_dist(const std::string & s1, const std::string & s2);


/**
 *  \brief  Levenshtein distance based string similarity measure
 *
 *  Returns 1 - dist(\c s1, \c s2) / max(|\c s1|, |\c s2|)
 *  (where dist is Levenshtein distance of \c s1 from \c s2).
 *
 *  Note that the result is from interval [0, 1] as max. of L. distance
 *  is clearly max. of strings' lengths (as every string may be turned into
 *  another one by changing the overlapping characters and adding or deleting
 *  the rest of the missing or trailing ones, respectively).
 *  Also note that the max. of strings' lengths is (sometimes) a valid value
 *  of L. distance (e.g. dist("aaaaa", "bbb") == max(5, 3) == 5).
 *
 *  \param  s1  A string
 *  \param  s2  Another string
 *
 *  \return Reversed normalised Levenshtein distance of \c s1 from \c s2
 */
double levenshtein_simi(const std::string & s1, const std::string & s2);

}}  // end of namespaces string algorithm

#endif  // end of #ifndef algorithm__string__levenshtein_hxx
