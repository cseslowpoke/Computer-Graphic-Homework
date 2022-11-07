#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include "button.hpp"
#include "dragbar.hpp"
#include "menubar.hpp"
#include "preview_color.hpp"
#include "gridline.hpp"
#include "paint.hpp"
#include "paint/Line.hpp"
#include "paint/Curve.hpp"
#include "paint/Text.hpp"
#include "paint/Rectangle.hpp"
#include "paint/Polygon.hpp"
#include "paint/Circle.hpp"
#include "paint/Point.hpp"

#include <iostream>

using namespace std;

void init();
void display();
void mouse_func(int button, int state, int x, int y);
void mouse_routine(int x, int y) ;
void mouse_motion(int x, int y);
void reshape_func(int new_w, int new_h);
void init_menubar_button();
void keyboard_func(unsigned char key, int x, int y);
vector<button> buttons;
vector<dragbar> dragbars;
vector<vector<button> > menus;
vector<paint::paints*> paints;
vector<paint::paints*> copy_paints;
preview_color preview(450, 38, 75, 75);
paint::paints *now_paint = NULL;
int now_grid = 1;
int now_mode = GL_FILL;
float now_linewidth = 1;
bool is_Text = false;
bool is_polygon = false, now_polygon = false;
paint::Polygon *polygon = NULL;


int height = 1000, width = 1000;

int main(int argc, char *argv[]) {
  // Initialize GLUT
  glutInit(&argc, argv);
 
  // Set up some memory buffers for our display
  glutInitWindowPosition(0,0);
  glutInitWindowSize(1000, 700);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  init();
  
  init_menubar_button();
  /// Create window
  glutCreateWindow("Linux");
  
  // add callbacks
  glutDisplayFunc(display);
  glutMouseFunc(mouse_func);
  glutMotionFunc(mouse_motion);
  glutPassiveMotionFunc(mouse_routine);
  glutReshapeFunc(reshape_func);
  glutKeyboardFunc(keyboard_func);
  glutMainLoop();
  return 0;
}

void init() {
  glClearColor(1, 1, 1, 1);
  glReadBuffer(GL_FRONT);
  glDrawBuffer(GL_FRONT);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glMatrixMode(GL_PROJECTION);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
}

void reshape_func(int new_w, int new_h) {
  height = new_h;
  width = new_w;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, (double) width, 0.0, (double) height);
  glViewport(0, 0, width, height);
  glMatrixMode(GL_MODELVIEW);
  glutPostRedisplay();   /*---Trigger Display event for redisplay window*/
}

void display() {
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  if(now_grid) {
    girdline::draw(height, width);
  }
  float line_width_radio = dragbars[0].get_ratio();
  float r = dragbars[1].get_ratio();
  float g = dragbars[2].get_ratio();
  float b = dragbars[3].get_ratio();
  // cout << line_width_radio << " " << r << " " << g << " " << b << endl;
  now_linewidth = 10 * line_width_radio + 1 * (1 - line_width_radio);
  for(int i = 0; i < paints.size(); i++) {
    paints[i]->draw(height, width);
  }
  if(polygon != NULL) {
    polygon->set_mode(now_mode);
    polygon->set_color(r, g, b);
    polygon->set_width(now_linewidth);
    polygon->draw(height, width);
  }
  if(now_paint != NULL) {
    now_paint->set_mode(now_mode);
    now_paint->set_color(r, g, b);
    now_paint->set_width(now_linewidth);
    now_paint->draw(height, width);
  }
  menubar::draw(height, width);
  preview.set_color(r, g, b);
  preview.set_width(now_linewidth);
  preview.draw(height, width);
  for (auto i:dragbars) {
    i.draw(height, width);
  }
  for (int i = 0; i < buttons.size(); i++) {
    buttons[i].draw(height, width);
    if (buttons[i].get_pushed()) {
      for (int j = 0; j < menus[i].size(); j++) {
        menus[i][j].draw(height, width);
      }
    }
  }
  
  glFlush();
}
bool now_draw = false;
void mouse_motion(int x, int y) {
  if(is_polygon && now_polygon) {
    polygon->vir_insert(x, y);
    now_polygon = true;
  }
  if(now_paint != NULL && now_draw) {
    now_paint->insert(x, y);
  }
  for (auto &i:dragbars) {
    if(i.is_inside(x, y)) {
      i.set_middle(x);
    }
  }
  glutPostRedisplay();
}

button *current_button = NULL;
int current_menu = -1;

void mouse_func(int bt, int state, int x, int y) { 
  if (bt == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    for(int i = 0; i < buttons.size(); i++) {
      if (buttons[i].is_inside(x, y)) {
        buttons[i].set_pushed(1);
        current_button = &buttons[i];
        current_menu = i;
        glutPostRedisplay();
      }
      else {
        buttons[i].set_pushed(0);
      }
    }
    if(y > 120 && is_polygon) {
      polygon->vir_insert(x, y);
      now_polygon = true;
    }
    else if(y > 120 && now_paint != NULL) {
      
      now_paint->insert(x, y);
      now_draw = true;
    }
 }
  else if (bt == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    if (current_button != NULL) {
      for (int j = 0; j < menus[current_menu].size(); j++) {
        if (menus[current_menu][j].is_inside(x, y)) {
          menus[current_menu][j].call_func();
          current_button = NULL;
          current_menu = -1;
          break;
        }
      }
    }
    if(now_polygon) {
      polygon->insert(x, y);
      if(polygon->is_end()) {
        paints.push_back(polygon->clone());
        polygon = new paint::Polygon();
      }
      now_polygon = false;
    }
    else if(now_draw) {
      
      paints.push_back(now_paint->clone());
      now_paint->clear();
      now_draw = false;
    }
    if(now_paint != NULL) {
      now_paint->clear();
      
    }
  }
  glutPostRedisplay();
}

void mouse_routine(int x, int y) {
  if(y > 120) {
    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
  }
  else {
    glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
  }
  for(int i = 0; i < buttons.size(); i++) {
    if (buttons[i].get_pushed()) {
      for (int j = 0; j < menus[i].size(); j++) {
        if (menus[i][j].is_inside(x, y)) {
          menus[i][j].set_pushed(1);
        }
        else {
          menus[i][j].set_pushed(0); 
        }
      }
    }
    if (buttons[i].is_inside(x, y)) {
      buttons[i].set_mouseon(1);
    } else {
      buttons[i].set_mouseon(0);
    }
  }
  glutPostRedisplay();
}

void keyboard_func(unsigned char key, int x, int y) {
  if(key == 26) {
    if(paints.size() > 0) {
      paints.pop_back();
    }
  }
  if(y > 120 && is_Text) {
    paint::Text *text = new paint::Text();
    if('a' <= key <= 'z' || 'A' <= key <= 'Z' || '0' <= key <= '9') {
      text->set_text(key);
      text->set_color(dragbars[1].get_ratio(), dragbars[2].get_ratio(), dragbars[3].get_ratio());
      text->set_width(now_linewidth);
      text->set_mode(now_mode);
      text->insert(x, y);
      paints.push_back(text);
    }
  }
  glutPostRedisplay();
}
float about_w, about_h;
void about_display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1, 1, 1);
  glRasterPos2f(0, about_h / 2);
  string s = "Nothing in here :D";
  for (int i = 0; i < s.size(); i++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
  }
  glFlush();
}

void about_reshape(int new_w, int new_h) {
  about_w = new_w;
  about_h = new_h;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, (double) new_w, 0.0, (double) new_h);
  glViewport(0, 0, new_w, new_h);
  glMatrixMode(GL_MODELVIEW);
  glutPostRedisplay();   /*---Trigger Display event for redisplay window*/
}

void nothing() {
  return;
}
void init_menubar_button() {

  dragbar d1(100, 35, 100, 30, 0, "Line Width:");
  dragbar d2(100, 75, 100, 30, 1, "RGB RED:   ");
  dragbar d3(320, 35, 100, 30, 2, "RGB GREEN: ");
  dragbar d4(320, 75, 100, 30, 3, "RGB BLUE:  ");
  dragbars.push_back(d1);
  dragbars.push_back(d2);
  dragbars.push_back(d3);
  dragbars.push_back(d4);

  
  button b1(0, 0, 80, 30, "File", [](){});
  button b2(85, 0, 80, 30, "Type", [](){});
  button b3(170, 0, 80, 30, "Mode", [](){});
  button b4(255, 0, 80, 30, "Func", [](){});
  buttons.push_back(b1);
  buttons.push_back(b2);
  buttons.push_back(b3);
  buttons.push_back(b4);
  menus.resize(4);
  menus[0].push_back(button(0, 30, 120, 30, "New", [&]() {
    polygon = NULL;
    now_paint = NULL;
    is_polygon = false;
    now_polygon = false;
    paints.clear();
    glutPostRedisplay();
  }));
  menus[0].push_back(button(0, 60, 120, 30, "Save", [&](){}));
  menus[0].push_back(button(0, 90, 120, 30, "About", [&]() {
    glutInitWindowPosition(300, 300);
    glutInitWindowSize(300, 300);
    GLint attack = glutCreateWindow("about");
    glutDisplayFunc(about_display);
    glutReshapeFunc(about_reshape);
    glutCloseFunc(nothing);
  }));
  menus[1].push_back(button(85, 30, 120, 30, "Mouse", [&]() {
    is_polygon = false;
    now_polygon = false;
    now_paint = NULL;
    is_Text = false;
    polygon = NULL;
  }));
  menus[1].push_back(button(85, 60, 120, 30, "Text", [&]() {
    is_Text = true;
    
    now_paint = NULL;
    polygon = NULL;
    is_polygon = false;
    now_polygon = false;
    glutPostRedisplay();
  }));
  menus[1].push_back(button(85, 90, 120, 30, "Point", [&]() {
    is_Text = false;
    polygon = NULL;
    now_paint = new paint::Point();
    is_polygon = false;
    now_polygon = false;
    glutPostRedisplay();
  }));
  menus[1].push_back(button(85, 120, 120, 30, "Line", [&]() {
    is_Text = false;
    polygon = NULL;
    now_paint = new paint::Line();
    is_polygon = false;
    now_polygon = false;
    glutPostRedisplay();
  }));
  menus[1].push_back(button(85, 150, 120, 30, "Rectangle", [&]() {
    is_Text = false;
    polygon = NULL;
    now_paint = new paint::Rectangle();
    is_polygon = false;
    now_polygon = false;
    glutPostRedisplay();
  }));
  menus[1].push_back(button(85, 180, 120, 30, "Circle", [&]() {
    is_Text = false;
    polygon = NULL;
    now_paint = new paint::Circle();
    is_polygon = false;
    now_polygon = false;
    glutPostRedisplay();
  }));
  menus[1].push_back(button(85, 210, 120, 30, "Polygon", [&]() {
    is_Text = false;
    polygon = new paint::Polygon();
    now_paint = NULL;
    is_polygon = true;
    now_draw = false;
    glutPostRedisplay();
  }));
  menus[1].push_back(button(85, 240, 120, 30, "Curve", [&]() {
    is_Text = false;
    polygon = NULL;
    now_paint = new paint::Curve();
    is_polygon = false; 
    now_polygon = false;
    glutPostRedisplay();
  }));
  menus[2].push_back(button(170, 30, 120, 30, "Fill", [&]() {
    now_mode = GL_FILL;
  }));
  
  menus[2].push_back(button(170, 60, 120, 30, "Line", [&]() {
    now_mode = GL_LINE;
  }));

  menus[3].push_back(button(255, 30, 120, 30, "GridLine", [&](){
    now_grid = !now_grid;
  }));
  
  menus[3].push_back(button(255, 60, 120, 30, "Save Panel", [&](){
    copy_paints.clear();
    for(auto i:paints) {
      copy_paints.push_back(i->clone());
    }
  }));

  menus[3].push_back(button(255, 90, 120, 30, "Load Panel", [&](){
    paints.clear();
    for(auto i:copy_paints) {
      paints.push_back(i->clone());
    }
  }));
  
}


