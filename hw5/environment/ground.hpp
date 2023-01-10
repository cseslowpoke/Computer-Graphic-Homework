#include "../texture/texture.hpp"
#include <GL/glut.h>
namespace environment {
namespace ground {

float point[8][3] = {{0, -20, -30}, {60, -20, -30}, {60, 0, -30}, {0, 0, -30},
                     {0, -20, 30},  {60, -20, 30},  {60, 0, 30},  {0, 0, 30}};
int face[6][4] = {{0, 3, 2, 1}, {0, 1, 5, 4}, {1, 2, 6, 5},
                  {4, 5, 6, 7}, {2, 3, 7, 6}, {0, 4, 7, 3}};

float normal[6][3];

int tex[4][2] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
texture::Texture texture;
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
  texture.load("texture/marble.bmp");
}

void draw() {
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
    glMaterialf(GL_FRONT, GL_SHININESS, 0);
    glEnable(GL_TEXTURE_2D);
    texture.bind();
    glNormal3fv(normal[i]);
    glBegin(GL_POLYGON);
    for (int j = 0; j < 4; j++) {
      glTexCoord2f(tex[j][0], tex[j][1]);
      glVertex3fv(point[face[i][j]]);
    }
    glEnd();
    texture.unbind();
    glDisable(GL_TEXTURE_2D);
  }
}
}; // namespace ground
}; // namespace environment