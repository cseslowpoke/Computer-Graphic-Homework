#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
// Define polygon drwaing models, filled or outlined.
#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

#define FILL 1
#define LINE 2

#define LEFT 1
#define RIGHT 2

#define LEFT_UP 0
#define LEFT_DOWN 1
#define RIGHT_UP 2
#define RIGHT_DOWN 3

#define table_width 15.0
#define table_length 25.0
#define table_thickness 1.5
#define table_height 4.0
#define table_feet_width 1

#define TRUE 1
#define FALSE 0

#define BIG 1
#define SMALL 0

#define STEP_MOD 10
#define TOTAL_STEP_MOD 209
#define PI acos(-1.0)

/* window shape */
int width = 700, height = 700;
// declare the rotational angle.
float rot_ang[3] = {0, 0, 0};
float left_thigh_ang = 0;
float right_thigh_ang = 0;

float left_calf_ang = 0;
float right_calf_ang = 0;

float left_arm_ang = 0;
float right_arm_ang = 0;

float left_forearm_ang = 0;
float right_forearm_ang = 0;

float left_feet_ang = 0;
float right_feet_ang = 0;

float left_hand_ang = 0;
float right_hand_ang = 0;

// Quodri objects for drawing the world coordinate system.
/*-----Define GLU quadric objects, a sphere and a cylinder----*/
GLUquadricObj *sphere = NULL, *cylind = NULL, *mycircle = NULL;

// setting
int polygonMode = FILL;
int view_mode = 0;
int thigh_state = 0;
float head_ang=0;
float walk_state_ang[8][4] = {{0, 0, 0, 0}, {5, 0, 0, -50}, {-15, 0, 45, -50}, {-20, 0, 45, -20}, {0, -50, 5, 0}, {45, -50, -15, 0}, {45, -20, -20, 0}, {5, 0, 0, -50}}; // 左大左小右大右小
float walk_state_time[9] = {0, 3, 9, 18, 24, 27, 33, 42, 48};
float walk_hand_state[8] = {0, 1, 1, 2, 3, 3, 0, 0};
float walk_hand_state_ang[4][4] = {{0, 15, 0, 15}, {18, 25, -18, 25}, {0, 15, 0, 15}, {-18, 25, 18, 25}};
float walk_cnt = 5;
float turn_feet_state_time[4] = {0, 4, 8, 12};
float turn_feet_state_ang[4][4] = {{0, 0, 0, 0}, {10, -10, 0, 0}, {0, 0, 0, 0}, {0, 0, 10, -10}};
float turn_cnt = 0;
float jump_feet_state_time[7] = {0, 64, 128, 230, 332, 396, 460};
float jump_time_slice = 3.0 / 204;
float jump_feet_state_ang[7][5] = {{0, 0, 0, 0, 0}, {-5, -1.5, 70, -90, 20}, {0, 0, 0, 0, 0}, {0, 11.025, 0, 0, 0}, {0, 0, 0, 0, 0}, {-5, -1.5, 70, -90, -90}, {0, 0, 0, 0, 0}}; // 前傾,y座標,大腿,小腿,腳掌
float jump_cnt = 0;
float sayhi_state_time[7] = {0, 128, 212, 296, 380, 474, 592};
float sayhi_state_ang[7][3] = {{0, 0, 0}, {175, 0, 50}, {175, -60, 56}, {175, 0, 50}, {175, -60, 56}, {175, 0, 50}, {0, 0, 0}}; // left_arm,left_forearm,tpang
float sayhi_cnt = 0;
int sayhi = FALSE;
int take_coffee = FALSE;
int table_coffee = TRUE;
float robot_range = 4.5;
int watch_mode = BIG;
int coffee_overthrow = FALSE;
int coffee_onfloor = FALSE;
int step_on_coffee = FALSE;
float coffee_onfloor_info[6] = {0.0};    // cos,sin,ang,x,y,z
float step_on_coffee_info[6][6] = {0.0}; // cos,sin,ang,x,y,z
int idx_cnt = -1;
int step_cnt = 0;
int view_volume = FALSE;

// pos
float robot_pos[3] = {10.0, 0.0, 10.0};
float view_pos[3][9] = {{79.000000, 23.000000, 25.000000, -170.000000, 9.000000, 35.000000, 0.000000, 1.000000, 0.000000},
                        {88.000000, 26.000000, 77.000000, -170.000000, -65.000000, -144.000000, 0.000000, 1.000000, 0.000000},
                        {85.000000, 55.000000, 79.000000, -170.000000, -95.000000, -142.000000, 0.000000, 1.000000, 0.000000}};
float table_pos[3] = {25, 0, 25};
float eyes_pos[3] = {3.0, 0.7, 1.7};
GLfloat ear_tri_pos[5][3] = {{-0.7, 0.0, 0.7}, {0.0, 1.35, 0.0}, {-0.7, 0.0, -0.7}, {0.7, 0.0, -0.7}, {0.7, 0.0, 0.7}};
float coffee_pos[3] = {10, 0, 14.5};
float table_top_point[8][3] = {{0, 0, 0}, {table_length, 0, 0}, {table_length, 0, table_width}, {0, 0, table_width}, {0, -table_thickness, 0}, {table_length, -table_thickness, 0}, {table_length, -table_thickness, table_width}, {0, -table_thickness, table_width}};
int table_faces[6][4] = {{0, 1, 2, 3}, {0, 1, 5, 4}, {1, 2, 6, 5}, {2, 3, 7, 6}, {0, 3, 7, 4}, {4, 5, 6, 7}};
float table_normal[6][4] = {{0.0, -1.0, 0.0}, {0.0, 0.0, -1.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}};
float table_feet_point[8][3] = {{0, 0, 0}, {table_feet_width, 0, 0}, {table_feet_width, 0, table_feet_width}, {0, 0, table_feet_width}, {0, -table_height, 0}, {table_feet_width, -table_height, 0}, {table_feet_width, -table_height, table_feet_width}, {0, -table_height, table_feet_width}};
float table_feet_trans[4][3] = {{0, 0, 0}, {table_length - table_feet_width, 0, 0}, {table_length - table_feet_width, 0, table_width - table_feet_width}, {0, 0, table_width - table_feet_width}};
float coffee_overthrow_pos[3] = {0.0, 0.1, 0.0};

float points[][3] = {{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 1.0}, {0.0, 1.0, 1.0}};
int face[][4] = {{0, 3, 2, 1}, {0, 1, 5, 4}, {1, 2, 6, 5}, {4, 5, 6, 7}, {2, 3, 7, 6}, {0, 4, 7, 3}};
float normal[][4] = {{0.0, 0.0, -1.0}, {0.0, -1.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {-1.0, 0.0, 0.0}};

// color
// float background_color[3] = { 1.0,0.98,0.8 };
float background_color[3] = {0.80, 0.87, 0.94};
float eyes_color[3] = {1.0, 0.84, 0.0};
float nose_color[3] = {0.73, 0.73, 0.73};

float tpx, tpy, tpz, tpang = 0;

float eyeDx = 0.0, eyeDy = 0.0, eyeDz = 0.0;
float eyeAngx = 0.0, eyeAngy = 0.0, eyeAngz = 0.0;
double Eye[3] = {4.0, 20, 16.5}, Focus[3] = {0.0, 0.0, 0.0},
       Vup[3] = {0.0, 1.0, 0.0};

float u[3][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};
float eye[3];
float cv, sv; /* cos(5.0) and sin(5.0) */
float zoom_fac = 1;

// light
float global_ambient[] = {0.2, 0.2, 0.2, 1.0};
float lit_specular[] = {0.7, 0.7, 0.7, 1.0};
float lit_diffuse[] = {0.6, 0.33, 0.0, 1.0};
float lit_direction[] = {0.0, 0.0, 1.0, 0.0};

float lit1_specular[] = {0.7, 0.7, 0.7, 1.0};
float lit1_diffuse[] = {0.0, 0.0, 0.5, 1.0};
float lit1_direction[] = {0.0, 0.0, 1.0, 0.0};
float lit1_position[] = {0.0, 30.0, 0.0, 1.0};

float  lit2_position[] = {0.0, 0.0, 0.0, 1.0};
float  lit2_direction[] = {1.0, 0.0, 0.0, 0.0};
float  lit2_diffuse[] = {0.0, 0.5, 0.0, 1.0};
float  lit2_specular[] = {0.0, 0.0, 0.0, 1.0};
float  lit2_cutoff=15.0;
float  lit2_exponent=8.0;

float flr_diffuse[] = {0.60, 0.60, 0.60, 1.0};
float flr_ambient[] = {0.3, 0.3, 0.3, 1.0};
float flr_specular[] = {0.0, 0.0, 0.0, 1.0};
float mat_ambient[] = {0.1, 0.1, 0.1, 1.0};
float mat_diffuse[] = {0.3, 0.3, 0.3, 1.0};
float mat_specular[] = {0.4, 0.4, 0.4, 1.0};
float mat_shininess = 64.0;

/*------------------------------------------------------------------
 * Procedure to draw a cylinder.
 */
void draw_cylinder(void)
{
    gluCylinder(cylind, 0.3, 0.3, /* radius of top and bottom circle */
                16.0,             /* height of the cylinder */
                12,               /* use 12-side polygon approximating circle*/
                4);               /* Divide it into 3 sections */
}

/*------------------------------------------------------------------
 * Procedure to draw an arrow .
 */
void draw_arrow(void)
{
    gluCylinder(cylind, 0.6, 0.0, /* radius of top and bottom circle */
                1.0,              /* height of the cylinder */
                12,               /* use 12-side polygon approximating circle*/
                4);               /* Divide it into 3 sections */
}
/*----------------------------------------------------------------------
 * Procedure to draw a coordinate system, RGB bars = XYZ axes
 * White ball = origin.
 */
void draw_coord_sys(void)
{

    // draw coord. sys. in line or fill mode.
    if (polygonMode == LINE)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glColor3f(1.0, 1.0, 1.0);
    gluSphere(sphere, 0.5, /* radius=0.5 */
              12,          /* composing of 12 slices*/
              12);         /* composing of 12 stacks */
    // Draw the x-axis in RED.
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    glRotatef(90.0, 0, 1, 0); // The x-axis
    draw_cylinder();
    glTranslatef(0, 0, 16);
    draw_arrow();
    glPopMatrix();
    // Draw the Y-axis in GREEN.
    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix(); // The y-axis
    glRotatef(-90.0, 1, 0, 0);
    draw_cylinder();
    glTranslatef(0, 0, 16);
    draw_arrow();
    glPopMatrix();
    // Draw the z-axis in BLUE.
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    draw_cylinder(); // The z-axis
    glTranslatef(0, 0, 16);
    draw_arrow();
    glPopMatrix();
}

void walk_end();

void draw_cube()
{
    /*-----Define some material properties shared by every one ---*/
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

    for (int i = 0; i < 6; i++)
    { /* draw the six faces one by one */
        glNormal3fv(normal[i]);
        glBegin(GL_POLYGON); /* Draw the face */
        glVertex3fv(points[face[i][0]]);
        glVertex3fv(points[face[i][1]]);
        glVertex3fv(points[face[i][2]]);
        glVertex3fv(points[face[i][3]]);
        glEnd();
    }
}

void draw_floor()
{
    int i, j;

    if (polygonMode == LINE)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    for (i = 0; i < 65; i++)
    {
        for (j = 0; j < 65; j++)
        {
            if ((i / 5 + j / 5) % 2 == 0)
                glColor3f(0.95, 0.95, 0.95);
            else
                glColor3f(0.61, 0.7, 0.68);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, flr_diffuse); /*diffuse color */
            glMaterialfv(GL_FRONT, GL_SPECULAR, flr_specular);
            glMaterialfv(GL_FRONT, GL_AMBIENT, flr_ambient);
            glNormal3f(0.0, 1.0, 0.0);
            glBegin(GL_POLYGON);
            glVertex3f(i, 0.0, j);
            glVertex3f(i, 0.0, j + 1);
            glVertex3f(i + 1, 0.0, j + 1);
            glVertex3f(i + 1, 0.0, j);
            glEnd();
        }
    }

    // 灑在地上的咖啡
    glColor3f(0.8, 0.2, 0.2);
    if (coffee_overthrow == TRUE)
    {
        float cos_ = cos(rot_ang[1] * PI / 180);
        float sin_ = -sin(rot_ang[1] * PI / 180);
        coffee_onfloor_info[0] = cos_;
        coffee_onfloor_info[1] = sin_;
        coffee_onfloor_info[2] = rot_ang[1];
        coffee_onfloor_info[3] = robot_pos[0] + 5 * cos_;
        coffee_onfloor_info[4] = 0.1;
        coffee_onfloor_info[5] = robot_pos[2] + 5 * sin_;
        coffee_overthrow = FALSE;
        take_coffee = FALSE;
        coffee_onfloor = TRUE;
    }
    if (coffee_onfloor == TRUE)
    {
        glPushMatrix();
        glTranslatef(coffee_onfloor_info[3], coffee_onfloor_info[4], coffee_onfloor_info[5]);
        glColor3f(0.0, 0.0, 0.0);
        glRotatef(-90, 1.0, 0.0, 0.0);
        glRotatef(coffee_onfloor_info[2], 0.0, 0.0, 1.0);
        glColor3f(0.58, 0.32, 0.16);
        glScalef(1.0, 1.4, 1.0);
        glRotatef(coffee_onfloor_info[2], 0.0, 0.0, 1.0);
        gluDisk(mycircle,
                0.0, /* inner radius=0.0 */
                3.0, /* outer radius=10.0 */
                16,  /* 16-side polygon */
                3);
        glPopMatrix();
    }

    // 腳印
    if (step_on_coffee == TRUE)
    {
        for (int i = 0; i < min(idx_cnt, 6); i++)
        {
            glPushMatrix();
            glTranslatef(step_on_coffee_info[i][3], step_on_coffee_info[i][4], step_on_coffee_info[i][5]);
            glScalef(0.2, 0.2, 0.2);
            glRotatef(-90, 1.0, 0.0, 0.0);
            glRotatef(-90, 0.0, 0.0, 1.0);
            glRotatef(step_on_coffee_info[i][2], 0.0, 0.0, 1.0);
            glPushMatrix();
            glScalef(1.3, 0.8, 1.0);
            glColor3f(0.58, 0.32, 0.16);
            gluDisk(mycircle,
                    0.0, /* inner radius=0.0 */
                    3.0, /* outer radius=10.0 */
                    16,  /* 16-side polygon */
                    3);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 1.5, 0);
            glScalef(1.1, 1.0, 1.0);
            gluDisk(mycircle,
                    0.0, /* inner radius=0.0 */
                    2.4, /* outer radius=10.0 */
                    16,  /* 16-side polygon */
                    3);
            glPopMatrix();

            // 腳趾
            glPushMatrix();
            glTranslatef(-4.2, 3.5, 0);
            // draw_coord_sys();
            glRotatef(21, 0.0, 0.0, 1.0);
            glScalef(1.0, 1.2, 1.0);
            gluDisk(mycircle,
                    0.0, /* inner radius=0.0 */
                    1.7, /* outer radius=10.0 */
                    16,  /* 16-side polygon */
                    3);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-1.7, 6.0, 0);
            glRotatef(12, 0.0, 0.0, 1.0);
            glScalef(1.0, 1.2, 1.0);
            gluDisk(mycircle,
                    0.0, /* inner radius=0.0 */
                    1.7, /* outer radius=10.0 */
                    16,  /* 16-side polygon */
                    3);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(1.7, 6.0, 0);
            glRotatef(-12, 0.0, 0.0, 1.0);
            glScalef(1.0, 1.2, 1.0);
            gluDisk(mycircle,
                    0.0, /* inner radius=0.0 */
                    1.7, /* outer radius=10.0 */
                    16,  /* 16-side polygon */
                    3);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(4.2, 3.5, 0);
            glRotatef(-21, 0.0, 0.0, 1.0);
            glScalef(1.0, 1.2, 1.0);
            gluDisk(mycircle,
                    0.0, /* inner radius=0.0 */
                    1.7, /* outer radius=10.0 */
                    16,  /* 16-side polygon */
                    3);
            glPopMatrix();

            glPopMatrix();
        }
    }

    // 左牆(門牆)
    glColor3f(0.7, 0.8, 0.75);
    glPushMatrix();
    glScalef(1, 40, 65);
    glRotatef(-90, 0.0, 1.0, 0.0);
    draw_cube();
    glPopMatrix();

    // 門
    glColor4f(0.6, 0.4, 0.3, 1.0);
    glPushMatrix();
    glTranslatef(0.1, 0, 5);
    glScalef(1.2, 25, 15);
    glRotatef(-90, 0.0, 1.0, 0.0);
    draw_cube();
    glPopMatrix();

    // 門把
    glColor3fv(nose_color);
    glPushMatrix();
    glTranslatef(0.5, 10.3, 8);
    glRotatef(90, 0.0, 1.0, 0.0);
    gluSphere(sphere, 1.0, /* radius=2.0 */
              12,          /* composing of 12 slices*/
              12);         /* composing of 12 stacks */
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5, 10.3, 8);
    glRotatef(90, 0.0, 1.0, 0.0);
    gluSphere(sphere, 1.0, /* radius=2.0 */
              12,          /* composing of 12 slices*/
              12);         /* composing of 12 stacks */
    glPopMatrix();

    // 右牆
    glColor3f(0.7, 0.8, 0.75);
    glPushMatrix();
    glTranslatef(65, 0, 0);
    for(i=0;i<40;i++)
    {
        for(j=0;j<65;j++)
        {
            draw_cube();
            glTranslatef(0, 0, 1);
        }
        glTranslatef(0, 1, 0);
        glTranslatef(0, 0, -65);
    }
    //glScalef(1, 40, 65);
    //draw_cube();
    glPopMatrix();

    // 天花板
    glColor3f(0.7, 0.8, 0.75);
    glPushMatrix();
    glTranslatef(-1, 40, 0);
    glScalef(67, 1, 65);
    draw_cube();
    glPopMatrix();

    // 前牆(窗戶牆)
    glColor3f(0.7, 0.8, 0.75);
    glPushMatrix();
    glScalef(8, 40, 1);
    draw_cube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(57, 0, 0);
    glScalef(8, 40, 1);
    draw_cube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 32, 0);
    glScalef(65, 8, 1);
    draw_cube();
    glPopMatrix();

    glPushMatrix();
    glScalef(65, 8, 1);
    draw_cube();
    glPopMatrix();

    // 窗戶
    glColor4f(1.0, 1.0, 1.0, 0.5);
    glPushMatrix();
    glTranslatef(10, 10, 0);
    glScalef(45, 20, 1);
    draw_cube();
    glPopMatrix();

    // 窗戶框
    glColor3f(0.9, 0.9, 0.9);
    glPushMatrix();
    glTranslatef(8, 8, 0);
    glScalef(2, 24, 1);
    draw_cube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8, 8, 0);
    glScalef(49, 2, 1);
    draw_cube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(55, 8, 0);
    glScalef(2, 24, 1);
    draw_cube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8, 30, 0);
    glScalef(49, 2, 1);
    draw_cube();
    glPopMatrix();
}
void draw_ear(int a, int b, int c)
{
    float v1[3];
    float v2[3];
    float n[4] = {0};
    for (int i = 0; i < 3; i++)
    {
        v1[i] = ear_tri_pos[b][i] - ear_tri_pos[a][i];
        v2[i] = ear_tri_pos[c][i] - ear_tri_pos[a][i];
    }
    n[0] = v1[1] * v2[2] - v1[2] * v2[1];
    n[1] = -(v1[0] * v2[2] - v1[2] * v2[0]);
    n[2] = v1[0] * v2[1] - v1[1] * v2[0];
    glNormal3fv(n);
    glBegin(GL_TRIANGLES);
    glVertex3fv(ear_tri_pos[a]);
    glVertex3fv(ear_tri_pos[b]);
    glVertex3fv(ear_tri_pos[c]);
    glEnd();
}
void draw_head()
{
    glTranslatef(0.0, 4.2, 0.0);
    glRotatef(head_ang, 0.0, 0.0, 1.0);	//頭旋轉
    glPushMatrix(); // 存下M4
    // 畫頭
    glScalef(1.0, 1.0, 1.16);
    glColor3f(0.0, 0.0, 0.0);
    gluSphere(sphere, 3.15, /* radius=2.0 */
              12,           /* composing of 12 slices*/
              12);          /* composing of 12 stacks */
    glPopMatrix();          // 回到M4

    // 畫左耳朵
    glPushMatrix(); // 存下M4
    glTranslatef(0.0, 2.0, 1.8);
    glRotatef(26, 1.0, 0.0, 0.0);
    glScalef(2.0, 2.0, 2.0);
    glColor3f(0.0, 0.0, 0.0);
    draw_ear(0, 1, 2);
    draw_ear(2, 1, 3);
    draw_ear(3, 1, 4);
    draw_ear(4, 1, 0);
    glPopMatrix(); // 回到M4

    // 畫右耳朵
    glPushMatrix(); // 存下M4
    glTranslatef(0.0, 2.0, -1.8);
    glRotatef(-26, 1.0, 0.0, 0.0);
    glScalef(2.0, 2.0, 2.0);
    glColor3f(0.0, 0.0, 0.0);
    draw_ear(0, 1, 2);
    draw_ear(2, 1, 3);
    draw_ear(3, 1, 4);
    draw_ear(4, 1, 0);
    glPopMatrix(); // 回到M4

    // 畫左眼睛
    glPushMatrix(); // 存下M4
    glTranslatef(eyes_pos[0], eyes_pos[1], eyes_pos[2]);
    glScalef(0.3, 1.0, 1.0);
    glColor3fv(eyes_color);
    gluSphere(sphere, 0.87, /* radius=2.0 */
              12,           /* composing of 12 slices*/
              12);          /* composing of 12 stacks */
    glPopMatrix();          // 回到M4

    glPushMatrix(); // 存下M4
    glTranslatef(eyes_pos[0] + 0.2, eyes_pos[1], eyes_pos[2]);
    glScalef(0.3, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    gluSphere(sphere, 0.68, /* radius=2.0 */
              12,           /* composing of 12 slices*/
              12);          /* composing of 12 stacks */
    glPopMatrix();          // 回到M4

    // 畫右眼睛
    glPushMatrix(); // 存下M4
    glTranslatef(eyes_pos[0], eyes_pos[1], -eyes_pos[2]);
    glScalef(0.3, 1.0, 1.0);
    glColor3fv(eyes_color);
    gluSphere(sphere, 0.87, /* radius=2.0 */
              12,           /* composing of 12 slices*/
              12);          /* composing of 12 stacks */
    glPopMatrix();          // 回到M4

    glPushMatrix(); // 存下M4
    glTranslatef(eyes_pos[0] + 0.2, eyes_pos[1], -eyes_pos[2]);
    glScalef(0.3, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    gluSphere(sphere, 0.68, /* radius=2.0 */
              12,           /* composing of 12 slices*/
              12);          /* composing of 12 stacks */
    glPopMatrix();          // 回到M4

    // 畫鼻子
    glPushMatrix(); // 存下M4
    glTranslatef(3.2, -0.2, 0.0);
    glRotatef(90, 1.0, 0.0, 0.0);
    // draw_coord_sys();
    // glColor3f(1.0,1.0,1.0);
    glColor3fv(nose_color);
    gluCylinder(cylind, 0.6, 0.1, /* radius of top and bottom circle */
                0.6,              /* height of the cylinder */
                12,               /* use 12-side polygon approximating circle*/
                3);               /* Divide it into 3 sections */
    glPopMatrix();                // 回到M4

    // 畫鼻子鬍鬚
    glPushMatrix(); // 存下M4
    glTranslatef(3.0, -0.45, 0.0);
    glRotatef(55, 1.0, 0.0, 0.0);
    glColor3fv(nose_color);
    gluCylinder(cylind, 0.12, 0.12, /* radius of top and bottom circle */
                0.9,                /* height of the cylinder */
                12,                 /* use 12-side polygon approximating circle*/
                3);                 /* Divide it into 3 sections */
    glPopMatrix();                  // 回到M4

    glPushMatrix(); // 存下M4
    glTranslatef(3.0, -0.45, 0.0);
    glRotatef(-235, 1.0, 0.0, 0.0);
    glColor3fv(nose_color);
    gluCylinder(cylind, 0.12, 0.12, /* radius of top and bottom circle */
                0.9,                /* height of the cylinder */
                12,                 /* use 12-side polygon approximating circle*/
                3);                 /* Divide it into 3 sections */
    glPopMatrix();                  // 回到M4

    // 畫左臉鬍鬚
    glPushMatrix(); // 存下M4
    glTranslatef(2.0, -0.6, 2.3);
    glPushMatrix(); // 存下M5

    glColor3fv(nose_color);
    gluCylinder(cylind, 0.12, 0.12, /* radius of top and bottom circle */
                2.0,                /* height of the cylinder */
                12,                 /* use 12-side polygon approximating circle*/
                3);                 /* Divide it into 3 sections */
    glPopMatrix();                  // 回到M5

    glPushMatrix(); // 存下M5
    glTranslatef(0.0, -0.4, 0.0);
    glRotatef(15, 1.0, 0.0, 0.0);
    glColor3fv(nose_color);
    gluCylinder(cylind, 0.12, 0.12, /* radius of top and bottom circle */
                2.0,                /* height of the cylinder */
                12,                 /* use 12-side polygon approximating circle*/
                3);                 /* Divide it into 3 sections */
    glPopMatrix();                  // 回到M5
    glPopMatrix();                  // 回到M4

    // 畫右臉鬍鬚
    glTranslatef(2.0, -0.6, -2.3);
    glRotatef(180, 0.0, 1.0, 0.0);
    glPushMatrix(); // 存下M6

    glColor3fv(nose_color);
    gluCylinder(cylind, 0.12, 0.12, /* radius of top and bottom circle */
                2.0,                /* height of the cylinder */
                12,                 /* use 12-side polygon approximating circle*/
                3);                 /* Divide it into 3 sections */
    glPopMatrix();                  // 回到M6

    glPushMatrix(); // 存下M6
    glTranslatef(0.0, -0.4, 0.0);
    glRotatef(15, 1.0, 0.0, 0.0);
    glColor3fv(nose_color);
    gluCylinder(cylind, 0.12, 0.12, /* radius of top and bottom circle */
                2.0,                /* height of the cylinder */
                12,                 /* use 12-side polygon approximating circle*/
                3);                 /* Divide it into 3 sections */

    glPopMatrix(); // 回到M6
    glPopMatrix(); // 回到M1
}

void draw_hand(int mode, float arm_ang, float forearm_ang, float hand_ang)
{

    glPushMatrix(); // 存下M1
    if (mode == LEFT)
    {
        glTranslatef(0.0, 1.5, 3.6);   // 移到M2
        glRotatef(-20, 1.0, 0.0, 0.0); // 手臂和身體分開一點
                                       //  draw_coord_sys();
    }
    else
    {
        glTranslatef(0.0, 1.5, -3.6); // 移到M2
        glRotatef(20, 1.0, 0.0, 0.0); // 手臂和身體分開一點
                                      //  draw_coord_sys();
    }
    glRotatef(arm_ang, 0.0, 0.0, 1.0); // 整隻手臂旋轉
    if (sayhi == TRUE && mode == RIGHT)
        glRotatef(tpang, 1.0, 0.0, 0.0); // 整隻手臂旋轉

    // 肩膀圓
    glPushMatrix(); // 存下M2
    // glScalef(1.0, 1.1, 1.0);
    glColor3fv(nose_color);
    gluSphere(sphere, 0.8, 12, 12);
    glPopMatrix(); // 回到M2

    // 手臂
    glPushMatrix(); // 存下M2
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    gluCylinder(cylind, 0.7, 0.45, /* radius of top and bottom circle */
                1.6,               /* height of the cylinder */
                12,                /* use 12-side polygon approximating circle*/
                3);                /* Divide it into 3 sections */

    glPopMatrix(); // 回到M2

    /*--------------前臂-----------------*/
    glPushMatrix();               // 存下M2
    glTranslatef(0.0, -2.0, 0.0); // 移到M3
    if (sayhi == TRUE)
    {
        if (mode == RIGHT)
        {
            glRotatef(forearm_ang, 1.0, 0.0, 0.0); // 前臂旋轉
            glRotatef(90, 0.0, 1.0, 0.0);          // 前臂旋轉
        }
    }
    else
        glRotatef(forearm_ang, 1.0, 0.0, 0.0); // 前臂旋轉
    // glRotatef(90, 0.0, 1.0, 0.0);	//前臂旋轉
    // draw_coord_sys();

    // 前臂圓
    glPushMatrix(); // 存下M3
    glColor3fv(nose_color);
    gluSphere(sphere, 0.65, /* radius=2.0 */
              12,           /* composing of 12 slices*/
              12);          /* composing of 12 stacks */
    glPopMatrix();          // 回到M3

    // 前臂
    glPushMatrix(); // 存下M3
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    gluCylinder(cylind, 0.6, 0.4, /* radius of top and bottom circle */
                1.6,              /* height of the cylinder */
                12,               /* use 12-side polygon approximating circle*/
                3);               /* Divide it into 3 sections */
    glPopMatrix();                // 回到M3

    /*--------------手掌-----------------*/
    glPushMatrix();               // 存下M3
    glTranslatef(0.0, -2.0, 0.0); // 移到M5
    // glRotatef(90, 0.0, 0.0,1.0);	//前臂旋轉

    // 手掌圓
    glPushMatrix(); // 存下M5
    glScalef(1.0, 1.4, 0.5);
    glColor3fv(nose_color);
    gluSphere(sphere, 0.76, /* radius=2.0 */
              12,           /* composing of 12 slices*/
              12);          /* composing of 12 stacks */

    glPopMatrix(); // 回到M5

    // 四手指
    glPushMatrix();
    glTranslatef(0.0, -0.55, 0.0);
    // draw_coord_sys();
    if (take_coffee == TRUE && mode == LEFT)
    {
        glTranslatef(0.0, -0.3, -0.55);
        glRotatef(75, 1.0, 0.0, 0.0);
    }
    else
        glRotatef(hand_ang, 1.0, 0.0, 0.0);

    glScalef(1.0, 1.2, 0.3);

    // glColor3f(0.0,0.0,0.0);
    gluSphere(sphere, 0.76, /* radius=2.0 */
              12,           /* composing of 12 slices*/
              12);          /* composing of 12 stacks */
    glPopMatrix();

    // 大拇指
    //  draw_coord_sys();
    glPushMatrix();
    if (mode == LEFT)
        glTranslatef(0.0, 0.3, -0.6); // 移到M8
    else
        glTranslatef(0.0, 0.3, 0.6); // 移到M8
    glRotatef(100, 1.0, 0.0, 0.0);
    // draw_coord_sys();
    glScalef(1.0, 0.8, 0.3);
    glColor3fv(nose_color);
    gluSphere(sphere, 0.76, /* radius=2.0 */
              12,           /* composing of 12 slices*/
              12);          /* composing of 12 stacks */
    glPopMatrix();

    // 手拿水
    if (take_coffee == TRUE && mode == LEFT)
    {
        glPushMatrix();
        glTranslatef(-0.6, -0.2, -1.0);
        glRotatef(90, 0.0, 1.0, 0.0);
        // 咖啡
        glColor4f(0.58, 0.32, 0.16, 1.0);
        glTranslatef(0.0, 0.0, 0.2);
        gluCylinder(cylind, 0.42, 0.80, /* radius of top and bottom circle */
                    1.8,                /* height of the cylinder */
                    12,                 /* use 12-side polygon approximating circle*/
                    3);                 /* Divide it into 3 sections */
        glTranslatef(0.0, 0.0, 1.8);
        glColor4f(0.58, 0.32, 0.16, 1.0);
        gluDisk(mycircle,
                0.0, /* inner radius=0.0 */
                0.8, /* outer radius=10.0 */
                16,  /* 16-side polygon */
                3);  /* Divide it into 3 sections */
        // 杯子
        glTranslatef(0.0, 0.0, -2.0);
        glColor4f(1.0, 1.0, 1.0, 0.35);
        gluCylinder(cylind, 0.6, 1.0, /* radius of top and bottom circle */
                    2.7,              /* height of the cylinder */
                    12,               /* use 12-side polygon approximating circle*/
                    3);               /* Divide it into 3 sections */
        glPopMatrix();
    }

    glPopMatrix(); // 回到M3
    glPopMatrix(); // 回到M2
    glPopMatrix(); // 回到M1
}

void draw_feet(int mode, float thigh_ang, float calf_ang, float feet_ang)
{
    glPushMatrix(); // 存下M1
    if (mode == LEFT)
        glTranslatef(0.0, -2.8, 1.2); // 移到M6
    else
        glTranslatef(0.0, -2.8, -1.2);   // 移到M6
    glRotatef(thigh_ang, 0.0, 0.0, 1.0); // 整隻腳旋轉
    /*---------------------大腿----------------------*/
    // 大腿圓
    glPushMatrix(); // 存下M6
    glColor3fv(nose_color);
    gluSphere(sphere, 1.2, /* radius=2.0 */
              12,          /* composing of 12 slices*/
              12);         /* composing of 12 stacks */
    glPopMatrix();         // 回到M6

    // 大腿
    glPushMatrix(); // 存下M6
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    if (cylind == NULL)
    {
        cylind = gluNewQuadric();
        gluQuadricDrawStyle(cylind, GLU_FILL);
        gluQuadricNormals(cylind, GLU_SMOOTH);
    }
    gluCylinder(cylind, 1.0, 0.7, /* radius of top and bottom circle */
                1.8,              /* height of the cylinder */
                12,               /* use 12-side polygon approximating circle*/
                3);               /* Divide it into 3 sections */
    glPopMatrix();                // 回到M6

    /*---------------------小腿----------------------*/
    glPushMatrix();               // 存下M6
    glTranslatef(0.0, -2.0, 0.0); // 移到M7
    glRotatef(calf_ang, 0.0, 0.0, 1.0);

    // 小腿圓
    glPushMatrix(); // 存下M7
    glColor3fv(nose_color);
    gluSphere(sphere, 0.7, /* radius=2.0 */
              12,          /* composing of 12 slices*/
              12);         /* composing of 12 stacks */
    glPopMatrix();         // 回到M6

    // 小腿
    glPushMatrix(); // 存下M7
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    gluCylinder(cylind, 0.65, 0.4, /* radius of top and bottom circle */
                1.8,               /* height of the cylinder */
                12,                /* use 12-side polygon approximating circle*/
                3);                /* Divide it into 3 sections */
    glPopMatrix();                 // 回到M7

    /*---------------------腳掌----------------------*/
    glPushMatrix(); // 存下M7

    glRotatef(feet_ang, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -2.0, 0.0);
    // 腳掌圓
    glPushMatrix(); // 存下M8

    glScalef(1.0, 0.6, 1.0);
    glColor3fv(nose_color);
    gluSphere(sphere, 1.0, /* radius=2.0 */
              12,          /* composing of 12 slices*/
              12);         /* composing of 12 stacks */

    glPopMatrix(); // 回到M8
    glPopMatrix(); // 回到M7
    glPopMatrix(); // 回到M6
    glPopMatrix(); // 回到M1
}

void draw_body()
{
    glPushMatrix(); // 存M1
    glScalef(0.9, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    gluSphere(sphere, 3.77, /* radius=2.0 */
              12,           /* composing of 12 slices*/
              12);          /* composing of 12 stacks */
    glPopMatrix();          // 回到M1

    draw_hand(LEFT, left_arm_ang, left_forearm_ang, left_hand_ang);
    draw_hand(RIGHT, right_arm_ang, right_forearm_ang, right_hand_ang);

    draw_feet(LEFT, left_thigh_ang, left_calf_ang, left_feet_ang);
    draw_feet(RIGHT, right_thigh_ang, right_calf_ang, right_feet_ang);
}

void draw_table()
{
    glPushMatrix();
    glTranslatef(table_pos[0], table_pos[1] + table_thickness + table_height, table_pos[2]);
    glPushMatrix();
    glColor3f(1.00, 0.8, 0.5);
    glTranslatef(0, -table_thickness, 0);
    glScalef(table_length, table_thickness, table_width);
    draw_cube();
    glPopMatrix();

    /*-------------------畫咖啡-------------------*/
    if (table_coffee == TRUE)
    {
        glPushMatrix();
        glTranslatef(coffee_pos[0], coffee_pos[1], coffee_pos[2]);
        glRotatef(-90, 1.0, 0.0, 0.0);
        // 咖啡
        glColor4f(0.58, 0.32, 0.16, 1.0);
        glTranslatef(0.0, 0.0, 0.2);
        gluCylinder(cylind, 0.42, 0.80, /* radius of top and bottom circle */
                    1.8,                /* height of the cylinder */
                    12,                 /* use 12-side polygon approximating circle*/
                    3);                 /* Divide it into 3 sections */
        glTranslatef(0.0, 0.0, 1.8);
        glColor4f(0.58, 0.32, 0.16, 1.0);
        gluDisk(mycircle,
                0.0, /* inner radius=0.0 */
                0.8, /* outer radius=10.0 */
                16,  /* 16-side polygon */
                3);  /* Divide it into 3 sections */
        // 杯子
        glTranslatef(0.0, 0.0, -2.0);
        glColor4f(1.0, 1.0, 1.0, 0.35);
        gluCylinder(cylind, 0.6, 1.0, /* radius of top and bottom circle */
                    2.7,              /* height of the cylinder */
                    12,               /* use 12-side polygon approximating circle*/
                    3);               /* Divide it into 3 sections */
        glPopMatrix();
    }

    /*----------------畫桌腳----------------------*/
    glColor3f(1.00, 0.8, 0.5);
    for (int t = 0; t < 4; t++)
    {
        glPushMatrix();
        glTranslatef(table_feet_trans[t][0], -table_thickness - table_height, table_feet_trans[t][2]);
        glScalef(table_feet_width, table_height, table_feet_width);
        draw_cube();
        glPopMatrix();
    }
    glPopMatrix();
}

void draw_view_volume()
{
    // glColor4f(1.0, 0.0, 0.0, 0.5); /* Set color */
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBegin(GL_POLYGON); // near clipping
    glVertex3f(-1.0 * zoom_fac, -1.0 * zoom_fac * (float)height / width, -1.0);
    glVertex3f(-1.0 * zoom_fac, 1.0 * zoom_fac * (float)height / width, -1.0);
    glVertex3f(1.0 * zoom_fac, 1.0 * zoom_fac * (float)height / width, -1.0);
    glVertex3f(1.0 * zoom_fac, -1.0 * zoom_fac * (float)height / width, -1.0);
    glEnd();

    glScalef(65, 65, 65);
    glBegin(GL_POLYGON); //(0,(l,b,f),(l,t,f))
    glVertex3f(0, 0, 0);
    glVertex3f(-1.0 * zoom_fac, -1.0 * zoom_fac * (float)height / width, -1.0);
    glVertex3f(-1.0 * zoom_fac, 1.0 * zoom_fac * (float)height / width, -1.0);
    glEnd();
    glBegin(GL_POLYGON); //(0,(l,t,f),(r,t,f))
    glVertex3f(0, 0, 0);
    glVertex3f(-1.0 * zoom_fac, 1.0 * zoom_fac * (float)height / width, -1.0);
    glVertex3f(1.0 * zoom_fac, 1.0 * zoom_fac * (float)height / width, -1.0);
    glEnd();
    glBegin(GL_POLYGON); //(0,(r,b,f),(r,t,f))
    glVertex3f(0, 0, 0);
    glVertex3f(1.0 * zoom_fac, -1.0 * zoom_fac * (float)height / width, -1.0);
    glVertex3f(1.0 * zoom_fac, 1.0 * zoom_fac * (float)height / width, -1.0);
    glEnd();
    glBegin(GL_POLYGON); //(0,(r,b,f),(l,b,f))
    glVertex3f(0, 0, 0);
    glVertex3f(1.0 * zoom_fac, -1.0 * zoom_fac * (float)height / width, -1.0);
    glVertex3f(-1.0 * zoom_fac, -1.0 * zoom_fac * (float)height / width, -1.0);
    glEnd();
}

void draw_scene()
{
    draw_coord_sys();

  glDisable(GL_LIGHTING);
    /*-------Draw light source as a red cube----*/
     glPushMatrix();
     glTranslatef(lit1_position[0],lit1_position[1],lit1_position[2]);
     glColor3f(0.0, 0.0, 1.0);
     gluSphere(sphere, 2, /* radius=0.5 */
              12,          /* composing of 12 slices*/
              12);         /* composing of 12 stacks */
     glPopMatrix();
    //glEnable(GL_LIGHTING); 
     glLightfv(GL_LIGHT1, GL_POSITION, lit1_position);

    glPushMatrix();
    glTranslatef(-32.5, 0, -32.5);
    glTranslatef(robot_pos[0], robot_pos[1] + 7.4, robot_pos[2] + 0.0); // M1
    glRotatef(rot_ang[1], 0.0, 1.0, 0.0);
    glRotatef(rot_ang[2], 0.0, 0.0, 1.0); // 轉圈
    glPushMatrix();
    glTranslatef(0.0, 4.2, 0.0);
    glRotatef(head_ang, 0.0, 0.0, 1.0);	//頭旋轉
    glTranslatef(eyes_pos[0], eyes_pos[1], eyes_pos[2]);
    glColor3f(0.0, 1.0, 0.0);
    gluSphere(sphere, 2, /* radius=0.5 */
              12,          /* composing of 12 slices*/
              12);         /* composing of 12 stacks */
    glLightfv(GL_LIGHT2, GL_POSITION, lit2_position);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lit2_direction);
    glTranslatef(0,0, -2*eyes_pos[2]);
    glColor3f(0.0, 1.0, 0.0);
    gluSphere(sphere, 2, /* radius=0.5 */
              12,          /* composing of 12 slices*/
              12);         /* composing of 12 stacks */
    glLightfv(GL_LIGHT3, GL_POSITION, lit2_position);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, lit2_direction);          
    glPopMatrix();
    glPopMatrix();
    // glEnable(GL_LIGHTING); 

    glPushMatrix();
    glColor3f(1.0, 0, 0);
    glTranslatef(-32.5, 0, -32.5);
    glPushMatrix();
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(robot_pos[0], robot_pos[1] + 7.4, robot_pos[2] + 0.0); // M1
    glRotatef(rot_ang[1], 0.0, 1.0, 0.0);                               // 轉圈
    glPushMatrix();
    glRotatef(rot_ang[2], 0.0, 0.0, 1.0); // 轉圈
    draw_body();
    draw_head();
    glPopMatrix();
    draw_table();
    draw_floor();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(eye[0], eye[1], eye[2]);
    glPushMatrix();
    GLdouble t_matrix[16] = {0.0};
    t_matrix[0] = u[0][0];
    t_matrix[1] = u[0][1];
    t_matrix[2] = u[0][2];
    t_matrix[4] = u[1][0];
    t_matrix[5] = u[1][1];
    t_matrix[6] = u[1][2];
    t_matrix[8] = u[2][0];
    t_matrix[9] = u[2][1];
    t_matrix[10] = u[2][2];
    t_matrix[15] = 1.0;
    glMultMatrixd(t_matrix);
    if (view_volume)
    {
        glColor4f(0.0, 0.0, 0.0, 0.5); /* Set color */
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        draw_view_volume();
        glColor4f(0.6, 0.6, 0.6, 0.3); /* Set color */
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        draw_view_volume();
    }
    glPopMatrix();
    glPopMatrix();
}

void make_view(int x)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // glPushMatrix();
    // glLoadIdentity();
    // /*----position light1 (fixed) in eye coord sys ---*/
    // glLightfv(GL_LIGHT1, GL_POSITION, lit1_position); /*fixed position in eye space---*/
    // glTranslatef(lit1_position[0], lit1_position[1], lit1_position[2]);
    // glDisable(GL_LIGHTING);
    // glDisable(GL_CULL_FACE);
    // glColor3f(0.80, 0.80, 0.0);
    // gluSphere(sphere, 3, /* radius=0.5 */
    //           12,          /* composing of 12 slices*/
    //           12);         /* composing of 12 stacks */
    // glPopMatrix();
    // glEnable(GL_CULL_FACE);
    // glEnable(GL_LIGHTING);
    switch (x)
    {
    case 4: /* Perspective */

        /* In this sample program, eye position and Xe, Ye, Ze are computed
           by ourselves. Therefore, use them directly; no trabsform is
           applied upon eye coordinate system
           */
        gluLookAt(eye[0], eye[1], eye[2],
                  eye[0] - u[2][0], eye[1] - u[2][1], eye[2] - u[2][2],
                  u[1][0], u[1][1], u[1][2]);
        break;

    case 1: /* X direction parallel viewing */
        gluLookAt(30.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        break;
    case 2: /* Y direction parallel viewing */
        gluLookAt(0.0, 30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
        break;
    case 3:
        gluLookAt(0.0, 0.0, 30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        break;
    }
}

/*------------------------------------------------------
 * Procedure to make projection matrix
 */
void make_projection(int x)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (x == 4)
    {
        // gluPerspective(90.0, (double)width / (double)height, 1.5, 50.0);
        if (width > height)
            glFrustum(-1.0 * zoom_fac, 1.0 * zoom_fac, -1.0 * zoom_fac * (float)height / width, 1.0 * zoom_fac * (float)height / width,
                      1.0, 65.0);
        else
            glFrustum(-1.0 * zoom_fac * (float)width / height, 1.0 * zoom_fac * (float)width / height, -1.0 * zoom_fac, 1.0 * zoom_fac,
                      1.0, 65.0);
    }
    else
    {
        if (x == 1 || x == 3)
        {
            if (width > height)
                glOrtho(-40.0 * zoom_fac, 40.0 * zoom_fac, -20.0 * zoom_fac * (float)height / (float)width,
                        60.0 * zoom_fac * (float)height / (float)width,
                        -0.0, 100.0);
            else
                glOrtho(-40 * zoom_fac * (float)width / (float)height,
                        40 * zoom_fac * (float)width / (float)height, -20 * zoom_fac, 60 * zoom_fac,
                        -0.0, 100.0);
        }
        else
        {
            if (width > height)
                glOrtho(zoom_fac * (-40.0), zoom_fac * 40.0, -40.0 * zoom_fac * (float)height / (float)width,
                        40.0 * zoom_fac * (float)height / (float)width,
                        -0.0, 100.0);
            else
                glOrtho(-40 * zoom_fac * (float)width / (float)height,
                        40 * zoom_fac * (float)width / (float)height, -40 * zoom_fac, 40 * zoom_fac,
                        -0.0, 100.0);
        }
    }
    glMatrixMode(GL_MODELVIEW);
}

/*---------------------------------------------------------
 * Procedure to draw view volume, eye position, focus ,...
 * for perspective projection
 */
void draw_view()
{
    int i;

    glMatrixMode(GL_MODELVIEW);

    /*----Draw Eye position-----*/
    glPushMatrix();
    glTranslatef(eye[0], eye[1], eye[2]);
    glColor3f(0.0, 1.0, 0.0);
    glutWireSphere(1.0, 10, 10);
    glPopMatrix();

    /*----Draw eye coord. axes -----*/
    glColor3f(1.0, 1.0, 0.0); /* Draw Xe */
    glBegin(GL_LINES);
    glVertex3f(eye[0], eye[1], eye[2]);
    glVertex3f(eye[0] + 20.0 * u[0][0], eye[1] + 20.0 * u[0][1], eye[2] + 20.0 * u[0][2]);
    glEnd();

    glColor3f(1.0, 0.0, 1.0); /* Draw Ye */
    glBegin(GL_LINES);
    glVertex3f(eye[0], eye[1], eye[2]);
    glVertex3f(eye[0] + 20.0 * u[1][0], eye[1] + 20.0 * u[1][1], eye[2] + 20.0 * u[1][2]);
    glEnd();

    glColor3f(0.0, 1.0, 1.0); /* Draw Ze */
    glBegin(GL_LINES);
    glVertex3f(eye[0], eye[1], eye[2]);
    glVertex3f(eye[0] + 20.0 * u[2][0], eye[1] + 20.0 * u[2][1], eye[2] + 20.0 * u[2][2]);
    glEnd();
}

int tmp = 0;
void display()
{

    /*Clear previous frame and the depth buffer */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    switch (view_mode)
    {
    case 0:
        make_view(4);
        make_projection(4);
        glViewport(width / 2, 0, width / 2, height / 2);
        draw_scene();

        make_view(1);
        make_projection(1);
        glViewport(0, height / 2, width / 2, height / 2);
        draw_scene();
        make_view(1);
        draw_view();

        make_view(2);
        make_projection(2);
        glViewport(width / 2, height / 2, width / 2, height / 2);
        draw_scene();
        make_view(2);
        draw_view();

        make_view(3);
        make_projection(3);
        glViewport(0, 0, width / 2, height / 2);
        draw_scene();
        make_view(3);
        draw_view();
        break;
    case 1:
        glViewport(0, 0, width, height);
        make_view(1);
        make_projection(1);
        draw_scene();
        make_view(1);
        draw_view();
        break;
    case 2:
        glViewport(0, 0, width, height);
        make_view(2);
        make_projection(2);
        draw_scene();
        make_view(2);
        draw_view();
        break;
    case 3:
        glViewport(0, 0, width, height);
        make_view(3);
        make_projection(3);
        draw_scene();
        make_view(3);
        draw_view();
        break;

    case 4:
        glViewport(0, 0, width, height);
        make_view(4);
        make_projection(4);
        draw_scene();
        make_view(4);
        draw_view();
        break;
    }
    //draw_scene();
    /*-------Swap the back buffer to the front --------*/
    glutSwapBuffers();
    return;
}

int check(float x, float z)
{
    float cos_ = cos(rot_ang[1] * PI / 180);
    float sin_ = -sin(rot_ang[1] * PI / 180);
    float l_x = x + (-robot_range), r_x = x + robot_range;
    float front_z = z + (-robot_range), back_z = z + robot_range;
    float check_step = FALSE;
    if (step_on_coffee == FALSE)
    {
        // 左前
        if (coffee_onfloor_info[3] - 3 >= l_x && coffee_onfloor_info[3] - 3 <= r_x && coffee_onfloor_info[5] - 3 >= front_z && coffee_onfloor_info[5] - 3 <= back_z)
            check_step = TRUE;
        // 右前
        if (coffee_onfloor_info[3] + 3 >= l_x && coffee_onfloor_info[3] + 3 <= r_x && coffee_onfloor_info[5] - 3 >= front_z && coffee_onfloor_info[5] - 3 <= back_z)
            check_step = TRUE;
        // 左後
        if (coffee_onfloor_info[3] - 3 >= l_x && coffee_onfloor_info[3] - 3 <= r_x && coffee_onfloor_info[5] + 3 >= front_z && coffee_onfloor_info[5] + 3 <= back_z)
            check_step = TRUE;
        // 右後
        if (coffee_onfloor_info[3] + 3 >= l_x && coffee_onfloor_info[3] + 3 <= r_x && coffee_onfloor_info[5] + 3 >= front_z && coffee_onfloor_info[5] + 3 <= back_z)
            check_step = TRUE;
    }
    else
    {
        step_cnt = (step_cnt + 1) % TOTAL_STEP_MOD;
        if (step_cnt % STEP_MOD == 0)
        {
            idx_cnt++;
            step_on_coffee_info[idx_cnt % 6][0] = cos_;
            step_on_coffee_info[idx_cnt % 6][1] = sin_;
            step_on_coffee_info[idx_cnt % 6][2] = rot_ang[1];
            step_on_coffee_info[idx_cnt % 6][3] = robot_pos[0] - 2.5 * cos_;
            step_on_coffee_info[idx_cnt % 6][4] = 0.1;
            if (idx_cnt % 6 % 2 == 1)
                step_on_coffee_info[idx_cnt % 6][5] = robot_pos[2] - 2.5 * sin_ + 2 * cos_;
            else
                step_on_coffee_info[idx_cnt % 6][5] = robot_pos[2] - 2.5 * sin_ - 2 * cos_;
        }
    }
    if (check_step == TRUE)
        step_on_coffee = TRUE;

    // 左前
    if (l_x >= table_pos[0] && l_x <= table_pos[0] + table_length && front_z >= table_pos[2] && front_z <= table_pos[2] + table_width)
        return 0;
    // 右前
    if (r_x >= table_pos[0] && r_x <= table_pos[0] + table_length && front_z >= table_pos[2] && front_z <= table_pos[2] + table_width)
        return 0;
    // 左後
    if (l_x >= table_pos[0] && l_x <= table_pos[0] + table_length && back_z >= table_pos[2] && back_z <= table_pos[2] + table_width)
        return 0;
    // 右後
    if (r_x >= table_pos[0] && r_x <= table_pos[0] + table_length && back_z >= table_pos[2] && back_z <= table_pos[2] + table_width)
        return 0;
    if (l_x <= 0 || r_x > 65 + 1 || front_z <= 0 || back_z > 65 + 1)
        return 0;

    return 1;
}

void walk()
{
    walk_cnt += 1.0;
    float nxt_x = robot_pos[0] + (15.0 / 48) * cos(rot_ang[1] * PI / 180);
    float nxt_z = robot_pos[2] + (15.0 / 48) * (-sin(rot_ang[1] * PI / 180));
    if (check(nxt_x, nxt_z))
    {
        robot_pos[0] = nxt_x;
        robot_pos[2] = nxt_z;
    }
    for (int i = 1; i < 7; i++)
    {
        if (walk_cnt <= walk_state_time[i + 1])
        {
            left_thigh_ang = walk_state_ang[i][0] + (walk_state_ang[i + 1][0] - walk_state_ang[i][0]) * (walk_cnt - walk_state_time[i]) / (walk_state_time[i + 1] - walk_state_time[i]);
            left_calf_ang = walk_state_ang[i][1] + (walk_state_ang[i + 1][1] - walk_state_ang[i][1]) * (walk_cnt - walk_state_time[i]) / (walk_state_time[i + 1] - walk_state_time[i]);
            right_thigh_ang = walk_state_ang[i][2] + (walk_state_ang[i + 1][2] - walk_state_ang[i][2]) * (walk_cnt - walk_state_time[i]) / (walk_state_time[i + 1] - walk_state_time[i]);
            right_calf_ang = walk_state_ang[i][3] + (walk_state_ang[i + 1][3] - walk_state_ang[i][3]) * (walk_cnt - walk_state_time[i]) / (walk_state_time[i + 1] - walk_state_time[i]);
            if (i + 1 <= 3)
            {
                left_arm_ang = walk_hand_state_ang[0][0] + (walk_hand_state_ang[1][0] - walk_hand_state_ang[0][0]) * (walk_cnt - walk_state_time[1]) / (walk_state_time[3] - walk_state_time[1]);
                left_forearm_ang = walk_hand_state_ang[0][1] + (walk_hand_state_ang[1][1] - walk_hand_state_ang[0][1]) * (walk_cnt - walk_state_time[1]) / (walk_state_time[3] - walk_state_time[1]);
                right_arm_ang = walk_hand_state_ang[0][2] + (walk_hand_state_ang[1][2] - walk_hand_state_ang[0][2]) * (walk_cnt - walk_state_time[1]) / (walk_state_time[3] - walk_state_time[1]);
                right_forearm_ang = walk_hand_state_ang[0][3] + (walk_hand_state_ang[1][3] - walk_hand_state_ang[0][3]) * (walk_cnt - walk_state_time[1]) / (walk_state_time[3] - walk_state_time[1]);
            }
            else if (i + 1 <= 4)
            {
                left_arm_ang = walk_hand_state_ang[1][0] + (walk_hand_state_ang[2][0] - walk_hand_state_ang[1][0]) * (walk_cnt - walk_state_time[3]) / (walk_state_time[4] - walk_state_time[3]);
                left_forearm_ang = walk_hand_state_ang[1][1] + (walk_hand_state_ang[2][1] - walk_hand_state_ang[1][1]) * (walk_cnt - walk_state_time[3]) / (walk_state_time[4] - walk_state_time[3]);
                right_arm_ang = walk_hand_state_ang[1][2] + (walk_hand_state_ang[2][2] - walk_hand_state_ang[1][2]) * (walk_cnt - walk_state_time[3]) / (walk_state_time[4] - walk_state_time[3]);
                right_forearm_ang = walk_hand_state_ang[1][3] + (walk_hand_state_ang[2][3] - walk_hand_state_ang[1][3]) * (walk_cnt - walk_state_time[3]) / (walk_state_time[4] - walk_state_time[3]);
            }
            else if (i + 1 <= 6)
            {
                left_arm_ang = walk_hand_state_ang[2][0] + (walk_hand_state_ang[3][0] - walk_hand_state_ang[2][0]) * (walk_cnt - walk_state_time[4]) / (walk_state_time[6] - walk_state_time[4]);
                left_forearm_ang = walk_hand_state_ang[2][1] + (walk_hand_state_ang[3][1] - walk_hand_state_ang[2][1]) * (walk_cnt - walk_state_time[4]) / (walk_state_time[6] - walk_state_time[4]);
                right_arm_ang = walk_hand_state_ang[2][2] + (walk_hand_state_ang[3][2] - walk_hand_state_ang[2][2]) * (walk_cnt - walk_state_time[4]) / (walk_state_time[6] - walk_state_time[4]);
                right_forearm_ang = walk_hand_state_ang[2][3] + (walk_hand_state_ang[3][3] - walk_hand_state_ang[2][3]) * (walk_cnt - walk_state_time[4]) / (walk_state_time[6] - walk_state_time[4]);
            }
            else
            {
                left_arm_ang = walk_hand_state_ang[3][0] + (walk_hand_state_ang[0][0] - walk_hand_state_ang[3][0]) * (walk_cnt - walk_state_time[6]) / (walk_state_time[7] - walk_state_time[6]);
                left_forearm_ang = walk_hand_state_ang[3][1] + (walk_hand_state_ang[0][1] - walk_hand_state_ang[3][1]) * (walk_cnt - walk_state_time[6]) / (walk_state_time[7] - walk_state_time[6]);
                right_arm_ang = walk_hand_state_ang[3][2] + (walk_hand_state_ang[0][2] - walk_hand_state_ang[3][2]) * (walk_cnt - walk_state_time[6]) / (walk_state_time[7] - walk_state_time[6]);
                right_forearm_ang = walk_hand_state_ang[3][3] + (walk_hand_state_ang[0][3] - walk_hand_state_ang[3][3]) * (walk_cnt - walk_state_time[6]) / (walk_state_time[7] - walk_state_time[6]);
            }
            if (take_coffee == TRUE)
            {
                left_arm_ang = 90;
                left_forearm_ang = 0;
            }
            return;
        }
    }
    walk_cnt = 3;
    left_thigh_ang = walk_state_ang[1][0];
    left_calf_ang = walk_state_ang[1][1];
    right_thigh_ang = walk_state_ang[1][2];
    right_calf_ang = walk_state_ang[1][3];
}

void walk_end()
{
    float dif_foot[4] = {0 - left_thigh_ang, 0 - left_calf_ang, 0 - right_thigh_ang, 0 - right_calf_ang};
    float dif_hand[4] = {0 - left_arm_ang, 0 - left_forearm_ang, 0 - right_arm_ang, 0 - right_forearm_ang};
    int div = 5;
    for (int i = 0; i < 4; i++)
    {
        dif_foot[i] /= div;
        dif_hand[i] /= div;
    }
    for (int i = 0; i < div; i++)
    {
        left_thigh_ang += dif_foot[0];
        left_calf_ang += dif_foot[1];
        right_thigh_ang += dif_foot[2];
        right_calf_ang += dif_foot[3];
        if (take_coffee == TRUE)
        {
            left_arm_ang = 90;
            left_forearm_ang = 0;
        }
        else
        {
            left_arm_ang += dif_hand[0];
            left_forearm_ang += dif_hand[1];
        }
        right_arm_ang += dif_hand[2];
        right_forearm_ang += dif_hand[3];

        display();
    }
    walk_cnt = 3;
    turn_cnt = 0;
}

void turn_around(float dif_ang)
{
    turn_cnt += 1.0;
    rot_ang[1] += dif_ang;
    for (int i = 0; i < 4; i++)
    {
        if (turn_cnt <= turn_feet_state_time[i + 1])
        {
            left_thigh_ang = turn_feet_state_ang[i][0] + (turn_feet_state_ang[i + 1][0] - turn_feet_state_ang[i][0]) * (turn_cnt - turn_feet_state_time[i]) / (turn_feet_state_time[i + 1] - turn_feet_state_time[i]);
            left_calf_ang = turn_feet_state_ang[i][1] + (turn_feet_state_ang[i + 1][1] - turn_feet_state_ang[i][1]) * (turn_cnt - turn_feet_state_time[i]) / (turn_feet_state_time[i + 1] - turn_feet_state_time[i]);
            right_thigh_ang = turn_feet_state_ang[i][2] + (turn_feet_state_ang[i + 1][2] - turn_feet_state_ang[i][2]) * (turn_cnt - turn_feet_state_time[i]) / (turn_feet_state_time[i + 1] - turn_feet_state_time[i]);
            right_calf_ang = turn_feet_state_ang[i][3] + (turn_feet_state_ang[i + 1][3] - turn_feet_state_ang[i][3]) * (turn_cnt - turn_feet_state_time[i]) / (turn_feet_state_time[i + 1] - turn_feet_state_time[i]);
            return;
        }
    }
    turn_cnt = 0.0;
    left_thigh_ang = turn_feet_state_ang[0][0];
    left_calf_ang = turn_feet_state_ang[0][1];
    right_thigh_ang = turn_feet_state_ang[0][2];
    right_calf_ang = turn_feet_state_ang[0][3];
}

void jump()
{
    for (int i = 0; i < 7; i++)
    {
        if (jump_cnt <= jump_feet_state_time[i + 1])
        {
            rot_ang[2] = jump_feet_state_ang[i][0] + (jump_feet_state_ang[i + 1][0] - jump_feet_state_ang[i][0]) * (jump_cnt - jump_feet_state_time[i]) / (jump_feet_state_time[i + 1] - jump_feet_state_time[i]);
            if (i == 2)
            {
                float t = jump_time_slice * (jump_cnt - jump_feet_state_time[i]);
                robot_pos[1] = 14.7 * t - 0.5 * 9.8 * t * t;
            }
            else if (i == 3)
            {
                float t = jump_time_slice * (jump_cnt - jump_feet_state_time[i]);
                robot_pos[1] = 11.025 - 0.5 * 9.8 * t * t;
            }
            else
                robot_pos[1] = jump_feet_state_ang[i][1] + (jump_feet_state_ang[i + 1][1] - jump_feet_state_ang[i][1]) * (jump_cnt - jump_feet_state_time[i]) / (jump_feet_state_time[i + 1] - jump_feet_state_time[i]);
            left_thigh_ang = jump_feet_state_ang[i][2] + (jump_feet_state_ang[i + 1][2] - jump_feet_state_ang[i][2]) * (jump_cnt - jump_feet_state_time[i]) / (jump_feet_state_time[i + 1] - jump_feet_state_time[i]);
            right_thigh_ang = left_thigh_ang;
            left_calf_ang = jump_feet_state_ang[i][3] + (jump_feet_state_ang[i + 1][3] - jump_feet_state_ang[i][3]) * (jump_cnt - jump_feet_state_time[i]) / (jump_feet_state_time[i + 1] - jump_feet_state_time[i]);
            right_calf_ang = left_calf_ang;
            left_feet_ang = jump_feet_state_ang[i][4] + (jump_feet_state_ang[i + 1][4] - jump_feet_state_ang[i][4]) * (jump_cnt - jump_feet_state_time[i]) / (jump_feet_state_time[i + 1] - jump_feet_state_time[i]);
            right_feet_ang = left_feet_ang;
            jump_cnt += 1.0;
            return;
        }
    }
    jump_cnt = 0.0;
    rot_ang[2] = jump_feet_state_ang[0][0];
    robot_pos[1] = jump_feet_state_ang[0][1];
    left_thigh_ang = jump_feet_state_ang[0][2];
    right_thigh_ang = left_thigh_ang;
    left_calf_ang = jump_feet_state_ang[0][3];
    right_calf_ang = left_calf_ang;
    left_feet_ang = jump_feet_state_ang[0][4];
    right_feet_ang = left_feet_ang;
}

void say_hi()
{
    for (int i = 0; i < 7; i++)
    {
        if (sayhi_cnt <= sayhi_state_time[i + 1])
        {
            right_arm_ang = sayhi_state_ang[i][0] + (sayhi_state_ang[i + 1][0] - sayhi_state_ang[i][0]) * (sayhi_cnt - sayhi_state_time[i]) / (sayhi_state_time[i + 1] - sayhi_state_time[i]);
            right_forearm_ang = sayhi_state_ang[i][1] + (sayhi_state_ang[i + 1][1] - sayhi_state_ang[i][1]) * (sayhi_cnt - sayhi_state_time[i]) / (sayhi_state_time[i + 1] - sayhi_state_time[i]);
            tpang = sayhi_state_ang[i][2] + (sayhi_state_ang[i + 1][2] - sayhi_state_ang[i][2]) * (sayhi_cnt - sayhi_state_time[i]) / (sayhi_state_time[i + 1] - sayhi_state_time[i]);
            ;
            sayhi_cnt += 1.0;
            return;
        }
    }
    sayhi_cnt = 0.0;
    right_arm_ang = 0;
    right_forearm_ang = 0;
    tpang = 0;
}

void my_reshape(int w, int h)
{
    width = w;
    height = h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, (double)w / (double)h, 1.5, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void check_coffee()
{
    float dis = sqrt((coffee_pos[0] + table_pos[0] - robot_pos[0]) * (coffee_pos[0] + table_pos[0] - robot_pos[0]) + (coffee_pos[2] + table_pos[2] - robot_pos[2]) * (coffee_pos[2] + table_pos[2] - robot_pos[2]));
    if (dis <= 12)
    {
        table_coffee = FALSE;
        take_coffee = TRUE;
        left_arm_ang = 90;
    }
}

void my_keyboard(unsigned char key, int x_pos, int y_pos)
{
    float x[3], y[3], z[3];
    int i;

    if(key=='+')
        head_ang+=1.0;
    if(key=='-')
        head_ang-=1.0;

    if (key == '1')
        view_mode = 1;
    if (key == '2')
        view_mode = 2;
    if (key == '3')
        view_mode = 3;
    if (key == '4')
        view_mode = 4;
    if (key == '0')
        view_mode = 0;
    if (key == '/')
        view_volume = !view_volume;
    if (key == 't')
    {
        eyeDx += -0.5; /* move left */
        for (i = 0; i < 3; i++)
            eye[i] += 0.5 * u[0][i];
    }
    if (key == 'y')
    {
        eyeDx += 0.5; /* move right */
        for (i = 0; i < 3; i++)
            eye[i] -= 0.5 * u[0][i];
    }
    if (key == 'u')
    {
        eyeDy += 0.5; /* move up */
        for (i = 0; i < 3; i++)
            eye[i] -= 0.5 * u[1][i];
    }
    if (key == 'i')
    {
        eyeDy += -0.5; /* move down */
        for (i = 0; i < 3; i++)
            eye[i] += 0.5 * u[1][i];
    }

    if (key == 'o')
    {
        eyeDz += 0.5; /* move forward */
        for (i = 0; i < 3; i++)
            eye[i] -= 0.5 * u[2][i];
    }
    if (key == 'p')
    {
        eyeDz += -0.5; /* move backward */
        for (i = 0; i < 3; i++)
            eye[i] += 0.5 * u[2][i];
    }
    if (key == '[') /* zoom in */
    {
        zoom_fac += -0.01;
        zoom_fac = max(0.1, zoom_fac);
    }
    if (key == ']') /* zoom out */
    {
        zoom_fac += 0.01;
        zoom_fac = min(1.5, zoom_fac);
    }
    if (key == 'z')
    { /* pitching */
        eyeAngx += 5.0;
        if (eyeAngx > 360.0)
            eyeAngx -= 360.0;
        y[0] = u[1][0] * cv - u[2][0] * sv;
        y[1] = u[1][1] * cv - u[2][1] * sv;
        y[2] = u[1][2] * cv - u[2][2] * sv;

        z[0] = u[2][0] * cv + u[1][0] * sv;
        z[1] = u[2][1] * cv + u[1][1] * sv;
        z[2] = u[2][2] * cv + u[1][2] * sv;

        for (i = 0; i < 3; i++)
        {
            u[1][i] = y[i];
            u[2][i] = z[i];
        }
    }
    if (key == 'Z')
    {
        eyeAngx += -5.0;
        if (eyeAngx < 0.0)
            eyeAngx += 360.0;
        y[0] = u[1][0] * cv + u[2][0] * sv;
        y[1] = u[1][1] * cv + u[2][1] * sv;
        y[2] = u[1][2] * cv + u[2][2] * sv;

        z[0] = u[2][0] * cv - u[1][0] * sv;
        z[1] = u[2][1] * cv - u[1][1] * sv;
        z[2] = u[2][2] * cv - u[1][2] * sv;

        for (i = 0; i < 3; i++)
        {
            u[1][i] = y[i];
            u[2][i] = z[i];
        }
    }
    if (key == 'x')
    { /* heading */
        eyeAngy += 5.0;
        if (eyeAngy > 360.0)
            eyeAngy -= 360.0;
        for (i = 0; i < 3; i++)
        {
            x[i] = cv * u[0][i] - sv * u[2][i];
            z[i] = sv * u[0][i] + cv * u[2][i];
        }
        for (i = 0; i < 3; i++)
        {
            u[0][i] = x[i];
            u[2][i] = z[i];
        }
    }
    if (key == 'X')
    {
        eyeAngy += -5.0;
        if (eyeAngy < 0.0)
            eyeAngy += 360.0;
        for (i = 0; i < 3; i++)
        {
            x[i] = cv * u[0][i] + sv * u[2][i];
            z[i] = -sv * u[0][i] + cv * u[2][i];
        }
        for (i = 0; i < 3; i++)
        {
            u[0][i] = x[i];
            u[2][i] = z[i];
        }
    }
    if (key == 'c')
    { /* rolling */
        eyeAngz += 5.0;
        if (eyeAngz > 360.0)
            eyeAngz -= 360.0;
        for (i = 0; i < 3; i++)
        {
            x[i] = cv * u[0][i] - sv * u[1][i];
            y[i] = sv * u[0][i] + cv * u[1][i];
        }
        for (i = 0; i < 3; i++)
        {
            u[0][i] = x[i];
            u[1][i] = y[i];
        }
    }
    if (key == 'C')
    {
        eyeAngz += -5.0;
        if (eyeAngz < 0.0)
            eyeAngz += 360.0;
        for (i = 0; i < 3; i++)
        {
            x[i] = cv * u[0][i] + sv * u[1][i];
            y[i] = -sv * u[0][i] + cv * u[1][i];
        }
        for (i = 0; i < 3; i++)
        {
            u[0][i] = x[i];
            u[1][i] = y[i];
        }
    }

    // 走路
    if (key == 'w' || key == 'W')
        walk();
    // 轉圈
    if (key == 'a' || key == 'A')
        turn_around(-3);
    if (key == 'd' || key == 'D')
        turn_around(3);
    // 拿咖啡
    if (key == 's' || key == 'S')
    {
        if (table_coffee == TRUE)
            check_coffee();
        else if (take_coffee == TRUE)
        {
            coffee_overthrow = TRUE;
            walk_end();
        }
    }

    // 跳
    if (key == 'j' || key == 'J')
    {
        jump_cnt += 1.0;
        while (jump_cnt != 0)
        {
            jump();
            display();
        }
    }
    // 招手打招呼
    if (key == 'h' || key == 'H')
    {
        sayhi_cnt += 1.0;
        sayhi = TRUE;
        while (sayhi_cnt != 0)
        {
            say_hi();
            display();
        }
        sayhi = FALSE;
    }

    display();
}

void myinit()
{
    if (sphere == NULL)
    {
        sphere = gluNewQuadric();
        gluQuadricDrawStyle(sphere, GLU_FILL);
        gluQuadricNormals(sphere, GLU_SMOOTH);
    }
    if (mycircle == NULL)
    {
        mycircle = gluNewQuadric();
        gluQuadricDrawStyle(mycircle, GLU_FILL);
        gluQuadricNormals(mycircle, GLU_SMOOTH);
    }
    if (cylind == NULL)
    {
        cylind = gluNewQuadric();
        gluQuadricDrawStyle(cylind, GLU_FILL);
        gluQuadricNormals(cylind, GLU_SMOOTH);
    }
    /*--- Draw a cylinder ---*/
    /*---- Compute cos(5.0) and sin(5.0) ----*/
    cv = cos(5.0 * PI / 180.0);
    sv = sin(5.0 * PI / 180.0);
    /*---- Copy eye position ---*/
    eye[0] = Eye[0];
    eye[1] = Eye[1];
    eye[2] = Eye[2];

    glClearColor(background_color[0], background_color[1], background_color[2], 1.0); /*set the background color BLACK */
    /*Clear the Depth & Color Buffers */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST); /*Enable depth buffer for shading computing */
    glEnable(GL_NORMALIZE);

    /*-----Define some global lighting status -----*/
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);    /* local viewer */
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient); /*global ambient*/

    /*-----Enable face culling -----*/
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    // glEnable(GL_LIGHTING); /*Enable lighting effects */
    //glEnable(GL_LIGHT0); /*Turn on light0 */
    //glEnable(GL_LIGHT1); /*Turn on light1 */
    // glEnable(GL_LIGHT2); /*Turn on light2 */
    //glEnable(GL_LIGHT3); /*Turn on light3 */
    /*-----Define light0 ---------*/
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lit_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lit_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, lit_direction);
    /*-----Define light1 ---------*/
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lit1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lit1_specular);
      /*-----Define light2 ---------*/
  glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, lit2_cutoff);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, lit2_diffuse);
  glLightfv(GL_LIGHT2, GL_SPECULAR, lit2_specular);
  glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, lit2_exponent);
        /*-----Define light3 ---------*/
  glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, lit2_cutoff);
  glLightfv(GL_LIGHT3, GL_DIFFUSE, lit2_diffuse);
  glLightfv(GL_LIGHT3, GL_SPECULAR, lit2_specular);
  glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, lit2_exponent);
    glFlush(); /*Enforce window system display the results*/
}
void keyUp(unsigned char key, int x, int y)
{
    if (key == 'w' || key == 'W' || key == 'a' || key == 'A' || key == 'd' || key == 'D')
    {
        walk_end();
    }
}
int main(int argc, char **argv)
{
    // scanf("%d",&tmp);
    /*-----Initialize the GLUT environment-------*/
    glutInit(&argc, argv);

    /*-----Depth buffer is used, be careful !!!----*/
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("robot");

    myinit(); /*---Initialize other state varibales----*/

    /*----Associate callback func's whith events------*/
    glutDisplayFunc(display);
    glutReshapeFunc(my_reshape);
    glutKeyboardFunc(my_keyboard);
    glutKeyboardUpFunc(keyUp);
    
    glutMainLoop();
}