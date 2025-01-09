#include "Shell.hpp"

#include <string>
#include <regex>
#include <thread>



namespace monolith {

std::vector<std::string> split(const std::string &line) {
    std::vector<std::string> tokens;
    tokens.reserve(5); // Оптимизация для средней длины команды
    std::istringstream stream(line);
    std::string token;
    while (stream >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

int ShellRun() {
    std::cout << "Shell for Windows\nType 'exit' to quit.\n\n";

    while (true) {
        std::cout << "> ";
        std::string input_line;
        std::getline(std::cin, input_line);

        // Игнорируем пустую строку или строки, содержащие только пробелы
        if (input_line.empty() || input_line.find_first_not_of(" \t") == std::string::npos) {
            continue;
        }

        // Выход из shell
        if (input_line == "exit") {
            break;
        }

        // Разделяем команду на имя программы и аргументы
        std::vector<std::string> args = split(input_line);
        if (args.empty()) {
            continue;
        }

        // Имя программы
        std::string program = args[0];
        if (!std::regex_match(args[1], std::regex("\\d+"))) {
            std::cerr << "Error: Process count must be a positive integer.\n";
            continue;
        }
        int64_t count_process = 1;
        try {
            count_process = std::stoll(args[1], nullptr, 10);
        } catch (const std::exception &e) {
            std::cerr << "Error: Failed to parse process count: " << e.what() << "\n";
            continue;
        }
        

        // Преобразуем аргументы в формат, понятный CreateProcess
        std::string command_line;
        for (size_t i = 0; i < args.size(); ++i) {
            if (i == 1) {
                continue;
            }
            command_line += args[i] + " ";
        }

        // Удаляем лишний пробел в конце
        if (!command_line.empty()) {
            command_line.pop_back();
        }

        // Подготовка параметров для CreateProcess
        STARTUPINFO si;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        PROCESS_INFORMATION pi;
        ZeroMemory(&pi, sizeof(pi));

        // Копия строки для CreateProcess
        std::string command_copy = command_line;
        LPSTR cmd_line_ptr = command_copy.empty() ? nullptr : &command_copy[0];

        // Старт измерения времени
        auto start_time = std::chrono::high_resolution_clock::now();

        // Попытка запуска процесса
        for (size_t i = 0; i < count_process; i++) {
            if (!CreateProcess(
                    program.c_str(),                     // Имя программы
                    cmd_line_ptr,                        // Аргументы
                    nullptr,                             // Атрибуты безопасности процесса
                    nullptr,                             // Атрибуты безопасности потока
                    FALSE,                               // Унаследовать дескрипторы
                    0,                                   // Флаги создания процесса
                    nullptr,                             // Переменные окружения
                    nullptr,                             // Рабочая директория
                    &si,                                 // Структура STARTUPINFO
                    &pi)) {                              // Структура PROCESS_INFORMATION
                std::cerr << "Failed to start process: " << GetLastError() << "\n";
                continue;
            }
        }

        // Ожидание завершения процесса
        WaitForSingleObject(pi.hProcess, INFINITE);

        // Остановка измерения времени
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_time = end_time - start_time;

        // Закрытие дескрипторов процесса
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        // Вывод времени выполнения
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Execution time: " << elapsed_time.count() << " seconds\n";
    }

    return 0;
}

}  // namespace monolith
