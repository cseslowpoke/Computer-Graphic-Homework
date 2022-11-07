CXX = g++
CXXFLAGS = $(shell pkg-config --cflags glu gl glut) -Wall 
CXXLIBS = $(shell pkg-config --libs glu gl glut)

all: main.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp $(CXXLIBS)

.PHONY: clean
clean:
	rm -rf *.o main