#include<GL/glut.h>

namespace girdline{
    void draw(int height,int width) {
        glLineWidth(1);
                glColor3f(0.9, 0.9, 0.9);
                for(int i = 0; i <= width; i += 25) {
                    glBegin(GL_LINES);
                        glVertex2f(i, 0);
                        glVertex2f(i, height);
                    glEnd();
                }   
                for(int i = 5; i <= height; i += 25) {
                    glBegin(GL_LINES);
                        glVertex2f(0, i);
                        glVertex2f(width, i);
                    glEnd();
                }   
    }
}