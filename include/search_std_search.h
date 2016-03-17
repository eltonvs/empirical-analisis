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
int wrapper_std_search(std::vector<T>, T, int, int);

// Search the nth element
template <typename T>
int mixed_search_nth(std::vector<T>, T, int, int, int, int (*)(std::vector<T>, T, int, int));

// Random Fill
template <typename T>
void randomFill(std::vector<T> &, const T, const T, const unsigned int, const int);

// Time Measurement
template <typename T>
long double time_measurement(int, int (*)(std::vector<T>, T, int, int), T, std::vector<long int>::const_iterator, int, int);

template <typename T>
long double time_measurement_nth(int, int (*)(std::vector<T>, T, int, int, int, int (*)(std::vector<T>, T, int, int)), T, std::vector<long int>::const_iterator, int, int, int, int (*)(std::vector<T>, T, int, int));

#include "search_std_search.inl"

#endif