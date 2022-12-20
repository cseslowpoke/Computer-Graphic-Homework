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
float point[8][3] = {{-10, -20, -15}, {60, -20, -15}, {60, 0, -15},
                     {-10, 0, -15},   {-10, -20, 30}, {60, -20, 30},
                     {60, 0, 30},     {-10, 0, 30}};
int face[6][4] = {{0, 3, 2, 1}, {0, 1, 5, 4}, {1, 2, 6, 5},
                  {4, 5, 6, 7}, {2, 3, 7, 6}, {0, 4, 7, 3}};

float normal[6][3];

void init() {
  for (int i = 0; i < 6; i++) {
    float v1[3] = {point[face[i][1]][0] - point[face[i][0]][0],
                   point[face[i][1]][1] - point[face[i][0]][1],
                   point[face[i][1]][2] - point[face[i][0]][2]};
    float v2[3] = {point[face[i][2]][0] - point[face[i][0]][0],
                   point[face[i][2]][1] - point[face[i][0]][1],
                   point[face[i][2]][2] - point[face[i][0]][2]};
    normal[i][0] = v1[1] * v2[2] - v1[2] * v2[1];
    normal[i][1] = v1[2] * v2[0] - v1[0] * v2[2];
    normal[i][2] = v1[0] * v2[1] - v1[1] * v2[0];
  }
}

void draw() {
  // glLoadIdentity();
  for (int i = 0; i < 6; i++) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    float mat[3]; // material
    mat[0] = 0.0;
    mat[1] = 0.0;
    mat[2] = 0.0;
    mat[3] = 1.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
    mat[0] = 0.55;
    mat[1] = 0.55;
    mat[2] = 0.55;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
    mat[0] = 0.25;
    mat[1] = 0.25;
    mat[2] = 0.25;
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
    glMaterialf(GL_FRONT, GL_SHININESS, 0 * 128.0);
    // glColor3f(0.7, 0.7, 0.7);

    glBegin(GL_POLYGON);
    // glColor3f(0.8, 0.8, 0.8);
    for (int j = 0; j < 4; j++) {
      glVertex3fv(point[face[i][j]]);
    }
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glColor3f(1.0, 0, 0);
    glLineWidth(3.5);
    glBegin(GL_POLYGON);
    // glColor3f(0, 0, 1);
    for (int j = 0; j < 4; j++) {
      glVertex3fv(point[face[i][j]]);
    }
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}
}; // namespace ground
}; // namespace environment