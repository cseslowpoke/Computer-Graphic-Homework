#include "../Gundam/hand.hpp"
#include "../item/item.hpp"
#include "../item/lollipop.hpp"
#include <GLUT/glut.h>
namespace robot {
class hand {
  float points[8][3] = {{0.7, 0.7, 0.7},   {-0.7, 0.7, 0.7},  {0.7, 0.7, -0.7},
                        {-0.7, 0.7, -0.7}, {0.7, -0.7, 0.7},  {-0.7, -0.7, 0.7},
                        {0.7, -0.7, -0.7}, {-0.7, -0.7, -0.7}};
  int face[6][4] = {{0, 1, 3, 2}, {0, 1, 5, 4}, {0, 2, 6, 4},
                    {1, 3, 7, 5}, {2, 3, 7, 6}, {4, 5, 7, 6}};
  item::item *obj = nullptr;
  gundam::hand gundam_hand;

public:
  void draw(int mode) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // glColor3d(0.07450980392, 0.39215686274, 0.31764705882);
    // draw_axes();
    // for (int i = 0; i < 6; i++) {
    //   glBegin(GL_POLYGON);
    //   for (int j = 0; j < 4; j++) {
    //     glVertex3fv(points[face[i][j]]);
    //   }
    //   glEnd();
    // }
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glColor3f(0, 0, 0);
    // glLineWidth(2);
    // for (int i = 0; i < 6; i++) {
    //   glBegin(GL_LINE_LOOP);
    //   for (int j = 0; j < 4; j++) {
    //     glVertex3fv(points[face[i][j]]);
    //   }
    //   glEnd();
    // }
    gundam_hand.draw(mode, (obj) != NULL);
    if (obj) {
      glPushMatrix();
      glTranslated(0, 0, 1.3);
      if (mode) {
        glRotated(180, 0, 1, 0);
      }
      // glTranslatef(0, 1, 0);
      obj->draw(0);
      glPopMatrix();
    }
  }

  void set_obj(item::item *obj) { this->obj = obj; }
  item::item *get_obj() { return obj; }
};

} // namespace robot