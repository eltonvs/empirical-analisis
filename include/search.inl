#include <algorithm>
#include "search.h"

template <typename T>
int compare(T a, T b) {
    return *(long int *)a - *(long int *)b;
}

template <typename T1, typename T2>
int wrapper_std_bsearch(T1 v, T2 x, int r, int l) {
    T1 a = (T1)bsearch(&x, v, l-r+1, sizeof(*v), compare);
    return (a == 0) ? -1 : a-v;
}
