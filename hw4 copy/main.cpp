/*---------------------------------------------------------------------------------
 * This file contains a program, drawing & animating a wind-mill.
 * This program is used to teach LCS and scene graph concepts.
 *
 * by S. K. Ueng, Nov.  2006
 */
#include "./debug/debug.hpp"
#include "./environment/init.hpp"
#include "./robot/robot.hpp"
#include <GLUT/glut.h>
#include <math.h>

#include <chrono>
#include <thread>

/*-----Define window size----*/
int width = 700, height = 700;
int back = 1;
int zoom = 5;
enum PROJECTION_MODE { OrthoX, OrthoY, OrthoZ, Perspective, FOURPRO };
PROJECTION_MODE style = Perspective;
// Global variables recording rotation angles of H-arm and blades.

/* define light state*/
int light0_state = 1;
int light1_state = 1;
int light2_state = 1;

void myinit() {
  glClearColor(0.3, 0.3, 0.3, 0.5); /*set the background color BLACK */
                                    /*Clear the Depth & Color Buffers */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glShadeModel(GL_SMOOTH);
  /*-----Set a parallel projection mode-----*/
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-40.0, 40.0, -40, 40, 0.0, 120.0);
  glEnable(GL_DEPTH_TEST); /*Enable depth buffer for shading computing */
  glEnable(GL_NORMALIZE);  /*Enable mornalization  */
  glEnable(GL_BLEND);      /*Enable blending */
  // glEnable(GL_CULL_FACE);
  // glEnable
  // glCullFace(GL_BACK);
  // glEnable(GL_CULL_FACE);
  cv = cos(5.0 * PI / 180.0);
  sv = sin(5.0 * PI / 180.0);
  glFlush(); /*Enforce window system display the results*/
}

/*-------------------------------------------------------
 * Display and Idle callback func. This func. draws three
 * cubes at proper places to simulate a solar system.
 */
float cx = 0, cy = 0, cz = 0;
int pers_zoom = 90;
int parl_zoom = 100;
void make_view(int mode) {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  switch (mode) {
  case 4: /* Perspective */
    gluLookAt(eye[0], eye[1], eye[2], eye[0] - u[2][0], eye[1] - u[2][1],
              eye[2] - u[2][2], u[1][0], u[1][1], u[1][2]);
    break;
  case 1: /* X direction parallel viewing */
    gluLookAt(30.0, 0.0, 10, 0.0, 0.0, 10, 0.0, 1.0, 0.0);
    break;
  case 2: /* Y direction parallel viewing */
    gluLookAt(20, 30.0, 0.0, 20, 0.0, 0.0, 1.0, 0.0, 0.0);
    break;
  case 3:
    gluLookAt(20, 0.0, 30.0, 20, 0.0, 0.0, 0.0, 1.0, 0.0);
    break;
  }
}

void make_projection(int x) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (x == 4) {
    gluPerspective(pers_zoom, (double)width / (double)height, zoom, 75);
    // glFrustum(-5* (float)height / (float)width,5* (float)height /
    // (float)width,-5,5,5,75);
  } else {
    if (width > height)
      glOrtho(-40.0 * parl_zoom / 100, 40.0 * parl_zoom / 100,
              -40.0 * (float)height / (float)width * parl_zoom / 100,
              40.0 * (float)height / (float)width * parl_zoom / 100, -0.0, 100);
    else
      glOrtho(-40.0 * (float)width / (float)height * parl_zoom / 100,
              40.0 * (float)width / (float)height * parl_zoom / 100,
              -40.0 * parl_zoom / 100, 40.0 * parl_zoom / 100, -0.0, 100);
  }
  glMatrixMode(GL_MODELVIEW);
}

void draw_style(PROJECTION_MODE style, int x, int y, int width, int height) {
  switch (style) {
  case OrthoX:
    make_view(1);
    make_projection(1);
    break;
  case OrthoY:
    make_view(2);
    make_projection(2);
    break;
  case OrthoZ:
    make_view(3);
    make_projection(3);
    break;
  case Perspective:
    make_view(4);
    make_projection(4);
    break;
  }
  glViewport(x, y, width, height);
  environment::draw_light0();
  if (light2_state) {
    robot::draw_light();
  }
  environment::draw();
  robot::draw();
}

void display() {
  /*Clear previous frame and the depth buffer */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /*----Define the current eye position and the eye-coordinate system---*/

  switch (style) {
  case OrthoX:
    draw_style(OrthoX, 0, 0, width, height);
    break;
  case OrthoY:
    draw_style(OrthoY, 0, 0, width, height);
    break;
  case OrthoZ:
    draw_style(OrthoZ, 0, 0, width, height);
    break;
  case Perspective:
    draw_style(Perspective, 0, 0, width, height);
    break;
  case FOURPRO:
    draw_style(OrthoX, 0, height / 2, width / 2, height / 2);
    draw_style(OrthoY, width / 2, height / 2, width / 2, height / 2);
    draw_style(OrthoZ, 0, 0, width / 2, height / 2);
    draw_style(Perspective, width / 2, 0, width / 2, height / 2);
    break;
  }
  // gluLookAt(view_x, view_y, view_z, robot::get_x(), robot::get_y(),
  // robot::get_z(), 0.0, 1.0, 0.0);
  /*----Draw the ground----*/

  // draw_axes();
  /*-------Swap the back buffer to the front --------*/
  glutSwapBuffers();
  glFlush(); /*--Display the results----*/
}

/*--------------------------------------------------
 * Reshape callback function which defines the size
 * of the main window when a reshape event occurrs.
 */
// void my_reshape(int w, int h) {
//   width = w;
//   height = h;

//   glMatrixMode(GL_PROJECTION);
//   glViewport(0, 0, w, h);
//   glLoadIdentity();
//   if (w > h)
//     glOrtho(-15.0, 15.0, -15.0 * (float)h / (float)w,
//             15.0 * (float)h / (float)w, -10.5, 30.0);
//   else
//     glOrtho(-15.0 * (float)w / (float)h, 15.0 * (float)w / (float)h, -15.0,
//             15.0, -10.5, 30.0);
// }

void my_reshape(int w, int h) {
  width = w;
  height = h;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, w, h);
  glOrtho(-40.0, 40.0, -40, 40, 0.0, 120.0);
  // make_projection(style);
}
/*--------------------------------------------------
 * Keyboard callback func. When a 'q' key is pressed,
 * the program is aborted.
 */
void my_keyboard(unsigned char key, int one, int two) {
  int i;
  float x[3], y[3], z[3];
  if (key == 'a') {
    robot::turn_left();
  } else if (key == 'd') {
    robot::turn_right();
  } else if (key == 'w') {
    // robot::set_z(robot::get_z() + 0.5);
    robot::walk_forward();
  } else if (key == 's') {
    // robot::set_z(robot::get_z() - 0.5);
    robot::walk_backward();
  } else if (key == 'j') {
    robot::jump();
  } else if (key == 'k') {
    robot::knee_down();
  } else if (key == 'f') {
    robot::grasp_or_drop_left();
  } else if (key == 'r') {
    robot::grasp_or_drop_right();
  } else if (key == 'o') {
    robot::orz();
  } else if (key == 'c') {
    style = PROJECTION_MODE(style + 1);
    if (style == 5) {
      style = OrthoX;
    }
  } else if (key == 'x') {
    back = -back;
  } else if (key == '+') {
    pers_zoom--;
    pers_zoom = max1(pers_zoom, 45);
    parl_zoom--;
    parl_zoom = max1(parl_zoom, 55);
  } else if (key == '-') {
    pers_zoom++;
    pers_zoom = min1(pers_zoom, 135);
    parl_zoom++;
    parl_zoom = min1(parl_zoom, 145);
  } else if (key == '1') {
    eyeDy += 0.5; /* move up */
    for (i = 0; i < 3; i++)
      eye[i] -= 0.5 * u[1][i];
  } else if (key == '!') {
    eyeDy += -0.5; /* move down */
    for (i = 0; i < 3; i++)
      eye[i] += 0.5 * u[1][i];
  } else if (key == '2') {
    eyeDx += -0.5; /* move left */
    for (i = 0; i < 3; i++)
      eye[i] += 0.5 * u[0][i];
  } else if (key == '@') {
    eyeDx += 0.5; /* move right */
    for (i = 0; i < 3; i++)
      eye[i] -= 0.5 * u[0][i];
  } else if (key == '3') {
    eyeDz += 0.5; /* zoom in */
    for (i = 0; i < 3; i++)
      eye[i] -= 0.5 * u[2][i];
  } else if (key == '#') {
    eyeDz += -0.5; /* zoom out */
    for (i = 0; i < 3; i++)
      eye[i] += 0.5 * u[2][i];
  } else if (key == '4') {
    eyeAngx += 5.0;
    if (eyeAngx > 360.0)
      eyeAngx -= 360.0;
    y[0] = u[1][0] * cv - u[2][0] * sv;
    y[1] = u[1][1] * cv - u[2][1] * sv;
    y[2] = u[1][2] * cv - u[2][2] * sv;

    z[0] = u[2][0] * cv + u[1][0] * sv;
    z[1] = u[2][1] * cv + u[1][1] * sv;
    z[2] = u[2][2] * cv + u[1][2] * sv;

    for (i = 0; i < 3; i++) {
      u[1][i] = y[i];
      u[2][i] = z[i];
    }
  } else if (key == '$') {
    eyeAngx += -5.0;
    if (eyeAngx < 0.0)
      eyeAngx += 360.0;
    y[0] = u[1][0] * cv + u[2][0] * sv;
    y[1] = u[1][1] * cv + u[2][1] * sv;
    y[2] = u[1][2] * cv + u[2][2] * sv;

    z[0] = u[2][0] * cv - u[1][0] * sv;
    z[1] = u[2][1] * cv - u[1][1] * sv;
    z[2] = u[2][2] * cv - u[1][2] * sv;

    for (i = 0; i < 3; i++) {
      u[1][i] = y[i];
      u[2][i] = z[i];
    }
  } else if (key == '5') {
    eyeAngy += 5.0;
    if (eyeAngy > 360.0)
      eyeAngy -= 360.0;
    for (i = 0; i < 3; i++) {
      x[i] = cv * u[0][i] - sv * u[2][i];
      z[i] = sv * u[0][i] + cv * u[2][i];
    }
    for (i = 0; i < 3; i++) {
      u[0][i] = x[i];
      u[2][i] = z[i];
    }
  } else if (key == '%') {
    eyeAngy += -5.0;
    if (eyeAngy < 0.0)
      eyeAngy += 360.0;
    for (i = 0; i < 3; i++) {
      x[i] = cv * u[0][i] + sv * u[2][i];
      z[i] = -sv * u[0][i] + cv * u[2][i];
    }
    for (i = 0; i < 3; i++) {
      u[0][i] = x[i];
      u[2][i] = z[i];
    }
  } else if (key == '6') {
    eyeAngz += 5.0;
    if (eyeAngz > 360.0)
      eyeAngz -= 360.0;
    for (i = 0; i < 3; i++) {
      x[i] = cv * u[0][i] - sv * u[1][i];
      y[i] = sv * u[0][i] + cv * u[1][i];
    }
    for (i = 0; i < 3; i++) {
      u[0][i] = x[i];
      u[1][i] = y[i];
    }
  } else if (key == '^') {
    eyeAngz += -5.0;
    if (eyeAngz < 0.0)
      eyeAngz += 360.0;
    for (i = 0; i < 3; i++) {
      x[i] = cv * u[0][i] + sv * u[1][i];
      y[i] = -sv * u[0][i] + cv * u[1][i];
    }
    for (i = 0; i < 3; i++) {
      u[0][i] = x[i];
      u[1][i] = y[i];
    }
  } else if (key == '7') {
    if (light0_state) {
      glDisable(GL_LIGHT0);
    } else {
      glEnable(GL_LIGHT0);
    }
    light0_state = !light0_state;
  } else if (key == '&') {
    environment::light::lit0_pos();
  } else if (key == '8') {
    environment::light::lit0_color();
  } else if (key == '*') {
    environment::light::lit0_intensity();
  } else if (key == '9') {
    if (light1_state) {
      glDisable(GL_LIGHT1);
    } else {
      glEnable(GL_LIGHT1);
    }
    light1_state = !light1_state;
  } else if (key == '(') {

  } else if (key == '0') {
    if (light2_state) {
      glDisable(GL_LIGHT2);
      glDisable(GL_LIGHT3);
    } else {
      glEnable(GL_LIGHT2);
      glEnable(GL_LIGHT3);
    }
    light2_state = !light2_state;
  } else if (key == ')') {

  } else if (key == '[') {
    environment::light::lit1_color();
  } else if (key == '{') {
    environment::light::lit1_intensity();
  } else if (key == ']') {
    environment::light::lit2_angle();
  } else if (key == '}') {
    environment::light::lit2_intensity();
  }
  display();
  // std::cerr << glutGetModifiers() << ' ' << key << '\n';;
}

/*---------------------------------------------
 * Idle event callback function, increase blade and arm
 * rotation angles.
 */
int times = 0;
void idle_func() {
  display(); /* show the scene again */
  // std::this_thread::sleep_for(std::chrono::milliseconds(20));
}

void init() {
  robot::init(25, 13, 10);
  environment::init();
}
/*---------------------------------------------------
 * Main procedure which defines the graphics environment,
 * the operation style, and the callback func's.
 */

int main(int argc, char **argv) {

  /*-----Initialize the GLUT environment-------*/
  glutInit(&argc, argv);

  /*-----Depth buffer is used, be careful !!!----*/
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(width, height);
  glutCreateWindow("robot");

  myinit(); /*---Initialize other state varibales----*/
  init();
  /*----Associate callback func's whith events------*/
  glutDisplayFunc(display);
  glutIdleFunc(idle_func); /* Add idle event */
  glutReshapeFunc(my_reshape);
  glutKeyboardFunc(my_keyboard);
  // glutKeyboardUpFunc([](unsigned char key, int x, int y){
  //   std::cerr << "?";
  // });
  glutMainLoop();
}