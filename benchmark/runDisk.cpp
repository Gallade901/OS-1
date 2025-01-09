#include "DiskBench.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Use: " << argv[0] << " <file path> <count iterations>" << std::endl;
        return 1;
    }

    std::string file_path = argv[1];
    int iterations = std::atoi(argv[2]);
    if (iterations <= 0) {
        std::cerr << "The number of iterations must be a positive number." << std::endl;
        return 1;
    }

    random_read_benchmark(file_path, iterations);
    return 0;
}