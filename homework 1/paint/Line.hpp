#include "../paint.hpp"
#include <GL/glut.h>
#include <vector>
namespace paint {
    class Line : public paints {
        std::vector<std::pair<int, int>> points;
        int mode;
        float r = 0, g = 0, b = 0, linewidth = 1;
        public:
            Line(){};
            void draw(int height, int width) {
                glColor3f(r, g, b);
                glLineWidth(linewidth);
                glBegin(GL_LINES);
                    for (int i = 0; i < points.size(); i++) {
                        glVertex2f(points[i].first,height- points[i].second);
                    }
                glEnd();
            }
            void insert(int x, int y) {
                if (points.size() == 2) {
                    points.pop_back();
                }
                points.push_back(std::make_pair(x, y));
            }
            void clear() {
                points.clear();
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
            Line* clone() const{
                return new Line(*this);
            }
    };
}
