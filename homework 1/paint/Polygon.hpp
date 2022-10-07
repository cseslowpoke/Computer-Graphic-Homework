#include "../paint.hpp"
#include <vector>
#include <cmath>
namespace paint {
    class Polygon : public paints {
        int mode, virX, virY;
        
        float r, g, b, linewidth;
        bool end = false;
        public:
            std::vector<std::pair<int, int> > points;
            Polygon() {
                // TODO
            }
            void draw(int height, int width) {
                glPolygonMode(GL_FRONT_AND_BACK, mode);
                glLineWidth(linewidth);
                glColor3f(r, g, b);
                if(!end) {
                    glBegin(GL_LINE_STRIP);
                        for(auto point : points) {
                            glVertex2f(point.first,height - point.second);
                        }
                        if(virX != -1 && virY != -1) {
                            glVertex2f(virX,height - virY);
                        }
                    glEnd();
                }
                else {
                    glBegin(GL_POLYGON);
                        for(auto point : points) {
                            glVertex2f(point.first,height - point.second);
                        }
                    glEnd();
                }
            }
            void vir_insert(int x, int y) {
                if(points.size() == 0) {
                    insert(x, y);
                }
                else {
                    virX = x;
                    virY = y;
                }
            }

            void insert(int x, int y) {
                virX = -1;
                virY = -1;
                if(!points.size()) {
                    points.push_back({x, y});
                    return;
                }
                if(fabs(points[0].first - x) < 10 && fabs(points[0].second - y) < 10) {
                    end = true;
                }
                else {
                    points.push_back({x, y});
                }
            }
            void clear() {
                points.clear();
                end = false;
            }
            bool is_end() {
                return end;
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
            Polygon* clone() const{
                return new Polygon(*this);
            }
    };
}
