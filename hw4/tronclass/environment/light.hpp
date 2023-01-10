namespace environment {
namespace light {
float litp = 0;
float lit_position[] = {0, 1, 0, 0};

float litx = 0.5, lity = 0.5, litz = 0.5;
float litd = 0;
float lit_diffuse[] = {0.5, 0.5, 0.5, 1.0};

float lits = 0;
float lit_specular[] = {0.7, 0.7, 0.7, 1.0};

float lit1_position[] = {0, 20, 0, 1.0};

float lit1x = 0.5, lit1y = 0.8, lit1z = 0.9;
float lit1d = 0, lit1s = 0;
float lit1_diffuse[] = {0.5, 0.8, 0.9, 1.0};

float lit2x = 0.8, lit2y = 0.4, lit2z = 0;
float lit2s = 0;
float lit2a = 30;
float lit2_diffuse[] = {0.8, 0.4, 0, 1.0};
float lit2_cutoff = 60;
float lit2_exponent = 0;

float global_ambient[] = {0.2, 0.2, 0.2, 1.0};
float lit_angle = 0.0;
void init() {
  glEnable(GL_LIGHTING); /*Enable lighting effects */
  glEnable(GL_LIGHT0);   /*Turn on light0 */
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
  glEnable(GL_LIGHT3);

  glLightfv(GL_LIGHT0, GL_DIFFUSE, lit_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, lit_specular);

  glLightfv(GL_LIGHT1, GL_DIFFUSE, lit1_diffuse);
  glLightfv(GL_LIGHT1, GL_SPECULAR, lit_specular);

  glLightfv(GL_LIGHT2, GL_DIFFUSE, lit2_diffuse);
  glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, lit2_cutoff);
  glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, lit2_exponent);

  glLightfv(GL_LIGHT3, GL_DIFFUSE, lit2_diffuse);
  glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, lit2_cutoff);
  glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, lit2_exponent);

  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);    /* local viewer */
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient); /*global ambient*/
}

void draw() {
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lit_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, lit_specular);

  glLightfv(GL_LIGHT1, GL_DIFFUSE, lit1_diffuse);
  glLightfv(GL_LIGHT1, GL_SPECULAR, lit_specular);

  glLightfv(GL_LIGHT2, GL_DIFFUSE, lit2_diffuse);
  glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, lit2_cutoff);
  glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, lit2_exponent);

  glLightfv(GL_LIGHT3, GL_DIFFUSE, lit2_diffuse);
  glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, lit2_cutoff);
  glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, lit2_exponent);

  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);    /* local viewer */
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient); /*global ambient*/
}

void lit0_pos() {
  litp += 10;
  lit_position[0] = 10 * cos(litp * 3.1415926 / 180);
  lit_position[1] = 10 * sin(litp * 3.1415926 / 180);
}

void lit0_color() {
  litd += 10;
  litx = rand() % 100 / 100.0;
  lity = rand() % 100 / 100.0;
  litz = rand() % 100 / 100.0;
  lit_diffuse[0] = litx * (abs(lits - 200) / 200);
  lit_diffuse[1] = lity * (abs(lits - 200) / 200);
  ;
  lit_diffuse[2] = litz * (abs(lits - 200) / 200);
  ;
}

void lit0_intensity() {
  lits += 10;
  if (lits >= 400)
    lits = 0;
  lit_diffuse[0] = litx * (abs(lits - 200) / 200);
  lit_diffuse[1] = lity * (abs(lits - 200) / 200);
  lit_diffuse[2] = litz * (abs(lits - 200) / 200);
}

void lit1_color() {
  lit1d += 10;
  lit1x = rand() % 100 / 100.0;
  lit1y = rand() % 100 / 100.0;
  lit1z = rand() % 100 / 100.0;
  lit1_diffuse[0] = lit1x * (abs(lit1s - 200) / 200);
  lit1_diffuse[1] = lit1y * (abs(lit1s - 200) / 200);
  ;
  lit1_diffuse[2] = lit1z * (abs(lit1s - 200) / 200);
  ;
}

void lit1_intensity() {
  lit1s += 10;
  if (lit1s >= 400)
    lit1s = 0;
  lit1_diffuse[0] = lit1x * (abs(lit1s - 200) / 200);
  lit1_diffuse[1] = lit1y * (abs(lit1s - 200) / 200);
  lit1_diffuse[2] = lit1z * (abs(lits - 200) / 200);
}

void lit2_intensity() {
  lit1s += 10;
  if (lit1s >= 400)
    lit1s = 0;
  lit2_diffuse[0] = lit2x * (abs(lit1s - 200) / 200);
  lit2_diffuse[1] = lit2y * (abs(lit1s - 200) / 200);
  lit2_diffuse[2] = lit2z * (abs(lit1s - 200) / 200);
}

void lit2_angle() {
  lit2a += 10;
  if (lit2a >= 150)
    lit2a = 0;
  lit2_cutoff = abs(lit2a - 75) + 15;
}

void draw_light0() {
  glPushMatrix();
  glLightfv(GL_LIGHT0, GL_POSITION, lit_position);
  glPopMatrix();
}

void draw_light1() {
  /*----position light1 (fixed) in eye coord sys ---*/
  glPushMatrix();
  glLightfv(GL_LIGHT1, GL_POSITION,
            lit1_position); /*fixed position in eye space---*/
  /*---draw the light source ---*/
  glTranslatef(lit1_position[0], lit1_position[1], lit1_position[2]);
  glDisable(GL_LIGHTING);
  glColor4f(0, 0.25, 0.4, 0.5);
  glutSolidSphere(2.5, 12, 12);
  glEnable(GL_LIGHTING);
  glPopMatrix();
}
} // namespace light
} // namespace environment