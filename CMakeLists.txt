option(AOP_CPP_BUILD_TESTS "Build all of aop's own tests." OFF)

cmake_minimum_required(VERSION 3.14)

project(aop VERSION 0.0.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# place binaries and libraries according to GNU standards
include(GNUInstallDirs)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

include(FetchContent)

FetchContent_Declare(
    result_cpp
    GIT_REPOSITORY https://github.com/Dup4/result-cpp.git
    GIT_TAG v0.0.13
)

FetchContent_MakeAvailable(result_cpp)
FetchContent_GetProperties(result_cpp)
set(RESULT_CPP_INCLUDE_DIR ${result_cpp_SOURCE_DIR}/include)

include_directories(
    ${PROJECT_SOURCE_DIR}/include/
    ${RESULT_CPP_INCLUDE_DIR}
)

add_library(aop INTERFACE)
target_include_directories(aop INTERFACE
    ${PROJECT_SOURCE_DIR}/include/
    ${RESULT_CPP_INCLUDE_DIR}
)

if(AOP_CPP_BUILD_TESTS)
    enable_testing()

    add_subdirectory(test/)
endif()
