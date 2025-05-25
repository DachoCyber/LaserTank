CXX := g++


CXXFLAGS := -std=c++14 -Wall -Wextra -I./tinyxml2


LDFLAGS := -L./tinyxml2 -ltinyxml2 -lsfml-graphics -lsfml-window -lsfml-system


SRCS := test.cpp game.cpp player.cpp extractMatrix.cpp map.cpp bulletInteraction.cpp playerInteraction.cpp


OBJS := $(SRCS:.cpp=.o)

TARGET := a

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
