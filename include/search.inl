#include <algorithm>
#include "search.h"

template <typename T>
int compare(T a, T b) {
    return *(long int *)a - *(long int *)b;
}

template <typename T1, typename T2>
int wrapper_std_bsearch(T1 v, T2 x, int l, int r) {
    T1 a = (T1)bsearch(&x, v, r-l+1, sizeof(*v), compare);
    return a == 0 ? -1 : a-v;
}

template <typename T1, typename T2>
int seq_search_r(T1 v, T2 x, int l, int r) {
    return (l > r) ? -1 :
        *(v+l) == x ? l : seq_search_r(v, x, l+1, r);
}

template <typename T1, typename T2>
int seq_search_i(T1 v, T2 x, int l, int r) {
    while (l <= r) {
        if (*(v+l) == x)
            return l;
        l++;
    }

    return -1;
}

template <typename T1, typename T2>
int binary_search_r(T1 v, T2 x, int l, int r) {
    int m = (r + l)/2;

    return (l > r) ? -1 :
        *(v+m) > x ? binary_search_r(v, x, l, m-1) :
            *(v+m) < x ? binary_search_r(v, x, m+1, r) : m;
}

template <typename T1, typename T2>
int binary_search_i(T1 v, T2 x, int l, int r) {
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

template <typename T1, typename T2>
int ternary_search_r(T1 v, T2 x, int l, int r) {
    int m1 = (r+l+l)/3, m2 = (r+r+l)/3;

    return (l > r) ? -1 :
        x == *(v+m1) ? m1 :
            x == *(v+m2) ? m2 :
                x > *(v+m2) ? ternary_search_r(v, x, m2+1, r) :
                    x < *(v+m1) ? ternary_search_r(v, x, l, m1-1) : ternary_search_r(v, x, m1+1, m2-1);
}

template <typename T1, typename T2>
int ternary_search_i(T1 v, T2 x, int l, int r) {
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