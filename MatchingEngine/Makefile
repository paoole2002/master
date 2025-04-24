# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++14 -Wall -Wextra -Werror -Iinclude

# Precompiled header
PCH = include/pch.h
PCH_GCH = $(PCH).gch

# Source files
SRCS = $(wildcard source/*.cpp)

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = matching_engine

# Default target
all: $(EXEC)

# Build executable
$(EXEC): $(PCH_GCH) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to build the precompiled header
$(PCH_GCH): $(PCH)
	$(CXX) $(CXXFLAGS) -x c++-header $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(PCH_GCH)