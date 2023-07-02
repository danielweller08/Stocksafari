# Konfiguration des Buildsystems CMake ##

# Minimale Version des Buildsystems
cmake_minimum_required(VERSION 3.14)
# Name des Projekts
project(StockSafari)

## Optionen ##

# Setzte verwendeten C++-Standard auf C++17
set(CMAKE_CXX_STANDARD 17)

# Prüfe ob Heapspeicher gefunden wird,
# der nicht freigegeben wurde
# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)

# Füge selbsgeschriebene Includes hinzu
include_directories(include)
# Füge externe Includes hinzu
include_directories(external)


find_package(pybind11 REQUIRED)

# Sammle die Quelldateien
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# demo
add_executable(demo
  examples/demo.cpp
  ${SRC_FILES}
)

# pybind
pybind11_add_module(stocksafari
  extra/stocksafari_pybind.cpp
  ${SRC_FILES}
)

# Füge die OpenSSL-Bibliotheken hinzu
target_link_libraries(demo PRIVATE ssl crypto)
target_link_libraries(stocksafari PRIVATE ssl crypto)

# # Installiere die Bibliothek
install(TARGETS stocksafari
  COMPONENT python
  LIBRARY DESTINATION "${PROJECT_SOURCE_DIR}/extra")

# Use CMakes FetchContent
include(FetchContent)
# Workaround for CMake >= 3.24
# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

# Download GoogleTest (we use version 1.12.1)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# Workaround for Windows:
# Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Include CMake configuration of GoogleTest
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

# Enable GoogleTest
enable_testing()

# Declare test program testController
add_executable(testController tests/testController.cpp ${SRC_FILES})
target_link_libraries(testController GTest::gtest_main ssl crypto)
gtest_discover_tests(testController)
