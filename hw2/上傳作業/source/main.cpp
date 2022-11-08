/*---------------------------------------------------------------------------------
 * This file contains a program, drawing & animating a wind-mill.
 * This program is used to teach LCS and scene graph concepts.
 *
 * by S. K. Ueng, Nov.  2006
 */
#include "./environment/init.hpp"
#include <math.h>
#include "./robot/robot.hpp"
#include <GL/glut.h>

/*-----Define window size----*/
int width = 1024, height = 1024;

// Global variables recording rotation angles of H-arm and blades.

/*----------------------------------------------------------
 * Procedure to initialize the working environment.
 */
void myinit() {
  glClearColor(0.3, 0.3, 0.3, 0.5); /*set the background color BLACK */
                                    /*Clear the Depth & Color Buffers */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glViewport(0, 0, width, height);

  /*-----Set a parallel projection mode-----*/
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-40.0, 40.0, -40, 40, 0.0, 120.0);

  glEnable(GL_DEPTH_TEST); /*Enable depth buffer for shading computing */

  glFlush(); /*Enforce window system display the results*/
}

/*-------------------------------------------------------
 * Display and Idle callback func. This func. draws three
 * cubes at proper places to simulate a solar system.
 */
float view_x = 45.0, view_y = 75.0, view_z = 55.0;

void display() {
  /*Clear previous frame and the depth buffer */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /*----Define the current eye position and the eye-coordinate system---*/
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(view_x, view_y, view_z, 25.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  // gluLookAt(view_x, view_y, view_z, robot::get_x(), robot::get_y(),
  // robot::get_z(), 0.0, 1.0, 0.0);
  /*----Draw the ground----*/
  environment::draw();
  // glScaled(0.5, 0.5, 0.5);
  robot::draw();
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

//   glViewport(0, 0, w, h);

//   glMatrixMode(GL_PROJECTION);
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
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-40.0, 40.0, -40, 40, 0.0, 120.0);
}
/*--------------------------------------------------
 * Keyboard callback func. When a 'q' key is pressed,
 * the program is aborted.
 */
void my_keyboard(unsigned char key, int x, int y) {
  if (key == '1') {
    view_x += 5;
  } else if (key == '2') {
    view_x -= 5;
  } else if (key == '3') {
    view_y += 5;
  } else if (key == '4') {
    view_y -= 5;
  } else if (key == '5') {
    view_z += 5;
  } else if (key == '6') {
    view_z -= 5;
  } else if (key == 'a') {
    robot::turn_left();
  } else if (key == 'd') {
    robot::turn_right();
  } else if (key == 'W' && glutGetModifiers() == GLUT_ACTIVE_SHIFT) {

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
  }
  display();
  // std::cerr << glutGetModifiers() << ' ' << key << '\n';;
}

/*---------------------------------------------
 * Idle event callback function, increase blade and arm
 * rotation angles.
 */
int times = 0;
void idle_func() { display(); /* show the scene again */ }

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
  glutMainLoop();
}