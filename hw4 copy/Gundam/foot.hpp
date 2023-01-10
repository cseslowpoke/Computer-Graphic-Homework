
#include "allmaterial.hpp"
#include <GLUT/glut.h>
#include <cmath>
namespace gundam {
class foot {
  float point[36][3] = {{1.3, 0, 1.3},   {1.3, 0, -1.3},   {-1.3, 0, -1.3},
                        {-1.3, 0, 1.3},  {1.3, 0.5, -2.6}, {-1.3, 0.5, -2.6},
                        {1.3, 0.5, 2.6}, {-1.3, 0.5, 2.6}, {1.3, 1, -2.6},
                        {-1.3, 1, -2.6}, {1.3, 1, 2.6},    {-1.3, 1, 2.6}};
  int face[10][4] = {{0, 1, 2, 3}, {1, 2, 5, 4},   {0, 3, 7, 6},
                     {0, 1, 4, 6}, {2, 3, 7, 5},   {6, 7, 11, 10},
                     {4, 5, 9, 8}, {8, 9, 11, 10}, {4, 6, 10, 8},
                     {5, 7, 11, 9}};
  GLUquadricObj *cylinder = gluNewQuadric();
  GLUquadricObj *sphere = gluNewQuadric();
  float normal[10][3];

public:
  foot() {
    gluQuadricDrawStyle(cylinder, GLU_FILL);
    gluQuadricNormals(cylinder, GLU_SMOOTH);
    gluQuadricTexture(cylinder, GL_TRUE);
    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    gluQuadricTexture(sphere, GL_TRUE);
    for (int i = 0; i < 10; i++) {
      // find cross product of two vectors
      float v1[3] = {point[face[i][1]][0] - point[face[i][0]][0],
                     point[face[i][1]][1] - point[face[i][0]][1],
                     point[face[i][1]][2] - point[face[i][0]][2]};
      float v2[3] = {point[face[i][2]][0] - point[face[i][0]][0],
                     point[face[i][2]][1] - point[face[i][0]][1],
                     point[face[i][2]][2] - point[face[i][0]][2]};
      float cross[3] = {v1[1] * v2[2] - v1[2] * v2[1],
                        v1[2] * v2[0] - v1[0] * v2[2],
                        v1[0] * v2[1] - v1[1] * v2[0]};
      normal[i][0] = cross[0];
      normal[i][1] = cross[1];
      normal[i][2] = cross[2];
    }
  }
  void draw() {
    glPushMatrix();

    green_material();
    for (int i = 0; i < 10; i++) {
      glNormal3fv(normal[i]);
      glBegin(GL_POLYGON);
      for (int j = 0; j < 4; j++) {
        glVertex3fv(point[face[i][j]]);
      }
      glEnd();
    }
    glPopMatrix();
  }
};
} // namespace gundam
