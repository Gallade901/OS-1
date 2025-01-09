#include <cstdlib> 
#include <iostream> 
#include <string>

// Функция для проверки запуска программы
bool test_program_execution(const std::string& program_path, const std::string& arguments = "") {
    std::string command = program_path + " " + arguments;
    int return_code = std::system(command.c_str());

    if (return_code == 0) {
        std::cout << "Program '" << program_path << "' executed successfully." << std::endl;
        return true;
    } else {
        std::cerr << "Program '" << program_path << "' failed with code " << return_code << "." << std::endl;
        return false;
    }
}

int main() {
    bool all_tests_passed = true;

    // Тестируем запуск multiThread.exe
    all_tests_passed &= test_program_execution("..\\benchmark\\multiThread.exe", "C:\\Users\\MSI\\Desktop\\PremierePro\\Adobe.Premiere.Pro.2024.u3.Multilingual.iso 1 52 1");

    // Тестируем запуск shell.exe
    all_tests_passed &= test_program_execution("..\\source\\shell.exe");

    // Тестируем запуск benchmarkFactor.exe
    all_tests_passed &= test_program_execution("..\\benchmark\\benchmarkFactor.exe", "52 1");

    // Тестируем запуск benchmarkDisk.exe
    all_tests_passed &= test_program_execution("..\\benchmark\\benchmarkDisk.exe", "C:\\Users\\MSI\\Desktop\\PremierePro\\Adobe.Premiere.Pro.2024.u3.Multilingual.iso 1");

    // Вывод результата
    if (all_tests_passed) {
        std::cout << "All tests passed successfully!" << std::endl;
        return 0; // Успешное завершение
    } else {
        std::cerr << "Some tests failed!" << std::endl;
        return 1; // Ошибка
    }
}
