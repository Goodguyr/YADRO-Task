add_library(TapeSorterLib OBJECT
    Setup.cpp
    Tape.cpp
    TapeSorter.cpp
)

# Add the executable for the main project
add_executable(TapeSorter
    main.cpp
    $<TARGET_OBJECTS:TapeSorterLib>
)

target_include_directories(TapeSorter PRIVATE ../include)

