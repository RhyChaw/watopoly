CXX = g++
CXXFLAGS = -std=c++20 -Wall -O -g -MMD -Werror=vla # Use -MMD to generate dependencies

# Only compile Player.cc
SOURCES = Player.cc
OBJECTS = $(SOURCES:.cc=.o)
DEPENDS = $(OBJECTS:.o=.d)
EXEC = player_test  # Name of the output executable

# Default target: Compile Player.cc
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)

# Compile .cc to .o
%.o: %.cc Player.h
	$(CXX) -c -o $@ $< $(CXXFLAGS) 

-include $(DEPENDS)

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(DEPENDS) $(EXEC)
