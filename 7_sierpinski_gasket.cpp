#include<stdio.h>
#include<OpenGL/OpenGL.h>
#include<GLUT/glut.h>
int c;
float v[4][3] = {
    {0,1,0},
    {0.5,-0.5,0},
    {-0.5,-0.5,0},
    {0,0,1}
};

void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2,2,-2,2);
    glMatrixMode(GL_MODELVIEW);
}
void draw_triangle(float a[3], float b[3], float c[3])
{
    glBegin(GL_POLYGON);
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
    glEnd();
}
void div_triangle(float *a, float *b, float *c, int n)
{
    float v1[3],v2[3], v3[3];
    if(n>0)
    {
        for(int i=0;i<3;i++)
        {
            v1[i] = (a[i]+b[i])/2;
            v2[i] = (a[i]+c[i])/2;
            v3[i] = (c[i] + b[i])/2;
        }
        div_triangle(a, v1,v2, n-1);
        div_triangle(v1,b,v3,n-1);
        div_triangle(v2,c,v3,n-1);
    }
    else
        draw_triangle(a,b,c);
}

void display()
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    div_triangle(v[0],v[1],v[2],c);
    div_triangle(v[0],v[1],v[3],c);
    div_triangle(v[1],v[2],v[3],c);
    div_triangle(v[0],v[2],v[3],c);
    glFlush();
}

int main(int argc , char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("sierpinski");
    myinit();
    printf("Enter the number of divisions\n");
    scanf("%d", &c);
    glutDisplayFunc(display);
    glutMainLoop();
}