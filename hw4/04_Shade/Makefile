CXX = gcc-12
CXXFLAGS = $(shell pkg-config --cflags glu gl glut) -Wall 
CXXLIBS = $(shell pkg-config --libs glu gl glut)

shade: 
	$(CXX) $(CXXFLAGS) -o main.o shade.c $(CXXLIBS)
	@./main.o
light: 
	$(CXX) $(CXXFLAGS) -o main.o light.c $(CXXLIBS)
	@./main.o

clean:
	rm -rf *.o 

indent:
	@clang-format -i main.cpp
	@clang-format -i robot/*.hpp
	@clang-format -i item/*.hpp
	@clang-format -i environment/*.hpp
	@clang-format -i Gundam/*.hpp