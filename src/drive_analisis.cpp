// Copyright - 2016

#include <iostream>   // To input/output
#include <fstream>    // To files i/o
#include <sstream>    // To convert args
#include <random>     // To generate random numbers
#include <chrono>     // To time measurement
#include <algorithm>  // To std::search
#include <cstdlib>    // To std::bsearch
#include <string>     // To use strings

#include "search.h"

//
// Constant expressions.
//
constexpr auto N_DEFAULT(20u);  // Default number of elements (exponent).
constexpr auto N_MAX(31u);      // Max number of elements (exponent).

//
// Function prototypes.
//
template <typename T>
void randomFill(T *&, const T, const T, const unsigned int, const int);

//
// Main function.
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

    arrSz = pow(2, arrSz);

    // Store the data.
    long int *V;

    // Allocate V
    V = new long int[arrSz];

    // To randomFill
    long int lower = -123456789, upper = 123456789;

    // Define random seed
    int seed = 2;

    // Create Functions Array
    int (*functions[])(long int *, long int, int, int) = {
        wrapper_std_search,
        seq_search_r,
        seq_search_i,
        wrapper_std_bsearch,
        binary_search_r,
        binary_search_i,
        ternary_search_r,
        ternary_search_i,
    };

    std::string functions_name[] = {
        "wrapper_std_search()",
        "seq_search_r()",
        "seq_search_i()",
        "wrapper_std_bsearch()",
        "binary_search_r()",
        "binary_search_i()",
        "ternary_search_r()",
        "ternary_search_i()",
    };

    // Fill it up with random integers.
    randomFill(V, lower, upper, seed, arrSz);

    for (auto n(16u); n < arrSz; n *= 2) {
        // Define numbers to search in array
        long int worst_case = upper + 1;          // inexistent value
        long int third_quartile = *(V+3*n/4);  // 3/4 lenght

        #ifdef PRINT_ARRAY_MIXED
        // Printing out the array, just to make sure we've got random integers.
        std::cout << ">>> ORIGINAL Vet = [ ";
        for (auto i(0u); i < n; i++)
            std::cout << *(V+i) << ' ';
        std::cout << "], Size = " << n << "\n\n";
        #endif

        std::cout << "\nElement = " << third_quartile << "\n";
        for (int i = 0; i < 3; i++) {
            std::cout << "Finding the Worst Case with " << functions_name[i] << " = " << functions[i](V, worst_case, 0, n-1) << std::endl;
            std::cout << "Finding the 3/4 Lenght with " << functions_name[i] << " = " << functions[i](V, third_quartile, 0, n-1) << std::endl;
            std::cout << "Finding the 3rd element with " << functions_name[i] << " = " << mixed_search_nth(V, third_quartile, 0, n-1, 2, functions[i]) << std::endl << std::endl;
        }

        // Sort array with the standard sort function.
        std::sort(V, V + n);

        #ifdef PRINT_ARRAY_SORTED
        // Printing out the sorted array, just to make sure we've got random integers.
        std::cout << ">>> SORTED Vet = [ ";
        for (auto i(0u); i < n; i++)
            std::cout << *(V+i) << ' ';
        std::cout << "], Size = " << n << "\n\n";
        #endif

        std::cout << "\nNow with the sorted Array\n";
        for (int i = 0; i < 3; i++) {
            std::cout << "Finding the Worst Case with " << functions_name[i] << " = " << functions[i](V, worst_case, 0, n-1) << std::endl;
            std::cout << "Finding the 3/4 Lenght with " << functions_name[i] << " = " << functions[i](V, third_quartile, 0, n-1) << std::endl;
            std::cout << "Finding the 3rd element with " << functions_name[i] << " = " << mixed_search_nth(V, third_quartile, 0, n-1, 2, functions[i]) << std::endl << std::endl;
        }
        for (int i = 3; i < 8; i++) {
            std::cout << "Finding the Worst Case with " << functions_name[i] << " = " << functions[i](V, worst_case, 0, n-1) << std::endl;
            std::cout << "Finding the 3/4 Lenght with " << functions_name[i] << " = " << functions[i](V, third_quartile, 0, n-1) << std::endl;
            std::cout << "Finding the 3rd element with " << functions_name[i] << " = " << sorted_search_nth(V, third_quartile, 0, n-1, 2, functions[i]) << std::endl << std::endl;
        }
    }
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
