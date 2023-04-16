add_executable(runMessagingTests runMessagingTests.cpp testMessage.cpp)


target_compile_features(runMessagingTests PRIVATE cxx_std_17)


target_link_libraries(runMessagingTests PRIVATE messages) # GTest::gtest_main)

# include(GoogleTest)
#gtest_discover_tests(tests)