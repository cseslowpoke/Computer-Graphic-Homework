#include <GL/glut.h>
#include <vector>
#include <string>
#include <iostream>
#include "define.hpp"
#include <functional>
class button{
    float posX, posY;
    float width, height;
    bool mouseon, pushed;
    std::string name;
    std::function<void()> func;
    public:
        button(float posX, float posY, float width, float height, std::string name, std::function<void()> func) {
            this->posX = posX;
            this->posY = posY;
            this->width = width;
            this->height = height;
            this->name = name;
            this->func = func;
            mouseon = 0;
            pushed = 0;
        }
        void draw(int screen_height, int screen_width) {
            glLineWidth(1);
            glColor3f(((mouseon || pushed) ? 0.5 : 0.7),((mouseon || pushed) ? 0.5 : 0.7),((mouseon || pushed) ? 0.5 : 0.7));
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glBegin(GL_POLYGON);
                glVertex2f(posX, screen_height - posY);
                glVertex2f(posX + width, screen_height - posY);
                glVertex2f(posX + width, screen_height -  posY -height);
                glVertex2f(posX, screen_height - posY - height);
            glEnd();
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glColor3f(0.3, 0.3, 0.3);
            glBegin(GL_POLYGON);
                glVertex2f(posX, screen_height - posY);
                glVertex2f(posX + width, screen_height - posY);
                glVertex2f(posX + width, screen_height -  posY - height + 1);
                glVertex2f(posX, screen_height - posY - height + 1);
            glEnd();
            glColor3f(0, 0, 0);
            glRasterPos2f(posX + width / 5 - name.length(), screen_height - posY - height / 2);
            for (int i = 0; i < name.length(); i++) {
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, name[i]);
            }
        }
        bool is_inside(int x, int y) {
            if (x >= posX && x <= posX + width && y >= posY && y <= posY + height) {
                return 1;
            }
            return 0;
        }
        void set_mouseon(bool boolean) {
            mouseon = boolean;
        }
        bool get_mouseon() {
            return mouseon;
        }
        void set_pushed(bool boolean) {
            pushed = boolean;
        }
        bool get_pushed() {
            return pushed;
        }
        float get_posX() {
            return posX;
        }
        float get_posY() {
            return posY;
        }
        float get_width() {
            return width;
        }
        float get_height() {
            return height;
        }
        void set_func(std::function<void()> func) {
            this->func = func;
        }
        void call_func() {
            func();
        }
};