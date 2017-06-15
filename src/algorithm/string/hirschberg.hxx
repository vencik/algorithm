#ifndef algorithm__string__hirschberg_hxx
#define algorithm__string__hirschberg_hxx

#include <string>
#include <tuple>
#include <memory>


namespace algorithm {
namespace string {

namespace impl {

template <typename T>
inline T max(T a) { return a; }

template <typename T, typename... Ts>
inline T max(T a1, Ts... args) {
    T max_args = max(args...);
    return a1 > max_args ? a1 : max_args;
}

};  // end of namespace impl


/**
 *  \brief  Hirschberg's algorithm
 *
 *  See https://en.wikipedia.org/wiki/Hirschberg's_algorithm
 *
 *  \tparam  Del  Deletion cost function type (char -> int)
 *  \tparam  Ins  Insertion cost function type (char -> int)
 *  \tparam  Sub  Substitution const function type (char, char -> int)
 */
template <class Del, class Ins, class Sub>
class hirschberg {
    private:

    mutable Del m_del;  /**< Deletion cost function     */
    mutable Ins m_ins;  /**< Insertion const function   */
    mutable Sub m_sub;  /**< Substitution cost function */

    public:

    /**
     *  \brief  Constructor
     *
     *  \param  del  Deletion cost function
     *  \param  ins  Insertion cost function
     *  \param  sub  Substitution cost function
     */
    hirschberg(Del del, Ins ins, Sub sub):
        m_del(del),
        m_ins(ins),
        m_sub(sub)
    {}

    typedef std::tuple<std::string, std::string> return_t;

    /**
     *  \brief  Implementation
     *
     *  \param  s1  A string
     *  \param  s2  Another string
     *
     *  \return String alignment
     */
    return_t operator () (
        const std::string & s1,
        const std::string & s2)
    const {
        const size_t s1_size = s1.size();
        const size_t s2_size = s2.size();

        // One of the strings is empty
        if (0 == s1_size) return return_t(std::string(s2_size, '-'), s2);
        if (0 == s2_size) return return_t(s1, std::string(s1_size, '-'));

        // Find string of length 1 (if any)
        const std::string * s_1 = NULL;
        const std::string * s_x;

        if (1 == s1_size) {
            s_1 = &s1;
            s_x = &s2;
        }
        else if (1 == s2_size) {
            s_1 = &s2;
            s_x = &s1;
        }

        // One of the strings has length 1
        if (NULL != s_1) {
            // Compute Needleman-Wunsch scores for |s_1| == 1
            const char   c_1             = s_1->at(0);
            const int    m_del_c_1       = m_del(c_1);
            const size_t s_x_size        = s_x->size();
            const size_t s_x_size_plus_1 = s_x_size + 1;
            std::unique_ptr<int> nw_scores(new int[2 * (s_x_size_plus_1)]);
            int * nw_scores_ptr = nw_scores.get();
            int * nw_score_0    = nw_scores_ptr + 0 * (s_x_size_plus_1);
            int * nw_score_1    = nw_scores_ptr + 1 * (s_x_size_plus_1);

            nw_score_0[0] = 0;
            nw_score_1[0] = 0 + m_del(m_del_c_1);
            for (size_t j = 0; j < s_x_size; ++j) {
                nw_score_0[j + 1] = nw_score_0[j] + m_ins(s_x->at(j));
                nw_score_1[j + 1] = impl::max(
                    nw_score_0[j]     + m_sub(c_1, s_x->at(j)),
                    nw_score_0[j + 1] + m_del_c_1,
                    nw_score_1[j]     + m_ins(s_x->at(j)));
            }

            // Compute Needleman-Wunsch aligment for |s_1| == 1
            std::string r1; r1.reserve(s_x_size);
            std::string r2; r2.reserve(s_x_size);

            for (size_t i = 1, j = s_x_size; i | j; ) {
                if (i) {
                    int nw_score;

                    if (j) {
                        nw_score = nw_score_0[j - 1] +
                            m_sub(c_1, s_x->at(j - 1));

                        // Substitution
                        if (nw_score_1[j] == nw_score) {
                            r1.push_back(c_1);
                            r2.push_back(s_x->at(j - 1));
                            --i;
                            --j;
                            continue;
                        }
                    }

                    nw_score = nw_score_0[j] + m_del_c_1;

                    // Deletion
                    if (nw_score_1[j] == nw_score) {
                        r1.push_back(c_1);
                        r2.push_back('-');
                        --i;
                        continue;
                    }
                }

                // Insertion
                r1.push_back('-');
                r2.push_back(s_x->at(j - 1));
                --j;
            }

            // Reverse output
            for (size_t j = 0, k = r1.size() - 1; j < k; ++j, --k) {
                auto c = r1[j];
                r1[j] = r1[k];
                r1[k] = c;
                c = r2[j];
                r2[j] = r2[k];
                r2[k] = c;
            }

            return 1 == s1_size ? return_t(r1, r2) : return_t(r2, r1);
        }

        // Compute Needleman-Wunsch scores
        size_t s1_div = s1_size / 2;

        // Needleman-Wunsch score matrices' last 2 rows (for each side of s1)
        const size_t s2_size_plus_1  = s2_size + 1;
        const size_t s2_size_minus_1 = s2_size - 1;
        std::unique_ptr<int> nw_score_buffer(new int[4 * (s2_size_plus_1)]);
        int * nw_score_ptr = nw_score_buffer.get();
        int * nw_score_a   = nw_score_ptr + 0 * s2_size_plus_1;
        int * nw_score_b   = nw_score_ptr + 1 * s2_size_plus_1;
        int * nw_score_x   = nw_score_ptr + 2 * s2_size_plus_1;
        int * nw_score_y   = nw_score_ptr + 3 * s2_size_plus_1;

        // Initialise 1st rows
        nw_score_a[0] = 0;
        for (size_t j = 0; j < s2_size; ++j)
            nw_score_a[j + 1] = nw_score_a[j] + m_ins(s2[j]);

        nw_score_x[0] = 0;
        for (size_t j = 1; j <= s2_size; ++j)
            nw_score_x[j] = nw_score_x[j - 1] + m_ins(s2[s2_size - j]);

        // Compute the matrices' other rows (keeping only the last 2 at a time)
        for (size_t i = 0, k = s1_size - 1; i < s1_div; ++i, --k) {
            nw_score_b[0] = nw_score_a[0] + m_del(s1[i]);
            nw_score_y[0] = nw_score_x[0] + m_del(s1[k]);

            for (size_t j = 0, l = s2_size_minus_1; j < s2_size; ++j, --l) {
                nw_score_b[j + 1] = impl::max(
                    nw_score_a[j]     + m_sub(s1[i], s2[j]),
                    nw_score_a[j + 1] + m_del(s1[i]),
                    nw_score_b[j]     + m_ins(s2[j]));

                nw_score_y[j + 1] = impl::max(
                    nw_score_x[j]     + m_sub(s1[k], s2[l]),
                    nw_score_x[j + 1] + m_del(s1[k]),
                    nw_score_y[j]     + m_ins(s2[l]));
            }

            // Swap Needleman-Wunsch score matrices' last 2 rows
            auto nw_score_t = nw_score_a;
            nw_score_a = nw_score_b;
            nw_score_b = nw_score_t;
            nw_score_t = nw_score_x;
            nw_score_x = nw_score_y;
            nw_score_y = nw_score_t;
        }

        // In case of odd s1 size, we must add one more iteration (right)
        if (s1_size % 2) {
            for (size_t j = 0, l = s2_size_minus_1; j < s2_size; ++j, --l)
                nw_score_y[j + 1] = impl::max(
                    nw_score_x[j]     + m_sub(s1[s1_div], s2[l]),
                    nw_score_x[j + 1] + m_del(s1[s1_div]),
                    nw_score_y[j]     + m_ins(s2[l]));

            // Final swap (no need to access the prev. row any longer)
            nw_score_x = nw_score_y;
        }

        // Get (locally) optimal s2 division
        size_t s2_div = 0;
        for (size_t j = 0, l = s2_size; j <= s2_size; ++j, --l) {
            nw_score_b[j] = nw_score_a[j] + nw_score_x[l];

            if (nw_score_b[j] > nw_score_b[s2_div]) s2_div = j;
        }

        // Divide and conquer
        auto left  = (*this)(s1.substr(0, s1_div),  s2.substr(0, s2_div));
        auto right = (*this)(s1.substr(s1_div),     s2.substr(s2_div));

        return return_t(
            std::get<0>(left) + std::get<0>(right),
            std::get<1>(left) + std::get<1>(right));
    }

};  // end of template class hirschberg

}}  // end of namespaces string algorithm

#endif  // end of #ifndef algorithm__string__hirschberg_hxx
