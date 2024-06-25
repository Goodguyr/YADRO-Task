enable_testing()

# Add a test executable
add_executable(TapeSorterTests
    test_main.cpp
    test_Tape.cpp
    # test_TapeSorter.cpp
    $<TARGET_OBJECTS:TapeSorterLib>
)

find_package(GTest REQUIRED)

target_link_libraries(TapeSorterTests gtest::gtest)

target_include_directories(TapeSorterTests PRIVATE ../include)

add_test(NAME TapeSorterTests COMMAND TapeSorterTests)
