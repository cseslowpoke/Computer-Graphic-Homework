cmake_minimum_required(VERSION 3.23)
project(cghw1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lopengl32 -lglu32 -lfreeglut")
set(CMAKE_CXX_STANDARD 17)


# link_directories(/opt/homebrew/include)
# include_directories(/opt/homebrew/lib)
find_path(/opt/homebrew/include GL/glut.h /opt/homebrew/lib)

add_executable(cghw1 main.cpp)

find_package(freeglut)
target_link_libraries(cghw1 freeglut)


