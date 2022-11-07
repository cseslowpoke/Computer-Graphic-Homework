#include "../paint.hpp"
namespace paint {
    class Text : public paints {
        int mode;
        float r = 0, g = 0, b = 0, linewidth = 1;
        int posX, posY;
        unsigned char text;
        public:
            Text() {
                // TODO
            }
            void draw(int height, int width) {
                glColor3f(r, g, b);
                glLineWidth(linewidth);
                glRasterPos2f(posX, height - posY);
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text);
            }
            void insert(int x, int y) {
                posX = x;
                posY = y;
            }
            void clear() {

            }
            void set_text(unsigned char text) {
                this->text = text;
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
                linewidth = width;   
            }
            Text* clone() const{
                return new Text(*this);
            }
            
    };
}