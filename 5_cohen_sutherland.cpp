#include<stdio.h>
#include<OpenGL/OpenGL.h>
#include<GLUT/glut.h>
float x1,y1,x2,y2;
float xmin,xmax,ymin,ymax,umin,umax,vmin,vmax;
enum {top = 0x08, bottom = 0x04, right = 0x02, left = 0x01};
#define opcode int
void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
    glMatrixMode(GL_MODELVIEW);
}
opcode compopcode(float x, float y)
{
    int p = 0;
    if(x<xmin) p|= left;
    if(x>xmax) p |= right;
    if(y<ymin) p |= bottom;
    if(y>ymax) p|= top;

    return p;
}
void cohensutherland()
{
    float x, y;
    bool accept = false, done = false;
    int p1 = compopcode(x1,y1);
    int p2 = compopcode(x2,y2);
    int p =0;
    float m = (y2-y1)/(x2-x1);
    do 
    {
        if(!(p1|p1))
        {
            accept = done = true;
        }
        else if(p1&p2)
        {
            done = true;
        }
        else
        {
            p = p1?p1:p2;
            if(p&top)
            {
                y = ymax;
                x = x1+(ymax-y1)/m;
            }
            if(p&bottom)
            {
                y =ymin;
                x = x1 + (ymin - y1)/m;
            }
            if(p & right)
            {
                x = xmax;
                y = y1+(xmax-x1)*m;
            }
            if(p & left)
            {
                x = xmin;
                y = y1+(xmin-x1)*m;
            }
            if(p == p1)
            {
                x1 = x;
                y1 = y;
                p1 = compopcode(x1,y1);
            }
            if(p == p2)
            {
                x2 = x;
                y2 = y;
                p2 = compopcode(x2,y2);
            }
        }
    }while(!done);
    if(accept)
    {
        float sx = (umax - umin)/(xmax - xmin);
        float sy = (vmax - vmin)/(ymax - ymin);
        x1 = sx*x1 + umin - sx*xmin;
        y1 = sy* y1 +vmin -sy*ymin;
        x2 = sx*x2 +umin -sx*xmin;
        y2 = sy*y2 +vmin - sy*ymin;
    }
    glColor3f(1,0,0);
    glBegin(GL_LINES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glEnd();
    glFlush();
}
void display()
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmin, ymax);
    glVertex2f(xmax, ymax);
    glVertex2f(xmax, ymin);
    glEnd();

    glColor3f(0,0,1);
     glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();

    glColor3f(0,0,1);
     glBegin(GL_LINE_LOOP);
    glVertex2f(umin, vmin);
    glVertex2f(umin, vmax);
    glVertex2f(umax, vmax);
    glVertex2f(umax, vmin);
    glEnd();
    cohensutherland();
    glFlush();
}
int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("cohen sutherland");
    myinit();
    printf("Enter xmin xmax , ymin , ymax\n");
    scanf("%f%f%f%f", &xmin, &xmax, &ymin, &ymax);
    printf("Enter x1 y1 and x2 y2\n");
    scanf("%f%f%f%f", &x1,&y1,&x2,&y2);
    printf("Enter umin umax , vmin , vmax\n");
    scanf("%f%f%f%f", &umin, &umax, &vmin, &vmax);
    glutDisplayFunc(display);
    glutMainLoop();
}