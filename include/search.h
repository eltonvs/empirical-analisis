#ifndef _COMPACT_H_
#define _COMPACT_H_

//
// Function prototypes.
//

// Compare (std::bsearch dependency)
template <typename T>
int compare(T, T);

// Wrappers
template <typename T1, typename T2>
int wrapper_std_search(T1, T2, int, int);

template <typename T1, typename T2>
int wrapper_std_bsearch(T1, T2, int, int);

// Search Functions
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
int mixed_search_nth(T1, T2, int, int, int, int (*)(T1, T2, int, int));

template <typename T1, typename T2>
int sorted_search_nth(T1, T2, int, int, int, int (*)(T1, T2, int, int));

#include "search.inl"

#endif
