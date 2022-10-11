#include<GL/glut.h>
#include<iostream>
#include<string>
class dragbar {
    float posX, posY;
    float width, height;
    float middle;
    float rgb1[3] = {0};
    float rgb2[3] = {0};
    std::string name;
    int color;
    public:
        dragbar(float posX, float posY, float width, float height, int color, std::string name) {
            this->posX = posX;
            middle = posX;
            this->posY = posY;
            this->width = width;
            this->height = height;
            this->color = color;
            this->name = name;
            switch (color)
            {
                case 0:
                    rgb1[0] = 0; rgb1[1] = 0; rgb1[2] = 0;
                    rgb2[0] = 0.5; rgb2[1] = 0.5; rgb2[2] = 0.5;
                    break;
                case 1:
                    rgb1[0] = 1; rgb1[1] = 0; rgb1[2] = 0;
                    rgb2[0] = 1; rgb2[1] = 0.7; rgb2[2] = 0.7;
                    break;
                case 2:
                    rgb1[0] = 0; rgb1[1] = 1; rgb1[2] = 0; 
                    rgb2[0] = 0.7; rgb2[1] = 1; rgb2[2] = 0.7;
                    break;
                case 3:
                    rgb1[0] = 0; rgb1[1] = 0; rgb1[2] = 1;
                    rgb2[0] = 0.7; rgb2[1] = 0.7; rgb2[2] = 1;
                    break;
            }
        }
        void draw(int screen_height, int screen_width) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glColor3f(rgb2[0], rgb2[1], rgb2[2]);
            glLineWidth(1);
            glBegin(GL_POLYGON);
                glVertex2f(posX, screen_height - posY);
                glVertex2f(posX + width, screen_height - posY);
                glVertex2f(posX + width, screen_height - (posY + height));
                glVertex2f(posX, screen_height - (posY + height));
            glEnd();
            glColor3f(rgb1[0], rgb1[1], rgb1[2]);
            glBegin(GL_POLYGON);
                glVertex2f(posX, screen_height - posY);
                glVertex2f(middle, screen_height - posY);
                glVertex2f(middle, screen_height - (posY + height));
                glVertex2f(posX, screen_height - (posY + height));
            glEnd();
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glColor3f(0, 0, 0);
            glBegin(GL_POLYGON);
                glVertex2f(posX, screen_height - posY);
                glVertex2f(posX + width, screen_height - posY);
                glVertex2f(posX + width, screen_height - (posY + height));
                glVertex2f(posX, screen_height - (posY + height));
            glEnd();
            glRasterPos2f(posX - 2 * name.length() - 77, screen_height - (posY + height / 2));
            for (int i = 0; i < name.length(); i++) {
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, name[i]);
            }
        }
        bool is_inside(int x, int y) {
            if (x >= posX && x <= posX + width && y >= posY && y <= posY + height) {
                // std::cout << x << ' ' << y << ' '<< color << '\n'
                return 1;
            }
            return 0;
        }   
        void set_middle(float middle) {
            this->middle = middle;
        }
        float get_ratio() {
            return (middle - posX) / width;
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
};