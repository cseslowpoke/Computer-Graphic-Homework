CXX = gcc-12
CXXFLAGS = $(shell pkg-config --cflags glu gl glut) -Wall 
CXXLIBS = $(shell pkg-config --libs glu gl glut)

all: main.c
	$(CXX) $(CXXFLAGS) -o main main.c $(CXXLIBS)

# .PHONY: clean
clean:
	rm -rf *.o main