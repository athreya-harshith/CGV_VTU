#include<stdio.h>
#include<OpenGL/OpenGL.h>
#include<GLUT/glut.h>
#include<stdlib.h>
#include<math.h>
float xx, yy, xend,yend;
void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
    glMatrixMode(GL_MODELVIEW);
}
void setpixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}
void bresenham()
{
    float x, y;
    if(xx>xend)
    {
        x = xend;
        y = yend;
        xend = xx;
        yend = yy;
    }
    else
    {
        x = xx;
        y = yy;
    }
    int dx = abs(xend-x);
    int dy = abs(yend -y);
    if(dx>dy)
    {
        //m<1
        int p = 2*dy-dx;
        setpixel(x,y);
        while(x<xend)
        {
            x++;
            if(p<0)
                p +=2*dy;
            else
            {
                y++;
                p+=2*dy-2*dx;
            }
            setpixel(x,y);
        }
    }
    else
    {
        // m>1
        int p = 2*dx-dy;
        setpixel(x,y);
        while(y<yend)
        {
            y++;
            if(p<0)
                p+=2*dx;
            else
            {
                x++;
                p+=2*dx-2*dy;
            }
            setpixel(x,y);
        }
    }
}

void display()
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1,0,0);
    glViewport(300,300,100,100);
    bresenham();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Bresenham");
    myinit();
    printf("Enter the x1 y1 and x2 y2\n");
    scanf("%f%f%f%f", &xx,&yy,&xend,&yend);
    glutDisplayFunc(display);
    glutMainLoop();
}