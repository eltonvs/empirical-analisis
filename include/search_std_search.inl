#include <algorithm>  // To std::search
#include <cstdlib>    // To std::bsearch
#include <chrono>     // To time measurement
#include <random>     // To generate random numbers
#include "search_2.h"

template <typename T>
int wrapper_std_search(std::vector<T> v, T x, int l, int r) {
    T needle[] = {x};
    std::vector<long int>::iterator i;
    i = std::search(v.begin()+l, v.begin()+r, needle, needle+1);

    return (i != v.begin()+r) ? i - (v.begin()+l) : -1;
}


template <typename T>
int mixed_search_nth(std::vector<T> v, T x, int l, int r, int k, int (*mixed_search)(std::vector<T>, T, int, int)) {
    int result = l-1;
    for (int i = 0; i <= k && !(i > 0 && -1 == result); i++)
        result = mixed_search(v, x, result+1, r);
    return result;
}

// Fill a vector with random numbers in the range [l -> lower, u -> upper]
template <typename T>
void randomFill(std::vector<T> &v, const T l, const T u, const unsigned int seed, const int s) {
    // use the default random engine and an uniform distribution
    std::default_random_engine eng(seed);
    std::uniform_real_distribution<double> distr(l, u);

    // Fill up vector
    for (int i = 0; i < s; i++)
        v[i] = distr(eng);
}

template <typename T>
long double time_measurement(int n, int (*f)(std::vector<T>, T, int, int), T x, std::vector<long int>::const_iterator it, int l, int r) {
    long double time = 0;
    std::vector<long int> v(it+l, it+r);
    for (int i = 0; i < n; i++) {
        auto s = std::chrono::steady_clock::now();
        f(v, x, l, r);
        auto e = std::chrono::steady_clock::now();
        auto diff = std::chrono::duration <double, std::milli> (e-s).count();

        time += (diff - time)/(i+1);
    }
    return time;
}

template <typename T>
long double time_measurement_nth(int n, int (*f)(std::vector<T>, T, int, int, int, int (*)(std::vector<T>, T, int, int)), T x, std::vector<long int>::const_iterator it, int l, int r, int k, int (*f2)(std::vector<T>, T, int, int)) {
    long double time = 0;
    std::vector<long int> v(it+l, it+r);
    for (int i = 0; i < n; i++) {
        auto s = std::chrono::steady_clock::now();
        f(v, x, l, r, k, f2);
        auto e = std::chrono::steady_clock::now();
        auto diff = std::chrono::duration <double, std::milli> (e-s).count();

        time += (diff - time)/(i+1);
    }
    return time;
}
