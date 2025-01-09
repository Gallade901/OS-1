// disk_benchmark.cpp: Нагрузчик 1 - Измерение задержки случайного чтения

#include "DiskBench.h"

const size_t BLOCK_SIZE = 1024; // Размер блока 1KB

void random_read_benchmark(const std::string& file_path, int iterations) {
    std::ifstream file(file_path, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file: " << file_path << std::endl;
        return;
    }

    // Определяем размер файла
    file.seekg(0, std::ios::end);
    size_t file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    if (file_size < BLOCK_SIZE) {
        std::cerr << "The file is too small for testing" << std::endl;
        return;
    }

    std::vector<char> buffer(BLOCK_SIZE);
    std::vector<size_t> offsets(iterations);

    // Генерация случайных позиций для чтения
    for (int i = 0; i < iterations; ++i) {
        offsets[i] = (std::rand() % (file_size / BLOCK_SIZE)) * BLOCK_SIZE;
    }

    // Измерение задержек чтения
    auto start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        file.seekg(offsets[i]);
        file.read(buffer.data(), BLOCK_SIZE);
        if (!file) {
            std::cerr << "Error read file." << std::endl;
            break;
        }
    }
    auto end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end_time - start_time;
    std::cout << "Average read latency: " << (duration.count() / iterations) * 1e6 << " mks" << std::endl;
}


