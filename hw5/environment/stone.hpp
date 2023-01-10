#include "../texture/texture.hpp"
#include <GL/glut.h>
#define max1(x, y) (((x) > (y) ? (x) : (y)))
#define min1(x, y) (((x) < (y) ? (x) : (y)))
using namespace std;
namespace environment {
class stone {
  float point[8][3] = {{3, 0, 3},  {-3, 0, 3},  {3, 0, -3},  {-3, 0, -3},
                       {3, 30, 3}, {-3, 30, 3}, {3, 30, -3}, {-3, 30, -3}};
  int face[6][4] = {{0, 1, 3, 2}, {0, 1, 5, 4}, {0, 2, 6, 4},
                    {1, 3, 7, 5}, {2, 3, 7, 6}, {4, 5, 7, 6}};

  float normal[6][3];
  int tex[4][2] = {{0, 0}, {1, 0}, {1, 15}, {0, 15}};
  int x, y;
  texture::Texture texture;

public:
  stone(int x, int y) {
    this->x = x;
    this->y = y;
    for (int i = 0; i < 6; i++) {
      float v2[3] = {point[face[i][1]][0] - point[face[i][0]][0],
                     point[face[i][1]][1] - point[face[i][0]][1],
                     point[face[i][1]][2] - point[face[i][0]][2]};
      float v1[3] = {point[face[i][2]][0] - point[face[i][0]][0],
                     point[face[i][2]][1] - point[face[i][0]][1],
                     point[face[i][2]][2] - point[face[i][0]][2]};
      normal[i][0] = v1[1] * v2[2] - v1[2] * v2[1];
      normal[i][1] = v1[2] * v2[0] - v1[0] * v2[2];
      normal[i][2] = v1[0] * v2[1] - v1[1] * v2[0];
    }
  }
  void init() { texture.load("texture/blackmarble.bmp"); }
  void draw() {
    glPushMatrix();
    glTranslatef(x, 0, y);
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
      mat[0] = 0.0;
      mat[1] = 0.0;
      mat[2] = 0.0;
      glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
      glMaterialf(GL_FRONT, GL_SHININESS, 0.0);
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