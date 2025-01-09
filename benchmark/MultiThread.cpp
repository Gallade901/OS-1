// main.cpp
#include <iostream>
#include <thread>
#include <string>
#include "DiskBench.h"
#include "FactorBench.h"

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Use: " << argv[0] << " <file path> <count iterations> <number> <count iterations>" << std::endl;
        return 1;
    }

    std::string file_path = argv[1];
    int iterations_disk = std::atoi(argv[2]);
    if (iterations_disk <= 0) {
        std::cerr << "The number of iterations for disk benchmark must be a positive number." << std::endl;
        return 1;
    }

    unsigned long long number = std::strtoull(argv[3], nullptr, 10);
    int iterations_factor = std::atoi(argv[4]);
    if (number <= 1 || iterations_factor <= 0) {
        std::cerr << "Number must be greater than 1, and the count of iterations for factorization must be > 0." << std::endl;
        return 1;
    }

    std::thread disk_thread(random_read_benchmark, file_path, iterations_disk);
    std::thread factor_thread(factorize_number, number, iterations_factor);

    disk_thread.join();
    factor_thread.join();

    return 0;
}
