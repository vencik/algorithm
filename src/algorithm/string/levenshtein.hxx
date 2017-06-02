#ifndef algorithm__string__levenshtein_hxx
#define algorithm__string__levenshtein_hxx

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
