#pragma once
#include "../Gundam/torso.hpp"
#include "../item/item.hpp"
#include "arm.hpp"
#include "head.hpp"
#include "leg.hpp"
#include <GL/glut.h>
namespace robot {
class torso {
  float points[8][3] = {{2, 4, 1},  {-2, 4, 1},  {2, 4, -1},  {-2, 4, -1},
                        {2, -4, 1}, {-2, -4, 1}, {2, -4, -1}, {-2, -4, -1}};
  int face[6][4] = {{0, 1, 3, 2}, {0, 1, 5, 4}, {0, 2, 6, 4},
                    {1, 3, 7, 5}, {2, 3, 7, 6}, {4, 5, 7, 6}};

  arm left_arm, right_arm;
  leg left_leg, right_leg;
  head myhead;
  gundam::torso gundam_torso;

  float walk = 45;
  int jump = 0;
  float turn = 45;
  int orz_type = 0;
  void rightarm() {
    glPushMatrix();
    glTranslatef(3.5, 3, 0);
    glRotated(90, 0, 1, 0);
    glRotated(85, 1, 0, 0);
    if (walk <= 90) {
      glRotated(walk - 45, 0, 1, 0);
    } else {
      glRotated(-(45 - (180 - walk)), 0, 1, 0);
    }
    right_arm.draw(1);
    glPopMatrix();
  }

  void leftarm() {

    glPushMatrix();
    glTranslatef(-3.5, 3, 0);
    glRotated(-90, 0, 1, 0);
    glRotated(85, 1, 0, 0);
    if (walk <= 90) {
      glRotated(walk - 45, 0, 1, 0);
    } else {
      glRotated(-(45 - (180 - walk)), 0, 1, 0);
    }
    left_arm.draw(0);
    glPopMatrix();
  }

  void rightleg() {
    glPushMatrix();
    glTranslatef(1, -4, 0);
    glRotated(180, 1, 0, 0);
    if (orz_type) {
      glRotated(-80, 1, 0, 0);
    }
    glRotated(-10, 0, 0, 1);
    if (walk <= 90) {
      glRotated(30 * float(45 - walk) / 45, 1, 0, 0);
      right_leg.set_walk(45 - walk);
    } else {
      glRotated(30 * float(walk - 135) / 45, 1, 0, 0);
      right_leg.set_walk(walk - 135);
    }

    if (turn <= 90) {
      glRotated(5 * -float(turn - 45) / 45, 1, 0, 0);
    } else {
      glRotated(5 * float(45 - (180 - turn)) / 45, 1, 0, 0);
    }

    if (0 < jump && jump <= 1000) {
      glRotated(-45 * (float)jump / 1000, 1, 0, 0);
    } else if (1000 < jump && jump <= 2000) {
      glRotated(-45 * (float)(2000 - jump) / 1000, 1, 0, 0);
    }
    if (6000 < jump && jump <= 7000) {
      glRotated(-30 * (float)(jump - 6000) / 1000, 1, 0, 0);
    } else if (7000 < jump && jump <= 8000) {
      glRotated(-30 * (float)(8000 - jump) / 1000, 1, 0, 0);
    }

    right_leg.set_jump(jump);
    right_leg.draw(1);
    glPopMatrix();
  }

  void leftleg() {
    glPushMatrix();
    glTranslatef(-1, -4, 0);
    glRotated(180, 1, 0, 0);
    if (orz_type) {
      glRotated(-80, 1, 0, 0);
    }
    glRotated(10, 0, 0, 1);
    if (walk <= 90) {
      glRotated(30 * float(walk - 45) / 45, 1, 0, 0);
      left_leg.set_walk(walk - 45);
    } else {
      glRotated(30 * float(-(walk - 135)) / 45, 1, 0, 0);
      left_leg.set_walk(-(45 - (180 - walk)));
    }

    if (turn <= 90) {
      glRotated(5 * float(turn - 45) / 45, 1, 0, 0);
    } else {
      glRotated(5 * float(-(45 - (180 - turn))) / 45, 1, 0, 0);
    }

    if (0 < jump && jump <= 1000) {
      glRotated(-45 * (float)jump / 1000, 1, 0, 0);
    } else if (1000 < jump && jump <= 2000) {
      glRotated(-45 * (float)(2000 - jump) / 1000, 1, 0, 0);
    } else if (6000 < jump && jump <= 7000) {
      glRotated(-30 * (float)(jump - 6000) / 1000, 1, 0, 0);
    } else if (7000 < jump && jump <= 8000) {
      glRotated(-30 * (float)(8000 - jump) / 1000, 1, 0, 0);
    }

    left_leg.set_jump(jump);
    left_leg.draw(0);
    glPopMatrix();
  }

  void ohead() {
    glPushMatrix();
    glTranslatef(0, 4, 0);
    glRotated(-90, 1, 0, 0);
    myhead.draw();
    glPopMatrix();
  }

public:
  void init() {
    left_arm.init();
    right_arm.init();
    left_leg.init();
    right_leg.init();
    myhead.init();
  }

  void draw() {
    glPushMatrix();
    if (walk <= 90) {
      glTranslatef(0, -1.4 * ((float)abs(walk - 45) / 45), 0);
    } else {
      glTranslatef(0, -1.4 * ((float)abs(walk - 135) / 45), 0);
    }
    if (0 < jump && jump <= 1000) {
      glTranslatef(0, -2.63 * (float)jump / 1000, 0);
    } else if (1000 < jump && jump <= 2000) {
      glTranslatef(0, -2.63 * (float)(2000 - jump) / 1000, 0);
    } else if (2000 < jump && jump <= 4000) {
      glTranslatef(0,
                   10 * float(jump - 2000) / 2000 -
                       0.5 * 9.8 * float(jump - 2000) / 2000 *
                           float(jump - 2000) / 2000,
                   0);
    } else if (4000 < jump && jump <= 6000) {
      glTranslatef(0,
                   5.1 - 0.5 * 9.8 * float(jump - 4000) / 2000 *
                             float(jump - 4000) / 2000,
                   0);
    } else if (6000 < jump && jump <= 7000) {
      glTranslatef(0, -2.63 * (float)(jump - 6000) / 1000, 0);
    } else if (7000 < jump && jump <= 8000) {
      glTranslatef(0, -2.63 * (float)(8000 - jump) / 1000, 0);
    }
    if (orz_type) {
      glTranslated(0, -7.5, 0);
      glRotated(90, 1, 0, 0);
    }
    gundam_torso.draw();
    // glColor3f(0, 1, 0);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
    //   glBegin(GL_POLYGON);
    //   for (int j = 0; j < 4; j++) {
    //     glVertex3fv(points[face[i][j]]);
    //   }
    //   glEnd();
    // }
    rightarm();
    leftarm();
    rightleg();
    leftleg();
    ohead();
    glPopMatrix();
  }
  void draw_light() {
    glPushMatrix();
    if (walk <= 90) {
      glTranslatef(0, -1.4 * ((float)abs(walk - 45) / 45), 0);
    } else {
      glTranslatef(0, -1.4 * ((float)abs(walk - 135) / 45), 0);
    }
    if (0 < jump && jump <= 1000) {
      glTranslatef(0, -2.63 * (float)jump / 1000, 0);
    } else if (1000 < jump && jump <= 2000) {
      glTranslatef(0, -2.63 * (float)(2000 - jump) / 1000, 0);
    } else if (2000 < jump && jump <= 4000) {
      glTranslatef(0,
                   10 * float(jump - 2000) / 2000 -
                       0.5 * 9.8 * float(jump - 2000) / 2000 *
                           float(jump - 2000) / 2000,
                   0);
    } else if (4000 < jump && jump <= 6000) {
      glTranslatef(0,
                   5.1 - 0.5 * 9.8 * float(jump - 4000) / 2000 *
                             float(jump - 4000) / 2000,
                   0);
    } else if (6000 < jump && jump <= 7000) {

      glTranslatef(0, -2.63 * (float)(jump - 6000) / 1000, 0);
    } else if (7000 < jump && jump <= 8000) {
      glTranslatef(0, -2.63 * (float)(8000 - jump) / 1000, 0);
    }
    if (orz_type) {
      glTranslated(0, -7.5, 0);
      glRotated(90, 1, 0, 0);
    }
    gundam_torso.draw_light();
    glPopMatrix();
  }
  void walk_forward() {
    walk = walk + 0.02;
    if (walk > 180) {
      walk = 0;
    }
  }
  void walk_backward() {
    walk = walk - 0.02;
    if (walk < 0) {
      walk = 180;
    }
  }
  void turn_right() {
    turn = turn + 0.1;
    if (turn > 180) {
      turn = 0;
    }
  }
  void turn_left() {
    turn = turn - 0.1;
    if (turn < 0) {
      turn = 180;
    }
  }
  float get_walk(void) { return walk; }
  void set_jump(int j) { jump = j; }
  void grasp_item_left(item::item *it) { left_arm.set_obj(it); }
  item::item *get_grasp_left(void) { return left_arm.get_grasp(); }
  void grasp_item_right(item::item *it) { right_arm.set_obj(it); }
  item::item *get_grasp_right(void) { return right_arm.get_grasp(); }
  void orz() {
    orz_type = !orz_type;
    right_leg.set_orz_type();
    left_leg.set_orz_type();
    right_arm.set_orz_type();
    left_arm.set_orz_type();
  }
};
}; // namespace robot