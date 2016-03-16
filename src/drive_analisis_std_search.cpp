// Copyright - 2016

#include <iostream>   // To input/output
#include <algorithm>  // To std:sort()
#include <fstream>    // To files i/o
#include <sstream>    // To convert args
#include <vector>     // To use vectors
#include <string>     // To use strings

#include "search_2.h"

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

    // Create array of files (8 functions with 3 "cases")
    std::ofstream files[2][3];

    files[0][0].open("results/wrapper_std_search/worst_case.dat");
    files[0][1].open("results/wrapper_std_search/third_quartile.dat");
    files[0][2].open("results/wrapper_std_search/third_occurrence.dat");
    files[1][0].open("results/wrapper_std_search/mixed_worst_case.dat");
    files[1][1].open("results/wrapper_std_search/mixed_third_quartile.dat");
    files[1][2].open("results/wrapper_std_search/mixed_third_occurrence.dat");

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

        std::cout << ">>> Processing wrapper_std_search\n";
        //std::cout << std::fixed << "WC = " << time_measurement(N_EXEC, wrapper_std_search, worst_case, V.begin(), 0, n-1) << '\n';
        //std::cout << std::fixed << "TQ = " << time_measurement(N_EXEC, wrapper_std_search, third_quartile, V.begin(), 0, n-1) << '\n';
        //std::cout << std::fixed << "KE = " << time_measurement_nth(N_EXEC, mixed_search_nth, third_quartile, V.begin(), 0, n-1, 2, wrapper_std_search) << '\n';
        files[1][0] << std::fixed << n << "\t" << time_measurement(N_EXEC, wrapper_std_search, worst_case, V.begin(), 0, n-1) << "\n";
        files[1][1] << std::fixed << n << "\t" << time_measurement(N_EXEC, wrapper_std_search, third_quartile, V.begin(), 0, n-1) << "\n";
        files[1][2] << std::fixed << n << "\t" << time_measurement_nth(N_EXEC, mixed_search_nth, third_quartile, V.begin(), 0, n-1, 2, wrapper_std_search) << "\n";
    }

    // Sort array with the standard sort function.
    std::sort(V.data(), V.data() + arrSz);

    // Tests with the sorted array
    for (auto n(16u); n < arrSz; n *= 2) {
        // Update third quartile with the new size
        third_quartile = V[3*n/4];  // 3/4 lenght

        // Show message with n
        std::cout << "\nSorted - Using n = " << n << " for this run\n";

        std::cout << ">>> Processing wrapper_std_search\n";
        //std::cout << std::fixed << "WC = " << time_measurement(N_EXEC, wrapper_std_search, worst_case, V.begin(), 0, n-1) << '\n';
        //std::cout << std::fixed << "TQ = " << time_measurement(N_EXEC, wrapper_std_search, third_quartile, V.begin(), 0, n-1) << '\n';
        //std::cout << std::fixed << "KE = " << time_measurement_nth(N_EXEC, mixed_search_nth, third_quartile, V.begin(), 0, n-1, 2, wrapper_std_search) << '\n';
        files[0][0] << std::fixed << n << "\t" << time_measurement(N_EXEC, wrapper_std_search, worst_case, V.begin(), 0, n-1) << "\n";
        files[0][1] << std::fixed << n << "\t" << time_measurement(N_EXEC, wrapper_std_search, third_quartile, V.begin(), 0, n-1) << "\n";
        files[0][2] << std::fixed << n << "\t" << time_measurement_nth(N_EXEC, mixed_search_nth, third_quartile, V.begin(), 0, n-1, 2, wrapper_std_search) << "\n";
    }

    // Close Opened files
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            files[i][j].close();

    return EXIT_SUCCESS;
}
