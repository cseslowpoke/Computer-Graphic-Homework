CXX = g++-12
CXXFLAGS = $(shell pkg-config --cflags glu glut) -Wall 
CXXLIBS = $(shell pkg-config --libs glu glut)
all: main.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp $(CXXLIBS)

.PHONY: clean
clean:
	rm -rf *.o main