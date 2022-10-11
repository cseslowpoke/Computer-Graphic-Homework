#include "../paint.hpp"
#include <string>
#include <vector>
namespace paint {
    class Curve : public paints {
        std::vector<std::pair<int, int> > points;
        int mode = 0;
        float r = 0, g = 0, b = 0, linewidth = 1;
        public:
            Curve() {
                // TODO
            }
            void draw(int height, int width) {
                // if(points.size() <2) return;
                glColor3f(r, g, b);
                // glColor3f(1, 0.7, 0.7);
                glLineWidth(linewidth);
                glBegin(GL_LINE_STRIP);
                    for(auto point : points) {
                        glVertex2f(point.first,height - point.second);
                    }
                glEnd();
            }
            void insert(int x, int y) {
                points.push_back({x, y});
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
            Curve* clone() const{
                return new Curve(*this);
            }
            
    };
}
