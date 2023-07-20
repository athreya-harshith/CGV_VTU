#include<stdio.h>
#include<math.h>
#include<OpenGL/OpenGL.h>
#include<GLUT/glut.h>

float ya = 50,xa = 10;
int yFlag = 1, xFlag = 1,animFlag=1;
void d_menu(int op){
    if(op == 1)
        animFlag =1;
    else if(op ==2)
        animFlag = 0;
    else if (op == 3)
        exit(0);
    glutPostRedisplay();
}
void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
    glMatrixMode(GL_MODELVIEW);
    glutCreateMenu(d_menu);
    glutAddMenuEntry("Animate",1);
    glutAddMenuEntry(" Stop Animate",2);
    glutAddMenuEntry("Exit ",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void animate()
{
    if(animFlag == 1)
    {
         if(ya>-50 && yFlag == 1)
            ya= ya-0.2;
         if(ya<=-50 && yFlag == 1)
            yFlag = 0;
        if(ya<50 && yFlag == 0)
            ya = ya+0.2;
        if(ya>= 50 && yFlag == 0)
            yFlag = 1; 
        if(xa>-10 && xFlag == 1)
            xa= xa-0.2;
        if(xa<=-10 && xFlag == 1)
            xFlag = 0;
        if(xa<10 && xFlag == 0)
            xa = xa+0.2;
        if(xa>= 10 && xFlag == 0)
            xFlag = 1;
    }
   
    glutPostRedisplay();
}
void display()
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);

    GLdouble x[4],y1[4],y2[4],y3[4];
    x[0]= 100;x[1]= 200;x[2]=200;x[3]= 300-xa;
    y1[0]=450;y1[1]=450+ya;y1[2]=450-ya;y1[3]=450;
    y2[0]=400;y2[1]=400+ya;y2[2]=400-ya;y2[3]=400;
    y3[0]=350;y3[1]=350+ya;y3[2]=350-ya;y3[3]=350;
    GLdouble xt[200], yt1[200],yt2[200],yt3[200];

    GLdouble t=0.00;
    for(int i=0;t<=1;i++,t+=0.01)
    {
        xt[i] = (pow(1-t,3)*x[0])+(3*t*pow(1-t,2)*x[1])+(3*pow(t,2)*(1-t)*x[2])+(pow(t,3)*x[3]);
        yt1[i] = (pow(1-t,3)*y1[0])+(3*t*pow(1-t,2)*y1[1])+(3*pow(t,2)*(1-t)*y1[2])+(pow(t,3)*y1[3]);
        yt2[i] = (pow(1-t,3)*y2[0])+(3*t*pow(1-t,2)*y2[1])+(3*pow(t,2)*(1-t)*y2[2])+(pow(t,3)*y2[3]);
        yt3[i] = (pow(1-t,3)*y3[0])+(3*t*pow(1-t,2)*y3[1])+(3*pow(t,2)*(1-t)*y3[2])+(pow(t,3)*y3[3]);
    }
    glPointSize(3);
    glColor3f(1,0,0);
    glBegin(GL_QUAD_STRIP);
    for(int i=0;i<100;i++)
    {
        glVertex2d(xt[i],yt1[i]);
        glVertex2d(xt[i],yt2[i]);
    }
    glColor3f(0,0,1);
    glBegin(GL_QUAD_STRIP);
    for(int i=0;i<100;i++)
    {
        glVertex2d(xt[i],yt2[i]);
        glVertex2d(xt[i],yt3[i]);
    }
    glEnd();
    glColor3f(1,0,1);
    glRecti(90,460,100,50);
    glEnd();
    glFlush();

}
int main(int argc , char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Bezier Curve");
    myinit();
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();
}