#ifndef _COMPACT_H_
#define _COMPACT_H_

//
// Function prototypes.
//

// Compare (std::bsearch dependency)
template <typename T>
int compare(T, T);

// Wrappers
template <typename T>
int wrapper_std_search(T *, T, int, int);

template <typename T>
int wrapper_std_bsearch(T *, T, int, int);

// Search Functions
template <typename T>
int seq_search_r(T *, T, int, int);

template <typename T>
int seq_search_i(T *, T, int, int);

template <typename T>
int binary_search_r(T *, T, int, int);

template <typename T>
int binary_search_i(T *, T, int, int);

template <typename T>
int ternary_search_r(T *, T, int, int);

template <typename T>
int ternary_search_i(T *, T, int, int);

// Search the nth element
template <typename T>
int mixed_search_nth(T *, T, int, int, int, int (*)(T *, T, int, int));

template <typename T>
int sorted_search_nth(T *, T, int, int, int, int (*)(T *, T, int, int));

// Random Fill
template <typename T>
void randomFill(T *&, const T, const T, const unsigned int, const int);

// Time Measurement
template <typename T>
long double time_measurement(int, int (*)(T *, T, int, int), T, T *, int, int);

template <typename T>
long double time_measurement_nth(int, int (*)(T *, T, int, int, int, int (*)(T *, T, int, int)), T, T *, int, int, int, int (*)(T *, T, int, int));

#include "search.inl"

#endif