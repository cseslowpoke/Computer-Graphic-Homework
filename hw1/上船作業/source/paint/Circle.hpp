#include "../paint.hpp"
#include <vector>
#include <string>
#include <GL/glut.h>
#include <cmath>

namespace paint {
    class Circle : public paints {
        int mode = 0;
        std::vector<std::pair<int, int> > points;
        float r = 0, g = 0, b = 0, linewidth;
        public:
            Circle() {
                // TODO
            }
            
            void draw(int height, int width) {
                if(points.size() != 2) return;
                glColor3f(r, g, b);
                glLineWidth(linewidth);
                glPolygonMode(GL_FRONT_AND_BACK, mode);
                glBegin(GL_POLYGON);
                    int x = points[0].first;
                    int y = points[0].second;
                    int x1 = points[1].first;
                    int y1 = points[1].second;
                    int middlex = (x + x1) / 2;
                    int middley = (y + y1) / 2;
                    int ar = abs(x - x1) / 2;
                    int br = abs(y - y1) / 2;
                    for(int i = 0; i < 720; i++) {
                        float theta = (double)2.0 * acos(-1) * float(i) / float(720);
                        float x = ar * cosf(theta);
                        float y = br * sinf(theta);
                        glVertex2f(x + middlex, height - (y + middley));
                    }
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
            Circle* clone() const{
                return new Circle(*this);
            }
    };
}

