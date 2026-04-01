cmake_minimum_required(VERSION 3.16)
project(interview_data_structures VERSION 1.0.0 LANGUAGES CXX)

# ─── C++ Standard ─────────────────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ─── Compiler flags ───────────────────────────────────────────────────────────
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Wno-unused-parameter)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-g -O0 -fsanitize=address,undefined)
        add_link_options(-fsanitize=address,undefined)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(-O2 -DNDEBUG)
    endif()
endif()

# ─── Include directories ──────────────────────────────────────────────────────
include_directories(${CMAKE_SOURCE_DIR}/src)

# ─── Helper macro ─────────────────────────────────────────────────────────────
macro(add_example NAME SOURCE)
    add_executable(${NAME} ${SOURCE})
    target_include_directories(${NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
endmacro()

# ─── Data Structure Examples ──────────────────────────────────────────────────
add_example(examples_arrays
    src/data_structures/arrays/examples.cpp)

add_example(examples_linked_lists
    src/data_structures/linked_lists/examples.cpp)

add_example(examples_stacks_queues
    src/data_structures/stacks_queues/examples.cpp)

add_example(examples_hash_tables
    src/data_structures/hash_tables/examples.cpp)

add_example(examples_trees
    src/data_structures/trees/examples.cpp)

add_example(examples_graphs
    src/data_structures/graphs/examples.cpp)

add_example(examples_heaps
    src/data_structures/heaps/examples.cpp)

add_example(examples_tries
    src/data_structures/tries/examples.cpp)

add_example(examples_union_find
    src/data_structures/union_find/examples.cpp)

add_example(examples_bit_manipulation
    src/data_structures/bit_manipulation/examples.cpp)

# ─── Algorithm Examples ───────────────────────────────────────────────────────
add_example(examples_sorting
    src/algorithms/sorting/examples.cpp)

add_example(examples_searching
    src/algorithms/searching/examples.cpp)

add_example(examples_dp
    src/algorithms/dynamic_programming/examples.cpp)

add_example(examples_greedy
    src/algorithms/greedy/examples.cpp)

add_example(examples_backtracking
    src/algorithms/backtracking/examples.cpp)

add_example(examples_two_pointers
    src/algorithms/two_pointers/examples.cpp)

# ─── Tests (Google Test) ──────────────────────────────────────────────────────
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
# Prevent overriding the parent project's compiler/linker settings (Windows)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_subdirectory(tests)

# ─── Print configuration summary ─────────────────────────────────────────────
message(STATUS "Build type:   ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler:     ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
