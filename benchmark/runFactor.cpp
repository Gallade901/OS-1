#include "FactorBench.h" 

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Use: " << argv[0] << " <number> <count iterations>" << std::endl;
        return 1;
    }

    unsigned long long number = std::strtoull(argv[1], nullptr, 10);
    int iterations = std::atoi(argv[2]);

    if (number <= 1 || iterations <= 0) {
        std::cerr << "Nimber could more than 1, and count iterations must > 0." << std::endl;
        return 1;
    }

    factorize_number(number, iterations);
    return 0;
}