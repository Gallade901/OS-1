#ifndef DISK_BENCHMARK_H
#define DISK_BENCHMARK_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <windows.h> // Для работы с низкоуровневыми системными вызовами

void random_read_benchmark(const std::string& file_path, int iterations);

#endif
