#include <algorithm>  // To std::search
#include <cstdlib>    // To std::bsearch
#include <chrono>     // To time measurement
#include <random>     // To generate random numbers
#include "search.h"

template <typename T>
int compare(T a, T b) {
    return *(long int *)a < *(long int *)b ? -1 : *(long int *)a > *(long int *)b ? 1 : 0;
}

template <typename T>
int wrapper_std_search(T *v, T x, int l, int r) {
    /* Not Working
    T needle[] = {x};
    std::vector<long int>::iterator i;
    i = std::search(v.begin()+l, v.begin()+r, needle, needle+1);

    return (i != v.begin()+r) ? i - (v.begin()+l) : -1;
    */
    return 0;
}

template <typename T>
int wrapper_std_bsearch(T *v, T x, int l, int r) {
    T *a = (T *)bsearch(&x, v+l, r-l+1, sizeof(T), compare);
    return a == 0 ? -1 : a-v;
}

template <typename T>
int seq_search_r(T *v, T x, int l, int r) {
    return (l > r) ? -1 :
        *(v+1) == x ? l : seq_search_r(v, x, l+1, r);
}

template <typename T>
int seq_search_i(T *v, T x, int l, int r) {
    while (l <= r) {
        if (*(v+1) == x)
            return l;
        l++;
    }

    return -1;
}

template <typename T>
int binary_search_r(T *v, T x, int l, int r) {
    int m = (r + l)/2;

    return (l > r) ? -1 :
        *(v+m) > x ? binary_search_r(v, x, l, m-1) :
            *(v+m) < x ? binary_search_r(v, x, m+1, r) : m;
}

template <typename T>
int binary_search_i(T *v, T x, int l, int r) {
    while (l <= r) {
        int m = (r + l)/2;
        if (*(v+m) == x)
            return m;
        else if (*(v+m) < x)
            l = m+1;
        else
            r = m-1;
    }

    return -1;
}

template <typename T>
int ternary_search_r(T *v, T x, int l, int r) {
    int m1 = (r+l+l)/3, m2 = (r+r+l)/3;

    return (l > r) ? -1 :
        x == *(v+m1) ? m1 :
            x == *(v+m2) ? m2 :
                x > *(v+m2) ? ternary_search_r(v, x, m2+1, r) :
                    x < *(v+m1) ? ternary_search_r(v, x, l, m1-1) : ternary_search_r(v, x, m1+1, m2-1);
}

template <typename T>
int ternary_search_i(T *v, T x, int l, int r) {
    while (l <= r) {
        int m1 = (r+l+l)/3, m2 = (r+r+l)/3;
        if (*(v+m1) == x)
            return m1;
        else if (*(v+m2) == x)
            return m2;
        else if (x > *(v+m2))
            l = m2+1;
        else if (x < *(v+m1))
            r = m1-1;
        else
            l = m1+1, r = m2-1;
    }

    return -1;
}

template <typename T>
int mixed_search_nth(T *v, T x, int l, int r, int k, int (*mixed_search)(T *, T, int, int)) {
    int result = l-1;
    for (int i = 0; i <= k || !(i > 0 && l-1 == result); i++)
        result = mixed_search(v, x, result+1, r);
    return result;
}

template <typename T>
int sorted_search_nth(T *v, T x, int l, int r, int k, int (*sorted_search)(T *, T, int, int)) {
    int first_result = sorted_search(v, x, l, r);
    while (first_result > 0 && *(v+first_result-1) == x)
        first_result--;
    return *(v+first_result+k) == x ? first_result+k : -1;
}

// Fill a vector with random numbers in the range [l -> lower, u -> upper]
template <typename T>
void randomFill(T *&v, const T l, const T u, const unsigned int seed, const int s) {
    // use the default random engine and an uniform distribution
    std::default_random_engine eng(seed);
    std::uniform_real_distribution<double> distr(l, u);

    // Fill up vector
    for (int i = 0; i < s; i++)
        *(v+i) = distr(eng);
}

template <typename T>
long double time_measurement(int n, int (*f)(T *, T, int, int), T x, T *v, int l, int r) {
    long double time = 0;
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
long double time_measurement_nth(int n, int (*f)(T *, T, int, int, int, int (*)(T *, T, int, int)), T x, T *v, int l, int r, int k, int (*f2)(T *, T, int, int)) {
    long double time = 0;
    for (int i = 0; i < n; i++) {
        auto s = std::chrono::steady_clock::now();
        f(v, x, l, r, k, f2);
        auto e = std::chrono::steady_clock::now();
        auto diff = std::chrono::duration <double, std::milli> (e-s).count();

        time += (diff - time)/(i+1);
    }
    return time;
}
