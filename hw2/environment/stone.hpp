#include <GL/glut.h>
#define max1(x, y) (((x) > (y) ? (x) : (y)))
#define min1(x, y) (((x) < (y) ? (x) : (y)))
namespace environment {
class stone {
  float point[8][3] = {{2, 0, 2},  {-2, 0, 2},  {2, 0, -2},  {-2, 0, -2},
                       {2, 10, 2}, {-2, 10, 2}, {2, 10, -2}, {-2, 10, -2}};
  int face[6][4] = {{0, 1, 3, 2}, {0, 1, 5, 4}, {0, 2, 6, 4},
                    {1, 3, 7, 5}, {2, 3, 7, 6}, {4, 5, 7, 6}};
  int x, y;

public:
  stone(int x, int y) {
    this->x = x;
    this->y = y;
  }
  void draw() {
    glPushMatrix();
    glTranslatef(x, 0, y);
    for (int i = 0; i < 6; i++) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glColor3f(0.7, 0.7, 0.7);

      glBegin(GL_POLYGON);
      glColor3f(0.8, 0.8, 0.8);
      for (int j = 0; j < 4; j++) {
        glVertex3fv(point[face[i][j]]);
      }
      glEnd();
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glColor3f(1.0, 0, 0);
      glLineWidth(2.5);
      glBegin(GL_POLYGON);
      glColor3f(0, 0, 1);
      for (int j = 0; j < 4; j++) {
        glVertex3fv(point[face[i][j]]);
      }
      glEnd();
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    glPopMatrix();
  }
  bool check(float x0, float y0, float x1, float y1) {
    if (max1(x0, x - 2) < min1(x1, x + 2) &&
        max1(y0, y - 2) < min1(y1, y + 2)) {
      return true;
    }
    return false;
  }
};
} // namespace environment