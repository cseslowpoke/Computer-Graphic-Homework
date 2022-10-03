
#include "../paint.hpp"

namespace paint {
    class Point : public paints {
        int x, y, mode;
        float r = 0, g = 0, b = 0;
        public:
            Point() {
                // TODO
            }
            void draw(int height, int width) {
                glColor3f(r, g, b);
                glBegin(GL_POINTS);
                    glVertex2i(x, height - y);
                glEnd();
            }
            void insert(int x, int y) {
                this->x = x;
                this->y = y;
            }
            void clear() {
                // TODO
            }
            void set_mode(int mode) {
                this->mode = mode;
            }
            void set_color(float r, float g, float b) {
                this->r = r;
                this->g = g;
                this->b = b;
            }
            void set_width(float width) {
                
            }
            Point* clone() const{
                return new Point(*this);
            }
    };
}
