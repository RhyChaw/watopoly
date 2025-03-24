CXX = g++
CXXFLAGS = -std=c++20 -Wall -g
EXEC = display
SOURCES = Display.cc
OBJECTS = $(SOURCES:.cc=.o)
DEPENDS = $(SOURCES:.cc=.d)

$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC) -lX11

-include $(DEPENDS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@ -MMD

.PHONY: clean

clean:
	rm -f $(OBJECTS) $(EXEC) $(DEPENDS)