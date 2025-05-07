# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -std=c++11 -Wall -Wextra -I./tinyxml2

# Linker flags
LDFLAGS := -L./tinyxml2 -ltinyxml2 -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SRCS := test.cpp game.cpp player.cpp extractMatrix.cpp map.cpp bulletInteraction.cpp

# Object files
OBJS := $(SRCS:.cpp=.o)

# Executable name
TARGET := a

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
