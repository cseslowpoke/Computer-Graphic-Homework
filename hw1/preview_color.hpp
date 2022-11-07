#include<GL/glut.h>
#include<cmath>
class preview_color {
    float posX, posY;
    float width, height;
    float rgb[3] = {0}, linewidth;
    public:
        preview_color(float posX, float posY, float width, float height) {
            this->posX = posX;
            this->posY = posY;
            this->width = width;
            this->height = height;
        }
        void draw(int screen_height, int screen_width) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glColor3f(rgb[0], rgb[1], rgb[2]);
            glBegin(GL_POLYGON);
                int x = posX;
                int y = posY;
                int x1 = posX + width;
                int y1 = posY + height;
                int middlex = (x + x1) / 2;
                int middley = (y + y1) / 2;
                int ar = abs(x - x1) / 2;
                int br = abs(y - y1) / 2;
                for(int i = 0; i < 720; i++) {
                    float theta = (double)2.0 * acos(-1) * float(i) / float(720);
                    float x = ar * cosf(theta);
                    float y = br * sinf(theta);
                    glVertex2f(x + middlex, screen_height - (y + middley));
                }
            glEnd();
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glLineWidth(linewidth);
            glColor3f(0, 0, 0);
            glBegin(GL_POLYGON);
                for(int i = 0; i < 720; i++) {
                    float theta = (double)2.0 * acos(-1) * float(i) / float(720);
                    float x = ar * cosf(theta);
                    float y = br * sinf(theta);
                    glVertex2f(x + middlex, screen_height - (y + middley));
                }
            glEnd();
        }
        void set_color(float r, float g, float b) {
            rgb[0] = r;
            rgb[1] = g;
            rgb[2] = b;
        }
        void set_width(float width) {
            this->linewidth = width;
        }
};
    