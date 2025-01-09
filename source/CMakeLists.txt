add_library(${PROJECT_NAME}lib Shell.cpp)

add_executable(${PROJECT_NAME} Main.cpp)

target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    ${PROJECT_NAME}lib
)