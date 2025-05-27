cmake_minimum_required(VERSION 3.10)
project(DHondtElection)

set(CMAKE_CXX_STANDARD 17)

# Set the path to SFML config BEFORE calling find_package
set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")

# Find SFML components (only once)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add executable with all your source files
add_executable(DHondt main.cpp Election.cpp)

# Link SFML libraries to your executable
target_link_libraries(DHondt sfml-graphics sfml-window sfml-system)
