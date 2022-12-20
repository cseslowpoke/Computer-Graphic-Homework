#include <GL/glut.h>

namespace environment {
namespace ground {
// float point[][3] = {
//     {-10, 0, -10},
//     {10, 0, -10},
//     {10, 0, 10},
//     {-10, 0, 10},
//     {-10, -20, -10},
//     {10, -20, -10},
//     {10, -20, 10},
//     {-10, -20, 10},
// };
float point[][3] = {{-10, -20, -15}, {60, -20, -15}, {60, 0, -15},
                    {-10, 0, -15},   {-10, -20, 30}, {60, -20, 30},
                    {60, 0, 30},     {-10, 0, 30}};
int face[][4] = {{0, 3, 2, 1}, {0, 1, 5, 4}, {1, 2, 6, 5},
                 {4, 5, 6, 7}, {2, 3, 7, 6}, {0, 4, 7, 3}};
void draw() {
  // glLoadIdentity();
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
    glLineWidth(3.5);
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 1);
    for (int j = 0; j < 4; j++) {
      glVertex3fv(point[face[i][j]]);
    }
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}
}; // namespace ground
}; // namespace environment