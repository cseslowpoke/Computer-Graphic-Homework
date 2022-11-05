CXX = gcc-12
CXXFLAGS = $(shell pkg-config --cflags glu gl glut) -Wall 
CXXLIBS = $(shell pkg-config --libs glu gl glut)
NAME = wind_mill
# all: cubes.c
# 	$(CXX) $(CXXFLAGS) -o cubes cubes.c $(CXXLIBS)
all: $(NAME).c
	$(CXX) $(CXXFLAGS) -o $(NAME) $(NAME).c $(CXXLIBS)
	./$(NAME)

.PHONY: clean
clean:
	rm -rf *.o cubes