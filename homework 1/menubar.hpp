#include<GL/glut.h>
#include<iostream>
namespace menubar {
    void draw(int height, int width) {
        glLineWidth(1);
        glColor3f(0.7, 0.7, 0.7);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBegin(GL_POLYGON);
            glVertex2f(0, height - 30);
            glVertex2f(width, height - 30);
            glVertex2f(width, height - 0);
            glVertex2f(0, height - 0);
        glEnd();
        glColor3f(0.9, 0.9, 0.9);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBegin(GL_POLYGON);
            glVertex2f(0, height - 120);
            glVertex2f(width, height - 120);
            glVertex2f(width, height - 30);
            glVertex2f(0, height - 30);
        glEnd();
    }
}