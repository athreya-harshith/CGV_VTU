#include<stdio.h>
#include<GLUT/glut.h>
#include<OpenGL/OpenGL.h>
#include<math.h>
float xp,yp,theta,rtheta;
float v[3][2]={{20,20},{40,40},{60,20}};
void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100,100,-100,100);
    glMatrixMode(GL_MODELVIEW);
}

void draw_triangle()
{
    glBegin(GL_TRIANGLES);
    glVertex2fv(v[0]);
    glVertex2fv(v[1]);
    glVertex2fv(v[2]);
    glEnd();
}
void display()
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    draw_triangle();
    rtheta = (theta * 3.142)/180;
    float x,y;
    for(int i=0;i<3;i++)
    {
        x = v[i][0];
        y = v[i][1];
        v[i][0] = xp + (x-xp)*cos(rtheta) - (y-yp)*sin(rtheta);
        v[i][1] = yp + (x-xp)*sin(rtheta)+(y-yp)*cos(rtheta);
    }
    glColor3f(0,1,0);
    draw_triangle();
    glFlush();
}

int main(int argc , char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Rotate a triangle");
    myinit();
    printf("Enter the point of rotation\n");
    scanf("%f%f",&xp,&yp);
    printf("Enter the angle \n");
    scanf("%f", &theta);
    glutDisplayFunc(display);
    glutMainLoop();
}