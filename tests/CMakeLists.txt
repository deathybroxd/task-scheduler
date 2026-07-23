add_executable(scheduler_tests
    TestDependencyGraph.cpp
    TestEDFScheduler.cpp
    
)

target_link_libraries(scheduler_tests PRIVATE scheduler_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(scheduler_tests)