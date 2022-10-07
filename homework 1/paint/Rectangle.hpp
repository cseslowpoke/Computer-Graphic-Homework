#include "../paint.hpp"
#include <vector>

namespace paint {
    class Rectangle : public paints {
        std::vector<std::pair<int, int>> points;
        int mode;
        float r = 0, g = 0, b = 0, linewidth = 1;
        public:
            Rectangle() {
                // TODO
            }
            void draw(int height, int width) {
                if(points.size() != 2) return;
                glColor3f(r, g, b);
                glLineWidth(linewidth);
                glPolygonMode(GL_FRONT_AND_BACK, mode);
                glBegin(GL_POLYGON);
                    glVertex2i(points[0].first, height - points[0].second);
                    glVertex2i(points[1].first, height - points[0].second);
                    glVertex2i(points[1].first, height - points[1].second);
                    glVertex2i(points[0].first, height - points[1].second);
                glEnd();
            }
            void insert(int x, int y) {
                if(points.size() == 2) {
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
            Rectangle* clone() const{
                return new Rectangle(*this);
            }
    };
}