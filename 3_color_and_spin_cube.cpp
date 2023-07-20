#include<stdio.h>
#include<OpenGL/OpenGL.h>
#include<GLUT/glut.h>
float v[8][3] = {
    {-1,-1,1},
    {-1,1,1},
    {1,1,1},
    {1,-1,1},
    {-1,-1,-1},
    {-1,1,-1},
    {1,1,-1},
    {1,-1,-1}
};
float c[6][3] = {
    {0,0,1},
    {0,1,0},
    {1,0,0},
    {0,1,1},
    {1,0,1},
    {1,1,0}
};
float theta[3] = {0,0,0};
int flag = 2;
void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2,2,-2,2,-2,2);
    glMatrixMode(GL_MODELVIEW);
}

void draw_poly(int a , int b, int c , int d)
{
    
    glBegin(GL_POLYGON);
    glVertex3fv(v[a]); 
    glVertex3fv(v[b]);      
    glVertex3fv(v[c]); 
    glVertex3fv(v[d]);
    glEnd(); 
}
void colorcube()
{
    glColor3fv(c[0]);
    draw_poly(0,1,4,5);
    glColor3fv(c[1]);
    draw_poly(4,5,6,7);
    glColor3fv(c[2]);
    draw_poly(2,3,7,6);
    glColor3fv(c[3]);
    draw_poly(0,1,2,3);
    glColor3fv(c[4]);
    draw_poly(1,2,5,6);
    glColor3fv(c[5]);
    draw_poly(0,3,4,7);
}
void idleFunc()
{
    theta[flag]++;
    if(theta[flag]>360) theta[flag]=0;
    glutPostRedisplay();
}

void mouseFunc(int b, int s, int x, int y)
{
    if(b == GLUT_LEFT_BUTTON && s == GLUT_DOWN)
        flag = 2;
    if(b == GLUT_MIDDLE_BUTTON && s == GLUT_DOWN)
        flag = 1;
    if(b == GLUT_RIGHT_BUTTON && s == GLUT_DOWN)
        flag = 0;
}

void display()
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0,1,0);
    glEnable(GL_DEPTH_TEST);
    // glLoadIdentity();
    glRotatef(theta[0],1,0,0);
    glRotatef(theta[1],0,1,0);
    glRotatef(theta[2],0,0,1);
    colorcube();
    glFlush();
    glutSwapBuffers();
}

int main(int argc , char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Spin and rotate cube");
    myinit();
    glutDisplayFunc(display);
    glutMouseFunc(mouseFunc);
    glutIdleFunc(idleFunc);
    glutMainLoop();
}
