/******************************************************************
 * This program illustrates the fundamental instructions for handling
 * mouse and keyboeard events as well as menu buttons.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glut.h>

#define    SIZEX   4000
#define    SIZEY   4000

#define    MY_QUIT -1
#define    MY_CLEAR -2
#define    MY_SAVE  -3
#define    MY_BLEND -4
#define    MY_LOAD  -5

#define    WHITE   1
#define    RED     2
#define    GREEN   3
#define    BLUE    4

#define    POINT   1
#define    LINE    2
#define    POLYGON 3
#define    CIRCLE  4
#define    CURVE   5
#define    TRIANGLE   6
#define    RECTANGLE   7

#define    FILL 1
#define    LINE 2

#define    SHOW 1
#define    HIDE 2

#define    TEMP 1
#define    FOREVER 2

#define    YES 1
#define    NO 2

typedef    int   menu_t;
menu_t     top_m, file_m, type_m, fontstyle_m, fill_mode_m, circle_m,polygon_m, grid_m,triangle_m,rectangle_m;

int        height = 512, width = 1024;
int         saved_height = 512, saved_width = 1024;
unsigned char  image[SIZEX * SIZEY][4];         //�ΨӦs�ϥΪ�save 
unsigned char  tp_image[SIZEX * SIZEY][4];      //�ΨӼȦs����L�B�z
unsigned char  always_load[SIZEX * SIZEY][4];   //�ΨӦbidle�ɪ��Ȧs


int        fill_mode = FILL;        //�񺡩Τ���
char*      mode = "shape";          //default�e�� �i�ରshape�Btext
int        obj_type = POINT;        //default�e�I �i�ର POINT�BLINE�BPOLYGON�BCIRCLE�BCURVE�BTRIANGLE�BRECTANGLE
int        font_style = 2;          //�r�� �i�ର/*GLUT_BITMAP_9_BY_15 �B GLUT_BITMAP_8_BY_13 ...
int        grid = SHOW;             //�O�_��ܺ���
int        enable = NO;             //�ΨӨ����ԤT���ΩM�|��ήɡA�e��W��bar
int        choosing_line_style = NO;//�P�_�O�_�b��u���˦�
int        choosing_now = NO;       //�Ψ����U�P�_�O�_���_�u���˦���
int        line_style = 0xFFFF;     //�u���˦�
int        first = 0;               //�����O�_���e�Ϫ��Ĥ@���I
int        vertex[128][2];          //�s�e�Ϯɪ����I
int        side = 0;                //�h����䪺�ƶq

float      pnt_size = 5.0;          //�I���j�p
float      line_width = 1.0;        //�u���ʫ�
float      circle_radius = 5.0;     //�ꪺ�b�|
float      bar_scale = 0.8;         //bar�b�ù�����Ҧ�m(0.8~1.0)

float      background_color[3] = { 1.0,1.0,1.0 };   //�e���I���C��
float      bar_color[3] = { 0.925,0.91,0.965 };     //�W��bar���I����
float      choose_color[3] = { 0.74,0.66,0.776 };   //���s�C��
float      choosed_color[3] = { 1.0,1.0,1.0 };      //�Q�襤�����s��
float      font_color[3] = { 0.01,0.01,0.01 };      //bar�W�r���C��
float      color_arr[8][3] = {                      //����C��ت��K���C��
                              {1.0,0.0,0.0},    //red
                              {1.0,0.5,0.0},    //orange
                              {1.0,1.0,0.0},    //yellow
                              {0.0,1.0,0.0},    //green
                              {0.0,1.0,1.0},
                              {0.0,0.0,1.0},    //blue
                              {1.0,0.0,1.0},    //purple
                              {0.01,0.01,0.01}, //black
};
float      myColor[3] = { 0.01,0.01,0.01 };         //�ϥΪ̿襤���K���C�⤤���Y�C��
float      use_color[3] = { 0.01,0.01,0.01 };       //�u���ϥΪ��C��(�]�i��ղ`�L)
float      grid_color[3] = { 0.74,0.66,0.776 };     //��u�C��

int        pos_x = -1, pos_y = -1;                  //�s�e�Ϯɪ����Ц�m
int        shape_pos[4];                            //�e�ϼҦ��ت����U(x,y)�M�k�W(x,y)
int        text_pos[4];                             //��r�Ҧ��ت����U(x,y)�M�k�W(x,y)
int        colorBlock_pos[4];                       //�K�C��j�ت����U(x,y)�M�k�W(x,y)
int        color_pos[8][4];                         //�C���C��ت����U(x,y)�M�k�W(x,y)
int        color_depth_pos[4];                      //�C��`�׮ت����U(x,y)�M�k�W(x,y)
int        plus_width_pos[4];                       //�`��+���s�����U(x,y)�M�k�W(x,y)
int        minus_width_pos[4];                      //�`��-���s�����U(x,y)�M�k�W(x,y)
int        plus_size_pos[4];                        //�I�j�p+���s�����U(x,y)�M�k�W(x,y)
int        minus_size_pos[4];                       //�I�j�p-���s�����U(x,y)�M�k�W(x,y)
int        plus_radius_pos[4];                      //��b�|+���s�����U(x,y)�M�k�W(x,y)
int        minus_radius_pos[4];                     //��b�|-���s�����U(x,y)�M�k�W(x,y)
int        line_style_pos[4];                       //�u�˦��ت����U(x,y)�M�k�W(x,y)
int        line_block_pos[4];                       //�I�U�u�˦��ث�X�{���j�ت����U(x,y)�M�k�W(x,y)
int        line_style_ypos[3][2];                   //�����C�ؼ˦��b�j�ؤ���y��m
int        mouse_x;                                 //���з��e��m
int        mouse_y;                                 //���з��e��m



/*���*/
void display_func(void)
{
    glFlush();
}

/*���m�ɰ���A�b����@����۹��Ш�*/
void idle_func(void)
{
    //���Ȧs��ӵe��
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE,
        always_load);

    //�b���Ц�m�e��
    glColor3f(use_color[0], use_color[1], use_color[2]);
    glPolygonMode(GL_FRONT, GL_LINE);
    glPolygonMode(GL_BACK, GL_LINE);
    float theta;
    glLineWidth(2.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        theta = i * 3.142 / 180;
        glVertex2f(mouse_x + 5.0 * cos(theta), mouse_y + 5.0 * sin(theta));
    }
    glEnd();
    glFlush();

    glRasterPos2i(0, 0);
    glDrawPixels(width, height,GL_RGBA, GL_UNSIGNED_BYTE,always_load);
}

void init_window();
void file_save(int mode);
void my_reshape(int new_w, int new_h)
{
    
    //glReadPixels(0, 0, width, height * bar_scale, GL_RGBA, GL_UNSIGNED_BYTE,
    //    tp_image);
    //for (i = 0; i < SIZEX; i++)
    //    for (j = 0; j < SIZEY; j++)
    //    {
    //        if (tp_image[i * width + j][0] == 189 &&
    //            tp_image[i * width + j][1] == 168 &&
    //            tp_image[i * width + j][2] == 198) tp_image[i * width + j][3] = 0;  //�ư���l�u(�N�䤣�z���׳]��0->�z��)
    //        else if (tp_image[i * width + j][0] == 255 &&
    //            tp_image[i * width + j][1] == 255 &&
    //            tp_image[i * width + j][2] == 255) tp_image[i * width + j][3] = 0;  //�ư��I��(�N�䤣�z���׳]��0->�z��)
    //        else tp_image[i * width + j][3] = 255;                                  //�u�d�U�ϥΪ̵e��(�N�䤣�z���׳]��1)
    //    }
    saved_height = height;
    saved_width = width;
    height = new_h;
    width = new_w;
    for (int i = 0; i < SIZEX; i++)
        for (int j = 0; j < SIZEY; j++)
        {
            tp_image[i * width + j][0] = image[i *saved_height/width + j][0];
            tp_image[i * width  + j][1] = image[i * saved_height / width + j][1];
            tp_image[i * width  + j][2] = image[i * saved_height / width + j][2];
            tp_image[i * width  + j][3] = image[i * saved_height / width + j][3];
        }
    for (int i = 0; i < SIZEX; i++)
        for (int j = 0; j < SIZEY; j++)
        {
            image[i *  width + j][0] = tp_image[i *width + j][0];
            image[i *width + j][1] = tp_image[i *width + j][1];
            image[i * width + j][2] = tp_image[i* width + j][2];
            image[i *  width + j][3] = tp_image[i *width + j][3];
        }
    init_window();

    file_load(FOREVER);
    glutPostRedisplay();   /*---Trigger Display event for redisplay window*/
}

/*�L�X��r      x,y:��m  string:�ݦL�X���r��   font_style:�r��   ftcolor:�r���C��*/
void print_text(int x, int y, char* string, int font_style, float* ftcolor)
{
    glColor3f(*(&ftcolor[0]), *(&ftcolor[1]), *(&ftcolor[2]));
    glRasterPos2f(x, y); //define position on the screen

    /*��r�˦�:
       GLUT_BITMAP_9_BY_15 : 2
       GLUT_BITMAP_8_BY_13 : 3
       GLUT_BITMAP_TIMES_ROMAN_10 : 4
       GLUT_BITMAP_TIMES_ROMAN_24 : 5
       GLUT_BITMAP_HELVETICA_10 : 6
       GLUT_BITMAP_HELVETICA_12 : 7
       GLUT_BITMAP_HELVETICA_18 : 8
     */
    while (*string) {
        glutBitmapCharacter(font_style, *string++);
    }
    glFlush();
}

/*����L�ƥ�o�ͮɪ�function     key:���U����   x,y:��m*/
void keyboard(unsigned char key, int x, int y)
{
    if (mode == "text") //�Y����r�Ҧ��h��X��r
    {
        print_text(pos_x, height-pos_y, &key, font_style,&use_color);
        if (font_style == 2 || font_style == 5 || font_style == 8)
            pos_x += 10; //��J�@�Ӧr��V�k���A���ݿ�U�@�Ӧr
        else
            pos_x += 8;
    }
    else if (key == 'Q' || key == 'q') 
        exit(0); //�_�h���Uq�h�h�X
}

/*�e�h���*/
void draw_polygon()
{
    int  i;
    if (fill_mode==FILL)    //�Y���񺡼Ҧ�
    {
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);
    }
    else                    //�Y���u�Ҧ�
    {
        glPolygonMode(GL_FRONT, GL_LINE);
        glPolygonMode(GL_BACK, GL_LINE);
    }
    glBegin(GL_POLYGON);
    for (i = 0; i < side; i++)
        glVertex2f(vertex[i][0], height - vertex[i][1]);
    glEnd();
    glFinish();
    side = 0;    /*��u�p���k�s*/
}

/*�e���*/
void draw_circle(int x,int y)
{
    if (fill_mode == FILL)    //�Y���񺡼Ҧ�
    {
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);
    }
    else
    {
        glPolygonMode(GL_FRONT, GL_LINE);
        glPolygonMode(GL_BACK, GL_LINE);
    }
    float theta; 
    float width = min(line_width, circle_radius / 5);

    glLineWidth(width);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        theta = i * 3.142 / 180;
        glVertex2f(x + circle_radius *cos(theta), height - y + circle_radius * sin(theta));
    }
    glEnd();
}

void bar()
{
    //bar�϶�
    glColor3f(bar_color[0], bar_color[1], bar_color[2]);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);

    glBegin(GL_POLYGON);
    glVertex2f(0, height * bar_scale);
    glVertex2f(0, height);
    glVertex2f(width, height);
    glVertex2f(width, height * bar_scale);
    glEnd();

    //bar�ؽu
    glColor3f(choose_color[0], choose_color[1], choose_color[2]);
    glLineStipple(6, 0xAFAF);//�w�q�u���˦��Afactor, pattern(1�e0���e�B�q�C�줸�}�l)
    glLineWidth(3.0);     //�w�q�u���e��
    glBegin(GL_LINES);    //�}�l�e�u
    glVertex2f(0, height * bar_scale + 3);
    glVertex2f(width, height * bar_scale + 3);
    glEnd();

    glBegin(GL_LINES);   
    glVertex2f(0, height - 3);
    glVertex2f(width, height - 3);
    glEnd();

    glBegin(GL_LINES);    
    glVertex2f(2, height * bar_scale);
    glVertex2f(2, height);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(width - 2, height * bar_scale);
    glVertex2f(width - 2, height);
    glEnd();

    int tp = (height * (1 - bar_scale) - 60) / 2;
    int tp2 = (height * (1 - bar_scale) - 60) / 2;

    //�e�ϼҦ��϶�
    if (mode == "shape")//�P�_���A�M�w�C��
        glColor3f(choosed_color[0], choosed_color[1], choosed_color[2]);
    else
        glColor3f(choose_color[0], choose_color[1], choose_color[2]);
    glBegin(GL_POLYGON);
    glVertex2f(20, height - tp - 60);
    glVertex2f(20, height - tp);
    glVertex2f(80, height - tp);
    glVertex2f(80, height - tp - 60);
    glEnd();
    shape_pos[0] = 20;
    shape_pos[1] = height - tp - 60;
    shape_pos[2] = 80;
    shape_pos[3] = height - tp;
    //�T���ζH�x��
    glColor3f(font_color[0], font_color[1], font_color[2]);
    glBegin(GL_POLYGON);
    glVertex2f(30, height - tp - 45);
    glVertex2f(50, height - tp - 15);
    glVertex2f(70, height - tp - 45);
    glEnd();


    //��r�Ҧ��϶�
    if (mode == "text")//�P�_���A�M�w�C��
        glColor3f(choosed_color[0], choosed_color[1], choosed_color[2]);
    else
        glColor3f(choose_color[0], choose_color[1], choose_color[2]);
    glBegin(GL_POLYGON);
    glVertex2f(100, height - tp - 60);
    glVertex2f(100, height - tp);
    glVertex2f(160, height - tp);
    glVertex2f(160, height - tp - 60);
    glEnd();
    text_pos[0] = 100;
    text_pos[1] = height - tp - 60;
    text_pos[2] = 160;
    text_pos[3] = height - tp;
    //Aa�H�x��r
    print_text(115, height - tp - 38, "Aa", 5, &font_color);

    //��ܥثe�C�⪺�϶�
    glColor3f(use_color[0], use_color[1], use_color[2]);
    glBegin(GL_POLYGON);
    glVertex2f(180, height - tp - 60);
    glVertex2f(180, height - tp);
    glVertex2f(240, height - tp);
    glVertex2f(240, height - tp - 60);
    glEnd();

    //����C�⪺�϶�
    glColor3f(bar_color[0], bar_color[1], bar_color[2]);
    glBegin(GL_POLYGON);
    glVertex2f(260, height - tp - 60);
    glVertex2f(260, height - tp);
    glVertex2f(365, height - tp);
    glVertex2f(365, height - tp - 60);
    glEnd();
    colorBlock_pos[0] = 180;
    colorBlock_pos[1] = height - tp - 60;
    colorBlock_pos[2] = 365;
    colorBlock_pos[3] = height - tp;

    //�e�W��|���C��
    int x = 265;
    for (int i = 0; i < 4; i++)
    {
        glColor3f(color_arr[i][0], color_arr[i][1], color_arr[i][2]);
        glBegin(GL_POLYGON);
        glVertex2f(x, height - tp - 25);
        glVertex2f(x, height - tp - 5);
        glVertex2f(x + 20, height - tp - 5);
        glVertex2f(x + 20, height - tp - 25);
        glEnd();
        color_pos[i][0] = x;
        color_pos[i][1] = height - tp - 25;
        color_pos[i][2] = x + 20;
        color_pos[i][3] = height - tp - 5;
        x += 25;
    }
    //�e�U��|���C��
    x = 265;
    for (int i = 4; i < 8; i++)
    {
        glColor3f(color_arr[i][0], color_arr[i][1], color_arr[i][2]);
        glBegin(GL_POLYGON);
        glVertex2f(x, height - tp - 55);
        glVertex2f(x, height - tp - 35);
        glVertex2f(x + 20, height - tp - 35);
        glVertex2f(x + 20, height - tp - 55);
        glEnd();
        color_pos[i][0] = x;
        color_pos[i][1] = height - tp - 55;
        color_pos[i][2] = x + 20;
        color_pos[i][3] = height - tp - 35;
        x += 25;
    }

    //�C��`�׿�ܮ�
    x = 385;
    glShadeModel(GL_SMOOTH);   //�ΨӺ��h
    glBegin(GL_POLYGON);
    glColor3f(0.99, 0.99, 0.99);   // white
    glVertex2f(x, height - tp - 30);
    glVertex2f(x, height - tp);
    glColor3f(myColor[0], myColor[1], myColor[2]);  //�ϥΪ̿諸�K��⤧�@
    glVertex2f(x + 60, height - tp);
    glVertex2f(x + 60, height - tp - 30);
    glEnd();
    //����b�e(�k�b)
    glBegin(GL_POLYGON);
    glVertex2f(x + 60, height - tp - 30);
    glVertex2f(x + 60, height - tp);
    glColor3f(0.01, 0.01, 0.01);   // black
    glVertex2f(x + 120, height - tp);
    glVertex2f(x + 120, height - tp - 30);
    glEnd();
    color_depth_pos[0] = x;
    color_depth_pos[1] = height - tp - 30;
    color_depth_pos[2] = x + 120;
    color_depth_pos[3] = height - tp;

    //��ܽu�ʫת��϶�
    glColor3f(font_color[0], font_color[1], font_color[2]);
    glLineStipple(1, 0xFFFF);      //�w�q�u���˦��Afactor, pattern(1�e0���e�B�q�C�줸�}�l)
    glLineWidth(line_width);
    glBegin(GL_LINES);
    glVertex2f(x, height - tp - 48);
    glVertex2f(x + 105, height - tp - 48);
    glEnd();

    //�ʫ׽վ���s
    //-���s
    x += 110;
    glColor3f(choose_color[0], choose_color[1], choose_color[2]);
    glBegin(GL_POLYGON);
    glVertex2f(x, height - tp - 60);
    glVertex2f(x, height - tp - 50);
    glVertex2f(x + 10, height - tp - 50);
    glVertex2f(x + 10, height - tp - 60);
    glEnd();
    minus_width_pos[0] = x;
    minus_width_pos[1] = height - tp - 60;
    minus_width_pos[2] = x + 10;
    minus_width_pos[3] = height - tp - 50;
    print_text(x, height - tp - 60, "-", 2, &font_color);
    //+���s
    glColor3f(choose_color[0], choose_color[1], choose_color[2]);
    glBegin(GL_POLYGON);
    glVertex2f(x, height - tp - 45);
    glVertex2f(x, height - tp - 35);
    glVertex2f(x + 10, height - tp - 35);
    glVertex2f(x + 10, height - tp - 45);
    glEnd();
    plus_width_pos[0] = x;
    plus_width_pos[1] = height - tp - 45;
    plus_width_pos[2] = x + 10;
    plus_width_pos[3] = height - tp - 35;
    print_text(x, height - tp - 45, "+", 2, &font_color);

    //��ܶ�j�p���϶�
    x += 45;
    glColor3f(font_color[0], font_color[1], font_color[2]);
    draw_circle(x, tp + 10);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);

    //��j�p�վ���s
    //-���s
    x += 30;
    glColor3f(choose_color[0], choose_color[1], choose_color[2]);
    glBegin(GL_POLYGON);
    glVertex2f(x, height - tp - 25);
    glVertex2f(x, height - tp - 15);
    glVertex2f(x + 10, height - tp - 15);
    glVertex2f(x + 10, height - tp - 25);
    glEnd();
    minus_radius_pos[0] = x;
    minus_radius_pos[1] = height - tp - 25;
    minus_radius_pos[2] = x + 10;
    minus_radius_pos[3] = height - tp - 15;
    print_text(x, height - tp - 25, "-", 2, &font_color);
    //+���s
    glColor3f(choose_color[0], choose_color[1], choose_color[2]);
    glBegin(GL_POLYGON);
    glVertex2f(x, height - tp - 10);
    glVertex2f(x, height - tp);
    glVertex2f(x + 10, height - tp);
    glVertex2f(x + 10, height - tp - 10);
    glEnd();
    plus_radius_pos[0] = x;
    plus_radius_pos[1] = height - tp - 10;
    plus_radius_pos[2] = x + 10;
    plus_radius_pos[3] = height - tp;
    print_text(x, height - tp - 10, "+", 2, &font_color);

    //����I�j�p���϶�
    x -= 30;
    glColor3f(font_color[0], font_color[1], font_color[2]);
    glPointSize(pnt_size);
    glBegin(GL_POINTS);
    glVertex2f(x, height - tp - 48);
    glEnd();

    //�I�j�p�վ���s
    //-���s
    x += 30;
    glColor3f(choose_color[0], choose_color[1], choose_color[2]);
    glBegin(GL_POLYGON);
    glVertex2f(x, height - tp - 60);
    glVertex2f(x, height - tp - 50);
    glVertex2f(x + 10, height - tp - 50);
    glVertex2f(x + 10, height - tp - 60);
    glEnd();
    minus_size_pos[0] = x;
    minus_size_pos[1] = height - tp - 60;
    minus_size_pos[2] = x + 10;
    minus_size_pos[3] = height - tp - 50;
    print_text(x, height - tp - 60, "-", 2, &font_color);
    //+���s
    glColor3f(choose_color[0], choose_color[1], choose_color[2]);
    glBegin(GL_POLYGON);
    glVertex2f(x, height - tp - 45);
    glVertex2f(x, height - tp - 35);
    glVertex2f(x + 10, height - tp - 35);
    glVertex2f(x + 10, height - tp - 45);
    glEnd();
    plus_size_pos[0] = x;
    plus_size_pos[1] = height - tp - 45;
    plus_size_pos[2] = x + 10;
    plus_size_pos[3] = height - tp - 35;
    print_text(x, height - tp - 45, "+", 2, &font_color);


    //��ܽu���˦����϶�
    x += 30;
    glColor3f(choosed_color[0], choosed_color[1], choosed_color[2]);
    glBegin(GL_POLYGON);
    glVertex2f(x, height - tp - 16);
    glVertex2f(x, height - tp);
    glVertex2f(x + 130, height - tp);
    glVertex2f(x + 130, height - tp - 16);
    glEnd();
    //�k��V�Uv�ê��϶�
    glColor3f(choose_color[0], choose_color[1], choose_color[2]);
    glBegin(GL_POLYGON);
    glVertex2f(x + 130, height - tp - 16);
    glVertex2f(x + 130, height - tp);
    glVertex2f(x + 146, height - tp);
    glVertex2f(x + 146, height - tp - 16);
    glEnd();
    line_style_pos[0] = x;
    line_style_pos[1] = height - tp - 16;
    line_style_pos[2] = x + 146;
    line_style_pos[3] = height - tp;
    print_text(x + 133, height - tp - 12, "v", 2, &font_color);

    if (choosing_line_style == YES)//�Y�O�b��u���˦��h�e�X��ܮ�
    {
        //��u��
        glColor3f(choosed_color[0], choosed_color[1], choosed_color[2]);
        glBegin(GL_POLYGON);
        glVertex2f(x, height - tp - 60);
        glVertex2f(x, height - tp - 15);
        glVertex2f(x + 130, height - tp - 15);
        glVertex2f(x + 130, height - tp - 60);
        glEnd();

        x += 5;
        //�˦��@
        glColor3f(font_color[0], font_color[1], font_color[2]);
        glLineStipple(6, 0x0F0F);
        glLineWidth(1.5);
        glBegin(GL_LINES);    
        glVertex2f(x, height - tp - 52.5);
        glVertex2f(x + 120, height - tp - 52.5);
        glEnd();
        line_style_ypos[0][0] = height - tp - 60;
        line_style_ypos[0][1] = height - tp - 45;
        //�˦��G
        glLineStipple(6, 0xAFAF);
        glBegin(GL_LINES);   
        glVertex2f(x, height - tp - 37.5);
        glVertex2f(x + 120, height - tp - 37.5);
        glEnd();
        line_style_ypos[1][0] = height - tp - 45;
        line_style_ypos[1][1] = height - tp - 30;
        //�˦��T
        glLineStipple(6, 0xFFFF);
        glBegin(GL_LINES);
        glVertex2f(x, height - tp - 22.5);
        glVertex2f(x + 120, height - tp - 22.5);
        glEnd();
        line_style_ypos[2][0] = height - tp - 30;
        line_style_ypos[2][1] = height - tp - 15;

        line_block_pos[0] = x;
        line_block_pos[1] = height - tp - 60;
        line_block_pos[2] = x + 130;
        line_block_pos[3] = height - tp - 15;

    }
    else
        x += 5;
    //�e�X���e�u���˦�
    glColor3f(font_color[0], font_color[1], font_color[2]);
    glLineStipple(6, line_style);
    glLineWidth(1.5); 
    glBegin(GL_LINES);
    glVertex2f(x, height - tp - 8);
    glVertex2f(x + 120, height - tp - 8);
    glEnd();

    glFlush();
}

/*�e��u*/
void draw_grid()
{
    glColor3f(grid_color[0],grid_color[1],grid_color[2]);
    glLineStipple(1, 0xFFFF);
    glLineWidth(1.0);
    //�e��(|)�u
    for (int i = 0; i < width; i+=10)
    {
        glBegin(GL_LINES);
        glVertex2f(i, 0);
        glVertex2f(i, height);
        glEnd();
    }
    //�e��(-)�u
    for (int i =0 ; i < height; i += 10)
    {
        glBegin(GL_LINES);
        glVertex2f(0, i);
        glVertex2f(width, i);
        glEnd();
    }
}

//��l��window
void init_window(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (double)width, 0.0, (double)height);//�ഫ�y�ХH���U�������I�Ax:0~width,y:0~height
    glViewport(0, 0, width, height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //�]�w�I����
    glClearColor(background_color[0], background_color[1], background_color[2], 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND);
    glEnable(GL_LINE_STIPPLE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //�Y����u�Ҧ��h�e��u
    if (grid == SHOW)
        draw_grid();
    
    //�e�W�誺bar
    bar();

    glEnd();
    glFlush();
}

//�x�s���e�e��
void file_save(int mode)
{
    int i, j;
    if (mode == TEMP)   //�B�z�ʧ@�ɥΨ쪺�Ȯ��x�s
    {
        glReadPixels(0, 0, width, height*bar_scale, GL_RGBA, GL_UNSIGNED_BYTE,
            tp_image);
        for (i = 0; i < SIZEX; i++)   
            for (j = 0; j < SIZEY; j++)
            {
                if (tp_image[i * width + j][0] == 189 &&
                    tp_image[i * width + j][1] == 168 &&
                    tp_image[i * width + j][2] == 198) tp_image[i * width + j][3] = 0;  //�ư���l�u(�N�䤣�z���׳]��0->�z��)
                else if (tp_image[i * width + j][0] == 255 &&
                    tp_image[i * width + j][1] == 255 &&
                    tp_image[i * width + j][2] == 255) tp_image[i * width + j][3] = 0;  //�ư��I��(�N�䤣�z���׳]��0->�z��)
                else tp_image[i * width + j][3] = 255;                                  //�u�d�U�ϥΪ̵e��(�N�䤣�z���׳]��1)
            }
    }
    else if (mode == FOREVER)   //�ϥΪ̭n�D���x�s
    {
        glReadPixels(0, 0, width, height * bar_scale, GL_RGBA, GL_UNSIGNED_BYTE,
            image);
        for (i = 0; i < SIZEX; i++) 
            for (j = 0; j < SIZEY; j++)
            {
                if (image[i * width + j][0] == 189 &&
                    image[i * width + j][1] == 168 &&
                    image[i * width + j][2] == 198) image[i * width + j][3] = 0;  //�ư���l�u(�N�䤣�z���׳]��0->�z��)
                else if (image[i * width + j][0] == 255 &&
                    image[i * width + j][1] == 255 &&
                    image[i * width + j][2] == 255) image[i * width + j][3] = 0;  //�ư��I��(�N�䤣�z���׳]��0->�z��)
                else image[i * width + j][3] = 255;                               //�u�d�U�ϥΪ̵e��(�N�䤣�z���׳]��1)
            }
    }
}

/*�N�s�U���e���e�W�h*/
void file_load(int mode)
{
    init_window();
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //gluOrtho2D(0.0, (double)width, 0.0, (double)height * bar_scale);
    //glViewport(0, 0, width, height * bar_scale);
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();

    if (mode == TEMP)
        glDrawPixels(width, height*bar_scale,GL_RGBA, GL_UNSIGNED_BYTE,tp_image);
    else if (mode == FOREVER)
        glDrawPixels(width,height*bar_scale,GL_RGBA, GL_UNSIGNED_BYTE,image);
}

/*menu����file�B�z*/
void file_func(int value)
{
    if (value == MY_QUIT) 
        exit(0);
    else if (value == MY_CLEAR) /*���m�e��*/
        init_window();
    else if (value == MY_SAVE)  /*�ϥΪ̦s��*/
        file_save(FOREVER);
    else if (value == MY_LOAD)  /*�ϥΪ�Ū�����e�s�����*/
        file_load(FOREVER);
    else if (value == MY_BLEND) { /*�N�ثe�e���M�ϥΪ̦s�����e���ĦX*/
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glRasterPos2i(0, 0);
        glDrawPixels(width, height*bar_scale,GL_RGBA, GL_UNSIGNED_BYTE,image);
        glDisable(GL_BLEND);
    }
    glFlush();
}

/*���m�U��e��������*/
void clean_draw()
{
    glColor3f(background_color[0], background_color[1], background_color[2]);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    /*���e�U��e��*/
    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(0, height * bar_scale);
    glVertex2f(width, height * bar_scale);
    glVertex2f(width, 0);
    glEnd();

    if (grid == SHOW)
        draw_grid();
}

/*��s�W��bar*/
void change_bar(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (double)width, 0.0, (double)height);//�ഫ�y�ХH���U�������I�Ax:0~width,y:0~height
    glViewport(0, 0, width, height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    bar();

    glEnd();
    glFlush();
}


void top_menu_func(int value)
{
}

/*���menu���e*/
void change_menu()
{
    glutDestroyMenu(top_m);     //�R�����menu
    top_m = glutCreateMenu(top_menu_func);
    if (mode == "shape")        //�Y���e�ϼҦ�
    {
        glutAddSubMenu(" Type ", type_m);
        glutAddSubMenu(" File ", file_m);
        glutAddSubMenu(" Grid ", grid_m);
    }
    else if (mode == "text")    //�Y����r�Ҧ�
    {
        glutAddSubMenu(" Font ", fontstyle_m); 
        glutAddSubMenu(" File ", file_m);
        glutAddSubMenu(" Grid ", grid_m);
    }
  
    glutAttachMenu(GLUT_RIGHT_BUTTON);   //�H�ƹ��k��Ĳ�o
}

/*���U�K����Ĳ�o�A�P�_���U���C�����mycolor�Muse_color*/
void change_color(int x, int y)
{
    for (int i = 0; i < 8; i++)
    {
        if (color_pos[i][0] <= x && x <= color_pos[i][2] && color_pos[i][1] <= y && y <= color_pos[i][3])//�H���U����m�P�_���U���C��
        {
            myColor[0] = color_arr[i][0];
            myColor[1] = color_arr[i][1];
            myColor[2] = color_arr[i][2];
            use_color[0] = color_arr[i][0];
            use_color[1] = color_arr[i][1];
            use_color[2] = color_arr[i][2];
            break;
        }
    }
}

/*���ܭ��`��*/
void change_color_depth(int x, int y)
{
    float tp = 1.0-((float)(x - color_depth_pos[0]) / (color_depth_pos[2] - color_depth_pos[0]));//��1.0~0.0��
    if (tp >= 0.5)  //�Y���a��ժ������A�h�̤�ҥ[�t�Z
    {
        use_color[0] = myColor[0]+(1.0- myColor[0])*tp;
        use_color[1] = myColor[1] + (1.0 - myColor[1]) * tp;
        use_color[2] = myColor[2] + (1.0 - myColor[2]) * tp;
    }
    else            //�Y�a��ª������A�h����������(���q0.5~0.0�վ㬰1.0~0.0�ҥH*2)
    {
        use_color[0] = myColor[0]*tp*2;
        use_color[1] = myColor[1] *tp*2;
        use_color[2] = myColor[2] *tp*2;
    }

    //�קK�Ψ�M�I���P��v�T�P�_
    if (abs(use_color[0] - background_color[0])<=0.01 && abs(use_color[1] - background_color[1])<=0.01 && abs(use_color[2] - background_color[2])<=0.01)
    {
        use_color[0] -= 0.01;
        use_color[1] -= 0.01;
        use_color[2] -= 0.01;
    }
    //�קK�Ψ�M��u�P��v�T�P�_
    else if (abs(use_color[0] - grid_color[0]) <= 0.01 && abs(use_color[1] - grid_color[1]) <= 0.01 && abs(use_color[2] - grid_color[2]) <= 0.01)
    {
        use_color[0] += 0.01;
        use_color[1] += 0.01;
        use_color[2] += 0.01;
    }

}

/*���ܽu���e��*/
void change_width(int value)
{
    if (value == 1) {   //�ܼe
        if (line_width < 10.0) line_width += 1.0;
    }
    else {              //�ܯ�
        if (line_width > 1.0) line_width -= 1.0;
    }
    //�B��sbar(�W����ܪ��u)
    change_bar();
}

/*�����I�j�p*/
void change_size(int value)
{
    if (value == 1) {   //�ܤj
        if (pnt_size < 12.0) pnt_size += 1.0;
    }
    else {              //�ܤp
        if (pnt_size > 1.0) pnt_size = pnt_size - 1.0;
    }
    //�B��sbar(�W����ܪ��I)
    change_bar();
}

/*���ܶꪺ�b�|*/
void change_radius(int value)
{
    if (value == 1) {   //�ܤj
        if (circle_radius < 20.0) circle_radius += 1.0;
    }
    else {              //�ܤp
        if (circle_radius > 3.0) circle_radius = circle_radius - 1.0;
    }
    //�B��sbar(�W����ܪ����)
    change_bar();
}

/*�B�z�ƹ��ƥ󪺨禡 button:�ƹ��ƥ�Ĳ�o�����s state:�ƹ��ƥ�Ĳ�o�����A(���U�Ω�}) (x,y):�ƹ���m*/
void mouse_func(int button, int state, int x, int y)
{
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)//�Y�D������U�h���B�z
        return;
    if (y <= height * (1- bar_scale))   //�Y���U���d��b�W��bar
    {
        if (shape_pos[0] <= x && x <= shape_pos[2] && shape_pos[1] <= height - y && height - y <= shape_pos[3]) {//��ܵe�ϼҦ�
            mode = "shape";
        }
        else  if (text_pos[0] <= x && x <= text_pos[2] && text_pos[1] <= height - y && height - y <= text_pos[3]) {//��ܤ�r�Ҧ�
            mode = "text";
        }
        else  if (colorBlock_pos[0] <= x && x <= colorBlock_pos[2] && colorBlock_pos[1] <= height - y && height - y <= colorBlock_pos[3]) {//��ܤK��⤧�@
            change_color(x, height - y);
        }
        else  if (color_depth_pos[0] <= x && x <= color_depth_pos[2] && color_depth_pos[1] <= height - y && height - y <= color_depth_pos[3]) {//����C��`��
            change_color_depth(x, height - y);
        }
        else  if (plus_width_pos[0] <= x && x <= plus_width_pos[2] && plus_width_pos[1] <= height - y && height - y <= plus_width_pos[3]){//�W�[�u���e��
            change_width(1);
        }
        else  if (minus_width_pos[0] <= x && x <= minus_width_pos[2] && minus_width_pos[1] <= height - y && height - y <= minus_width_pos[3]){//��ֽu���e��
            change_width(0);
        }
        else  if (plus_size_pos[0] <= x && x <= plus_size_pos[2] && plus_size_pos[1] <= height - y && height - y <= plus_size_pos[3]){//�W�[�I���j�p
            change_size(1);
        }
        else  if (minus_size_pos[0] <= x && x <= minus_size_pos[2] && minus_size_pos[1] <= height - y && height - y <= minus_size_pos[3]){//��p�I���j�p
            change_size(0);
        }
        else  if (plus_radius_pos[0] <= x && x <= plus_radius_pos[2] && plus_radius_pos[1] <= height - y && height - y <= plus_radius_pos[3]){//�W�[�ꪺ�b�|
            change_radius(1);
        }
        else  if (minus_radius_pos[0] <= x && x <= minus_radius_pos[2] && minus_radius_pos[1] <= height - y && height - y <= minus_radius_pos[3]){//��ֶꪺ�b�|
            change_radius(0);
        }
        else if(line_style_pos[0] <= x && x <= line_style_pos[2] && line_style_pos[1] <= height - y && height - y <= line_style_pos[3])//��ܽu�˦����p��
        {
            choosing_line_style = YES;  //��ܽu�˦����j��
            choosing_now = YES;
        }
        if (choosing_line_style == YES&& line_block_pos[0] <= x && x <= line_block_pos[2] && line_block_pos[1] <= height - y && height - y <= line_block_pos[3])//��ܦU�ؽu���˦���
        {
            //�P�_��ܪ��u�˦�
            if (line_style_ypos[0][0] <= height - y && height - y <= line_style_ypos[0][1])
                line_style = 0x0F0F;
            else if (line_style_ypos[1][0] <= height - y && height - y <= line_style_ypos[1][1])
                line_style = 0xAFAF;
            else if (line_style_ypos[2][0] <= height - y && height - y <= line_style_ypos[2][1])
                line_style = 0xFFFF;
            choosing_line_style = NO;   //�����u�˦����j��
        }
        else if (choosing_now != YES)   //�Y���F��L�a��h������ܽu�˦����j��
            choosing_line_style = NO;

        change_bar();
        change_menu();
        enable = NO;                   //�]���O�b�W��bar�A����e
        choosing_now = NO;
        return;
    }

    //�N������w�b�U��e���A����e��W��
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (double)width, 0.0, (double)height * bar_scale);
    glViewport(0, 0, width, height * bar_scale);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(use_color[0], use_color[1], use_color[2]);

    //�Y����r�Ҧ��h�O�U���Ы��U��m�A�r����q���}�l�L�X
    if (mode == "text")
    {
        pos_x = x; pos_y = y;
        return;
    }

    //�_�h�P�_���e�ϼҦ���������
    switch (obj_type) {
    case POINT:
        glPointSize(pnt_size);  //�]�w�I�j�p
        glBegin(GL_POINTS);     //�e�I
        glVertex2f(x, height - y);
        glEnd();
        break;
    case LINE:
        if (first == 0) {   //�Y���Ĥ@���I
            first = 1;
            pos_x = x; pos_y = y;   //���O�U��m
            glPointSize(line_width);
            glBegin(GL_POINTS);  //���e�@���I
            glVertex3f(x, height - y, 0);
            glEnd();
        }
        else {
            first = 0;
            glLineWidth(line_width);    //�]�w�u���e��
            glLineStipple(6, line_style);
            glBegin(GL_LINES);   
            glVertex2f(pos_x, height - pos_y);  //�ھڦ����m�M�Ĥ@���I��������m�e�u
            glVertex2f(x, height - y);
            glEnd();
        }
        break;
    case POLYGON: 
        if (side == 0) {    //���Ĥ@���I
            //�������I
            vertex[side][0] = x; 
            vertex[side][1] = y;
            side++;
        }
        else {
            if (fabs(vertex[side - 1][0] - x) + fabs(vertex[side - 1][1] - y) < 2)//�Y�M�W�@�I�۶Z�p(�N���I����U)�A�h�ھڬ��������I�e�X�h���
                draw_polygon();
            else {
                glBegin(GL_LINES);  //�e�X�M�W�@�I���s�u
                glVertex2f(vertex[side - 1][0], height - vertex[side - 1][1]);
                glVertex2f(x, height - y);
                glEnd();
                //�������I
                vertex[side][0] = x;
                vertex[side][1] = y;
                side++;
            }
        }
        break;
    case CIRCLE:
        pos_x = x; pos_y = y;   //�������ߦ�m
        draw_circle(pos_x,pos_y);//�e��
        break;
    case TRIANGLE:
        enable = YES;           //���ϥi�e�A�B�}�l�Ω�Եe�T����
        pos_x = x; pos_y = y;   //�����T�w�I����m
        file_save(TEMP);        //�N�e���e���e���Ȧs(�ΨӰ��X��ۨϥΪ̩���ܤƪ��ĪG)
        break;
    case RECTANGLE:
        enable = YES;           //���ϥi�e�A�B�}�l�Ω�Եe�|���
        pos_x = x; pos_y = y;   //�����T�w�I����m
        file_save(TEMP);        //�N�e���e���e���Ȧs(�ΨӰ��X��ۨϥΪ̩���ܤƪ��ĪG)
        break;
    default:
        break;
    }
    glFinish();
}


/*���ƹ����۲��ʮ�Ĳ�o���禡*/
void motion_func(int  x, int y)
{
    //�����ƹ����e��m
    mouse_x = x;
    mouse_y = height - y;

    if (obj_type == CURVE)//�Y���e���u�Ҧ�
    {
        if (first == 0) {
            first = 1;
            pos_x = x; pos_y = y;
        }
        else {
            glLineStipple(6, line_style);
            glLineWidth(line_width);     
            glBegin(GL_LINES);
            glVertex3f(pos_x, height - pos_y, 0.0);
            glVertex3f(x, height - y, 0.0);
            glEnd();
            pos_x = x; pos_y = y;
        }
    }
    else if (enable == YES) //�Y���i�e��
    {
        clean_draw();       //�h�M���e��
        file_load(TEMP);    //�ñN�e���e���e��load�X��
        glColor3f(use_color[0], use_color[1], use_color[2]);
        if (fill_mode == FILL)
        {
            glPolygonMode(GL_FRONT, GL_FILL);
            glPolygonMode(GL_BACK, GL_FILL);
        }
        else
        {
            glPolygonMode(GL_FRONT, GL_LINE);
            glPolygonMode(GL_BACK, GL_LINE);
        }
        if (obj_type == TRIANGLE)      //�e�X��Ԫ��T����
        {
            glBegin(GL_POLYGON);
            glVertex2f(pos_x, height - pos_y);
            glVertex2f(x, height - y);
            glVertex2f(pos_x - (x - pos_x), height - y);
            glEnd();
        }
        else if (obj_type == RECTANGLE)//�e�X��Ԫ��|���
        {
            glBegin(GL_POLYGON);
            glVertex2f(pos_x, height - pos_y);
            glVertex2f(x, height - pos_y);
            glVertex2f(x, height - y);
            glVertex2f(pos_x, height - y);
            glEnd();
        }
    }
    
    glFinish();
}

/*�S�����s�ɷƹ�����Ĳ�o���禡*/
void passive_motion_func(int x, int y)
{
    mouse_x = x;
    mouse_y = height - y;
    if (obj_type == CURVE)
        first = 0;
    if(obj_type == TRIANGLE ||obj_type==RECTANGLE)//��}����h���e�A���D�A���@�ӷs�����I
        enable = NO;
}


/*��l�]�w*/
void init_func()
{
    glReadBuffer(GL_FRONT);
    glDrawBuffer(GL_FRONT);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

/*menu����ܶ��Ҧ���Ĳ�o*/
void circle_func(int value)
{
    obj_type = CIRCLE;
    fill_mode = value;
    change_bar();
}

/*menu����ܦh��μҦ���Ĳ�o*/
void polygon_func(int value)
{
    obj_type = POLYGON;
    fill_mode = value;
    side = 0;
    change_bar();
}

/*menu����ܤT���μҦ���Ĳ�o*/
void triangle_func(int value)
{
    obj_type = TRIANGLE;
    fill_mode = value;
    change_bar();
}

/*menu����ܥ|��μҦ���Ĳ�o*/
void rectangle_func(int value)
{
    obj_type = RECTANGLE;
    fill_mode = value;
    change_bar();
}

/*menu�����type_m��Ĳ�o*/
void draw_type(int value)
{
    obj_type = value;
    if (value == LINE || value == CURVE)
        first = 0;
}

/*menu����ܦr����Ĳ�o*/
void font_func(int value)
{
    font_style = value;
}

/*menu����ܬO�_��ܮ�u��Ĳ�o*/
void grid_func(int value)
{
    grid = value;
    file_save(TEMP);    //���s�ϥΪ̵e����
    init_window();      //��l�Ƶe��(�÷|�b�䤤�P�_�O�_�e��u)
    file_load(TEMP);    //�N��s���ϥΪ̪��e��ܥX��
    glFlush();
}

/*�]�wmenu���e*/
void menu()
{
    //file��
    file_m = glutCreateMenu(file_func);
    glutAddMenuEntry(" Save ", MY_SAVE);
    glutAddMenuEntry(" Load ", MY_LOAD);
    glutAddMenuEntry(" Blend ", MY_BLEND);
    glutAddMenuEntry(" Clear ", MY_CLEAR);
    glutAddMenuEntry(" Quit ", MY_QUIT);

    //circle���ܶ񺡩ΪŤ�
    circle_m = glutCreateMenu(circle_func);
    glutAddMenuEntry(" Fill ", FILL);
    glutAddMenuEntry(" Line ", LINE);

    //�h������ܶ񺡩ΪŤ�
    polygon_m = glutCreateMenu(polygon_func);
    glutAddMenuEntry(" Fill ", FILL);
    glutAddMenuEntry(" Line ", LINE);

    //�T�������ܶ񺡩ΪŤ�
    triangle_m = glutCreateMenu(triangle_func);
    glutAddMenuEntry(" Fill ", FILL);
    glutAddMenuEntry(" Line ", LINE);

    //�|������ܶ񺡩ΪŤ�
    rectangle_m = glutCreateMenu(rectangle_func);
    glutAddMenuEntry(" Fill ", FILL);
    glutAddMenuEntry(" Line ", LINE);

    //�e�ϼҦ��ɪ�����
    type_m = glutCreateMenu(draw_type); 
    glutAddMenuEntry(" Point ", POINT);
    glutAddMenuEntry(" Line ", LINE);
    glutAddMenuEntry(" Curve ", CURVE);
    glutAddSubMenu(" Polygon ", polygon_m);
    glutAddSubMenu(" Circle ", circle_m);
    glutAddSubMenu(" Triangle ", triangle_m);
    glutAddSubMenu(" Rectangle ", rectangle_m);

    //��ܬO�_�n��u
    grid_m = glutCreateMenu(grid_func);   /* Create draw-type menu */
    glutAddMenuEntry(" Show ", SHOW);
    glutAddMenuEntry(" Hide ", HIDE);

    //�r��������
    fontstyle_m = glutCreateMenu(font_func);   /* Create draw-type menu */
    glutAddMenuEntry("GLUT_BITMAP_9_BY_15", GLUT_BITMAP_9_BY_15);
    glutAddMenuEntry("GLUT_BITMAP_8_BY_13", GLUT_BITMAP_8_BY_13);
    glutAddMenuEntry("GLUT_BITMAP_TIMES_ROMAN_10", GLUT_BITMAP_TIMES_ROMAN_10);
    glutAddMenuEntry("GLUT_BITMAP_TIMES_ROMAN_24", GLUT_BITMAP_TIMES_ROMAN_24);
    glutAddMenuEntry("GLUT_BITMAP_HELVETICA_10", GLUT_BITMAP_HELVETICA_10);
    glutAddMenuEntry("GLUT_BITMAP_HELVETICA_12", GLUT_BITMAP_HELVETICA_12);
    glutAddMenuEntry("GLUT_BITMAP_HELVETICA_18", GLUT_BITMAP_HELVETICA_18);

    change_menu();
}


/*main*/
void main(int argc, char** argv)
{

    glutInit(&argc, argv);               /*---Make connection with server---*/

    glutInitWindowPosition(0, 0);       //�]�w�����b�ù�����ܪ���m
    glutInitWindowSize(width, height);  //�]�w�����j�p

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); /*---set display mode---*/
    init_func();

    
    glutCreateWindow("mydraw");         //�гy�X�@�ӵ����éR�W
    init_window();

    glutIdleFunc(idle_func);            //���m��call idle_func
    glutDisplayFunc(display_func);      /* Associate display event callback func */
    glutReshapeFunc(my_reshape);        /* Associate reshape event callback func */


    glutKeyboardFunc(keyboard);         /* Callback func for keyboard event */

    glutMouseFunc(mouse_func);          /* Mouse Button Callback func */
    glutMotionFunc(motion_func);        /* Mouse motion event callback func */
    glutPassiveMotionFunc(passive_motion_func);
    menu();//�]�wmenu���e

    /*---Test whether overlay support is available --*/
    if (glutLayerGet(GLUT_OVERLAY_POSSIBLE)) {
        fprintf(stderr, "Overlay is available\n");
    }
    else {
        fprintf(stderr, "Overlay is NOT available, May encounter problems for menu\n");
    }

    /*---Enter the event loop ----*/
    glutMainLoop();
}
