#include "../item/item.hpp"
#include "../item/lollipop.hpp"
#include <GL/glut.h>
namespace robot {
class hand {
  float points[8][3] = {{1, 1, 1},  {-1, 1, 1},  {1, 1, -1},  {-1, 1, -1},
                        {1, -1, 1}, {-1, -1, 1}, {1, -1, -1}, {-1, -1, -1}};
  int face[6][4] = {{0, 1, 3, 2}, {0, 1, 5, 4}, {0, 2, 6, 4},
                    {1, 3, 7, 5}, {2, 3, 7, 6}, {4, 5, 7, 6}};
  item::item *obj = nullptr;

public:
  void draw() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(1, 0, 0);
    for (int i = 0; i < 6; i++) {
      glBegin(GL_POLYGON);
      for (int j = 0; j < 4; j++) {
        glVertex3fv(points[face[i][j]]);
      }
      glEnd();
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0, 0, 0);
    glLineWidth(2);
    for (int i = 0; i < 6; i++) {
      glBegin(GL_LINE_LOOP);
      for (int j = 0; j < 4; j++) {
        glVertex3fv(points[face[i][j]]);
      }
      glEnd();
    }
    if (obj) {
      glPushMatrix();
      glTranslatef(0, 1, 0);
      obj->draw(0);
      glPopMatrix();
    }
  }
  void set_obj(item::item *obj) { this->obj = obj; }
  item::item *get_obj() { return obj; }
};

} // namespace robot