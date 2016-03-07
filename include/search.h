#ifndef _COMPACT_H_
#define _COMPACT_H_

//
// Function prototypes.
//

// Compare (std::bsearch dependency)
template <typename T>
int compare(T, T);

// Wrapper to std::bsearch
template <typename T1, typename T2>
int wrapper_std_bsearch(T1, T2, int, int);

template <typename T1, typename T2>
int seq_search_r(T1, T2, int, int);

template <typename T1, typename T2>
int seq_search_i(T1, T2, int, int);

template <typename T1, typename T2>
int binary_search_r(T1, T2, int, int);

template <typename T1, typename T2>
int binary_search_i(T1, T2, int, int);

template <typename T1, typename T2>
int ternary_search_r(T1, T2, int, int);

template <typename T1, typename T2>
int ternary_search_i(T1, T2, int, int);

// Search the nth element
template <typename T1, typename T2>
int seq_search_r_nth(T1 v, T2 x, int l, int r, int k);

template <typename T1, typename T2>
int seq_search_i_nth(T1 v, T2 x, int l, int r, int k);

#include "search.inl"

#endif
