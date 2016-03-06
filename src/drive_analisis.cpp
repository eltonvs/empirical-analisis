// Copyright - 2016

#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <functional>
#include <limits>

#include "search.h"

//
// Constant expressions.
//
constexpr auto N_DEFAULT(20u);  // Default number of elements.
constexpr auto N_MAX(31u);     // Max number of elements in the array.

//
// Function prototypes.
//
template <typename T>
void randomFill(T *&, const T, const T, const unsigned int, const int);

//
// Main program.
//
int main(int argc, char *argv[]) {
    auto arrSz(N_DEFAULT);  // Initialize vector size.

    // Process any command line arguments.
    if (argc > 1) {
    // In case the user has provided a value for us.
        std::stringstream(argv[1]) >> arrSz;
    }

    // Do we have a valid array size so far?
    if (arrSz <= 5 || arrSz > N_MAX) {
        std::cout << "\n\n>>> Invalid argument provided!\n"
                  << "    Correct sintax: " << argv[0] << " [N > 5 and N <= " << N_MAX << "]\n"
                  << "    Assuming N = " << N_DEFAULT << " for this run.\n";
        arrSz = N_DEFAULT;  // Back to the default value.
    }

    std::cout << "\n\n>>> Required array size is: 2^" << arrSz << "\n\n";

    // Store the data.
    long int *V;

    // To randomFill
    long int lower = 0, upper = 100;

    // Allocate V
    V = new long int[arrSz];

    // Seed with a real random value, if available.
    std::random_device r;
    // Fill it up with random integers.
    randomFill(V, lower, upper, r(), arrSz);

    // Printing out the array, just to make sure we've got random integers.
    std::cout << ">>> ORIGINAL Vet = [ ";
    for (auto i(0u); i < arrSz; i++)
        std::cout << *(V+i) << ' ';
    std::cout << "], Size = " << arrSz << "\n\n";

    // Sort array with the standard sort function.
    std::sort(V, V + arrSz);

    // Printing out the sorted array.
    std::cout << ">>> SORTED Vet = [ ";
    for (auto i(0u); i < arrSz; i++)
        std::cout << *(V+i) << ' ';
    std::cout << "], Size = " << arrSz << "\n\n";

    // bsearch wrapper example
    long int to_search = 10;
    std::cout << wrapper_std_bsearch(V, to_search, 0, arrSz-1) << std::endl;

    // Delete allocated vector
    delete[] V;

    return EXIT_SUCCESS;
}

// Fill a vector with random numbers in the range [l -> lower, u -> upper]
template <typename T>
void randomFill(T *&V, const T l, const T u, const unsigned int seed, const int s) {
    // use the default random engine and an uniform distribution
    std::default_random_engine eng(seed);
    std::uniform_real_distribution<double> distr(l, u);

    // Fill up vector
    for (int i = 0; i < s; i++)
        *(V+i) = distr(eng);
}
