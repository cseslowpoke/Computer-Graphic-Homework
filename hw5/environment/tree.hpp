#include "../texture/texture.hpp"
#include <GL/glut.h>
#include <chrono>
#include <iostream>
namespace environment {
class tree {
  texture::Texture texture[98];
  int w = 30, h = 30;
  int select = 0;
  vector<pair<int, int>> pos;
  std::chrono::steady_clock::time_point last_time;
  // std::chrono::steady_clock::now();
public:
  void init() {
    for (int i = 1; i <= 98; i++) {
      //  texture[i - 1].load("0032.bmp");
      texture[i - 1].load(("tree/" + to_string(i) + ".bmp").c_str());
    }
    last_time = std::chrono::steady_clock::now();
    for(int i = 0; i < 5; i++) {
      pos.push_back({rand() % 61, rand() % 45 - 30});
    }
  }

  void draw(float a1, float a3) {
    // cerr << "?";
    if (std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::steady_clock::now() - last_time)
            .count() > 100000) {
      select = (select + 1) % 98;
      last_time = std::chrono::steady_clock::now();
    }
     float mat[3]; // material
      mat[0] = 0.0;
      mat[1] = 0.0;
      mat[2] = 0.0;
      mat[3] = 1.0;
      glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
      mat[0] = 1;
      mat[1] = 1;
      mat[2] = 1;
      glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
      mat[0] = 0.0;
      mat[1] = 0.0;
      mat[2] = 0.0;
      glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
      glMaterialf(GL_FRONT, GL_SHININESS, 0.0);
    for (auto i : pos) {
      glPushMatrix();
      // glutWireCube(10);
      glTranslated(i.first, 0, i.second);
      float v0[3] = {-a1 * w / 2, -5, -a3 * w / 2};
      float v1[3] = {a1 * w / 2, -5, a3 * w / 2};
      float v2[3] = {a1 * w / 2, h-5, a3 * w / 2};
      float v3[3] = {-a1 * w / 2, h-5, -a3 * w / 2};
      glEnable(GL_TEXTURE_2D);
      glEnable(GL_ALPHA_TEST);
      glAlphaFunc(GL_GREATER, 0.5);
      texture[select].bind();
      glBegin(GL_POLYGON);
      glTexCoord2f(1, 1);
      glVertex3fv(v0);
      glTexCoord2f(0, 1);
      glVertex3fv(v1);
      glTexCoord2f(0, 0);
      glVertex3fv(v2);
      glTexCoord2f(1, 0);
      glVertex3fv(v3);
      glEnd();
      texture[select].unbind();
      glDisable(GL_ALPHA_TEST);
      glDisable(GL_TEXTURE_2D);
      glPopMatrix();
    }
  }
};
} // namespace environment