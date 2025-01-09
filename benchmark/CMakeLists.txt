add_library(${PROJECT_NAME}lib-Factor FactorBench.cpp)
add_library(${PROJECT_NAME}lib-Disk DiskBench.cpp)

add_executable(benchmarkDisk runDisk.cpp)
add_executable(benchmarkFactor runFactor.cpp)
add_executable(multiThread MultiThread.cpp)

target_link_libraries(
    benchmarkFactor PUBLIC
    ${PROJECT_NAME}lib-Factor
)

target_link_libraries(
    benchmarkDisk PUBLIC
    ${PROJECT_NAME}lib-Disk
)

target_link_libraries(
    multiThread PUBLIC
    ${PROJECT_NAME}lib-Disk PUBLIC
    ${PROJECT_NAME}lib-Factor
)









# Указываем агрессивные флаги оптимизации для benchmarkDisk
target_compile_options(benchmarkDisk PRIVATE
    -O3             # Уровень оптимизации 3
    -march=native   # Использовать все доступные инструкции для текущей архитектуры
    -ffast-math     # Быстрые математические вычисления (возможно, с потерей точности)
    -funroll-loops  # Разворачивать циклы
)

# Указываем агрессивные флаги оптимизации для benchmarkFactor
target_compile_options(benchmarkFactor PRIVATE
    -O3
    -march=native
    -ffast-math
    -flto           # Link Time Optimization (оптимизация на этапе линковки)
)
