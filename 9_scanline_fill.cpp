#include<stdio.h>
#include<GLUT/glut.h>
#include<OpenGL/OpenGL.h>
#include<stdlib.h>
float x1,ya,x2,y2,x3,y3,x4,y4;
void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glPointSize(1.0);
    glColor3f(1,0,0);
    glLoadIdentity();
    gluOrtho2D(0,499,0,499);
    glMatrixMode(GL_MODELVIEW);
}
void d_menu(int op)
{
    if(op ==1 )
        glColor3f(1,0,0);
    else if(op == 2)
        glColor3f(0,1,0);
    else if (op == 3)
        exit(0);
    glutPostRedisplay();
}
void detectedge(float x1,float y1,float x2, float y2, int *le, int *re)
{
    float x, temp, mx;
    if((y2-y1)<0)
    {
        temp = x1;x1 = x2;
        x2 = temp;

        temp = y1;
        y1 = y2;
        y2 = temp;
    }

    if((y2-y1)!=0)
        mx = (x2-x1)/(y2-y1);
    else   
        mx = x2-x1;
    x = x1;
    for(int i=y1;i<=y2;i++)
    {
        if(x<(float)le[i])
            le[i] = (int) x;
        if(x>(float)re[i])
            re[i] = (int) x;
        x+=mx;
    }
}
void drawpixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}
void scanlinefill(float x1,float y1,float x2, float y2,float x3,float y3,float x4, float y4)
{
    int le[500], re[500];
    for(int i=0;i<500;i++)
    {
        le[i] = 500;
        re[i] = 0;
    }
    detectedge(x1,ya,x2,y2,le,re);
    detectedge(x2,y2,x3,y3,le,re);
    detectedge(x3,y3,x4,y4,le,re);
    detectedge(x4,y4,x1,ya,le,re);

    for(int y = 0;y<500;y++)
    {
        if(le[y]<=re[y])
        {
            for(int i= le[y];i<re[y];i++)
                drawpixel(i,y);
        }
    }
}

void display()
{
    x1 = 200; ya = 200; x2 = 100; y2 = 300; x3 = 200; y3 = 400; x4 =300; y4 = 300;
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_LINE_LOOP);
    glVertex2f(x1,ya);
    glVertex2f(x2,y2);
    glVertex2f(x3,y3);
    glVertex2f(x4,y4);
    glEnd();
    scanlinefill(x1,ya,x2,y2,x3,y3,x4,y4);
    glFlush();
}

int main(int argc , char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Scan line fill");
    glutCreateMenu(d_menu);
    glutAddMenuEntry("Red",1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Exit", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    myinit();
    glutDisplayFunc(display);
    glutMainLoop();
}