#include "../Gundam/lower_arm.hpp"
#include "../Gundam/upper_arm.hpp"
#include "hand.hpp"
#include <GLUT/glut.h>
namespace robot {
class arm {
  float points[8][3] = {{0.7, 0.7, 3},   {0.7, -0.7, 3}, {-0.7, 0.7, 3},
                        {-0.7, -0.7, 3}, {0.7, 0.7, 0},  {0.7, -0.7, 0},
                        {-0.7, 0.7, 0},  {-0.7, -0.7, 0}};
  int face[6][4] = {{0, 1, 3, 2}, {0, 1, 5, 4}, {1, 3, 7, 5},
                    {4, 5, 7, 6}, {2, 3, 7, 6}, {0, 2, 6, 4}};
  hand handla;
  gundam::upper_arm gundam_upper_arm;
  gundam::lower_arm gundam_lower_arm;
  GLUquadricObj *sphere;

  int orz_type = 0;

public:
  void draw(int mode) {
    glPushMatrix();

    if (orz_type) {
      glRotated(mode ? -100 : 100, 0, 1, 0);
    }
    gundam_upper_arm.draw();
    glTranslated(0, 0, 2);
    if (orz_type) {
      glTranslated(mode ? 0.3 : -0.3, 0, 1);
      glRotated(mode ? -80 : 80, 0, 1, 0);
    }
    gundam_lower_arm.draw();

    glTranslated(0, 0, 5);
    handla.draw(mode);
    glPopMatrix();
  }
  void init() { sphere = gluNewQuadric(); }
  void set_obj(item::item *obj) { handla.set_obj(obj); }
  void set_orz_type() { orz_type = !orz_type; }
  item::item *get_grasp() { return handla.get_obj(); }
};
}; // namespace robot