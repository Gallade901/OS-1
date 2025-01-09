// factors.cpp: Нагрузчик 2 - Разложение числа на простые множители

#include "FactorBench.h"

void factorize_number(unsigned long long number, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        unsigned long long n = number;
        std::vector<unsigned long long> factors;

        for (unsigned long long d = 2; d * d <= n; ++d) {
            while (n % d == 0) {
                factors.push_back(d);
                n /= d;
            }
        }
        if (n > 1) {
            factors.push_back(n);
        }

        // Печать результатов для отладки (опционально)
        // std::cout << "Iterations " << i + 1 << ": " << number << " = ";
        // for (size_t j = 0; j < factors.size(); ++j) {
        //     std::cout << factors[j];
        //     if (j < factors.size() - 1) {
        //         std::cout << " * ";
        //     }
        // }
        // std::cout << std::endl;
    }
}


