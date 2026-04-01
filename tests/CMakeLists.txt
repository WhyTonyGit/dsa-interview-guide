add_executable(run_tests
    test_main.cpp
    test_arrays.cpp
    test_linked_lists.cpp
    test_trees.cpp
    test_graphs.cpp
)

target_include_directories(run_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(run_tests
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(run_tests)
