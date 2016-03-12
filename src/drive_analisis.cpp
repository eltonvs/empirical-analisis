// Copyright - 2016

#include <iostream>   // To input/output
#include <algorithm>  // To std:sort()
#include <fstream>    // To files i/o
#include <sstream>    // To convert args
#include <vector>     // To use vectors
#include <string>     // To use strings

#include "search.h"

//
// Constant expressions.
//
constexpr auto N_DEFAULT(20u);  // Default number of elements (exponent).
constexpr auto N_MAX(31u);      // Max number of elements (exponent).
constexpr auto N_EXEC(100);     // Number of executions to take average time.

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

    // Create vector
    std::vector<long int> V(arrSz);

    // To randomFill
    long int lower = -9876543210, upper = 9876543210;
    int seed = 2;

    // Create Functions Array
    int (*functions[])(std::vector<long int>, long int, int, int) = {
        wrapper_std_search,
        seq_search_r,
        seq_search_i,
        wrapper_std_bsearch,
        binary_search_r,
        binary_search_i,
        ternary_search_r,
        ternary_search_i,
    };

    // This will be used to save (folder name)
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

    // Define numbers to search in array
    long int worst_case = upper + 1;  // inexistent value
    long int third_quartile;          // 3/4 lenght

    // Fill it up with random integers.
    randomFill(V, lower, upper, seed, arrSz);

    // Tests with the mixed array
    for (auto n(16u); n < arrSz; n *= 2) {
        // Update third quartile with the new size
        third_quartile = V[3*n/4];  // 3/4 lenght

        // Show message with n
        std::cout << "\nMixed - Using n = " << n << " for this run\n";

        for (int i = 0; i < 3; i++) {
            // seq_search_r() limits (Recursion Limit)
            if (i == 1 && n >= 262144)
                continue;

            std::cout << ">>> Processing " << functions_name[i] << '\n';
            std::cout << std::fixed << "WC = " << time_measurement(N_EXEC, functions[i], worst_case, V.begin(), 0, n-1) << '\n';
            std::cout << std::fixed << "TQ = " << time_measurement(N_EXEC, functions[i], third_quartile, V.begin(), 0, n-1) << '\n';
            std::cout << std::fixed << "KE = " << time_measurement_nth(N_EXEC, mixed_search_nth, third_quartile, V.begin(), 0, n-1, 2, functions[i]) << '\n';
        }
    }

    // Sort array with the standard sort function.
    std::sort(V.data(), V.data() + arrSz);

    // Tests with the sorted array
    for (auto n(16u); n < arrSz; n *= 2) {
        // Update third quartile with the new size
        third_quartile = V[3*n/4];  // 3/4 lenght

        // Show message with n
        std::cout << "\nSorted - Using n = " << n << " for this run\n";

        for (int i = 0; i < 3; i++) {
            // seq_search_r() limits (Recursion Limit)
            if (i == 1 && n >= 262144)
                continue;

            std::cout << ">>> Processing " << functions_name[i] << '\n';
            std::cout << std::fixed << "WC = " << time_measurement(N_EXEC, functions[i], worst_case, V.begin(), 0, n-1) << '\n';
            std::cout << std::fixed << "TQ = " << time_measurement(N_EXEC, functions[i], third_quartile, V.begin(), 0, n-1) << '\n';
            std::cout << std::fixed << "KE = " << time_measurement_nth(N_EXEC, mixed_search_nth, third_quartile, V.begin(), 0, n-1, 2, functions[i]) << '\n';
        }
        for (int i = 3; i < 8; i++) {
            std::cout << ">>> Processing " << functions_name[i] << '\n';
            std::cout << std::fixed << "WC = " << time_measurement(N_EXEC, functions[i], worst_case, V.begin(), 0, n-1) << '\n';
            std::cout << std::fixed << "TQ = " << time_measurement(N_EXEC, functions[i], third_quartile, V.begin(), 0, n-1) << '\n';
            std::cout << std::fixed << "KE = " << time_measurement_nth(N_EXEC, sorted_search_nth, third_quartile, V.begin(), 0, n-1, 2, functions[i]) << '\n';
        }
    }

    return EXIT_SUCCESS;
}
