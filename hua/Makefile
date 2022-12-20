CXX = gcc-12
CXXFLAGS = $(shell pkg-config --cflags glu gl glut) -Wall -O3
CXXLIBS = $(shell pkg-config --libs glu gl glut)

all: robot.cpp
	$(CXX) $(CXXFLAGS) -o robot.o robot.cpp $(CXXLIBS)
	./robot.o

clean:
	rm -rf *.o 

indent:
	@clang-format -i robot.cpp
	@clang-format -i robot/*.hpp
	@clang-format -i item/*.hpp
	@clang-format -i environment/*.hpp
	@clang-format -i Gundam/*.hpp