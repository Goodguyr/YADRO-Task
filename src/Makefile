# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
# Source directories
SRCDIRS = tape algorithms config
# Source files
SRCS = $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.cpp)) main.cpp
# Object files
OBJS = $(SRCS:.cpp=.o)
# Executable name
TARGET = tapeSorter

# Default target
all: $(TARGET)
	rm -f $(OBJS)

# Linking rule
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compilation rule for source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET) input.txt output.txt
