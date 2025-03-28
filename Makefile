CXX = g++
CXXFLAGS = -std=c++20 -Wall -g
EXEC = watopoly-test
SOURCES = watopoly-display.cc GameBoard.cc test-watopoly.cc
OBJECTS = $(SOURCES:.cc=.o)
DEPENDS = $(SOURCES:.cc=.d)
LDFLAGS = -lX11

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC) $(LDFLAGS)

-include $(DEPENDS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@ -MMD

.PHONY: clean run

clean:
	rm -f $(OBJECTS) $(EXEC) $(DEPENDS)

run: $(EXEC)
	./$(EXEC).