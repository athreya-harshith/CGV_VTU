//as given in manual
#include<stdio.h>
#include<GLUT/glut.h>
#include<OpenGL/OpenGL.h>
#include<math.h>
void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100,200,-100,200,-200,200);
    glMatrixMode(GL_MODELVIEW);
}
void drawtable()
{
    //table top
    glPushMatrix();
    glTranslatef(50,40,-50);
    glScalef(50,5,50);
    glutSolidCube(1);
    glPopMatrix();

    //1st leg
    glPushMatrix();
    glColor3f(1,1,0);
    glTranslatef(30,20,-30);
    glScalef(5,35,5);
    glutSolidCube(1);
    glPopMatrix();
    //2ndleg
    glPushMatrix();
    glColor3f(1,1,0);
    glTranslatef(70,20,-30);
    glScalef(5,35,5);
    glutSolidCube(1);
    glPopMatrix();
    //3d leg

    glPushMatrix();
    glColor3f(1,1,0);
    glTranslatef(30,20,-70);
    glScalef(5,35,5);
    glutSolidCube(1);
    glPopMatrix();

    //4th leg 
    glPushMatrix();
    glColor3f(1,1,0);
    glTranslatef(70,20,-70);
    glScalef(5,35,5);
    glutSolidCube(1);
    glPopMatrix();
    
    //floor
    glPushMatrix();
    // glColor3f(1,0,1);
    glTranslatef(50,0,-50);
    glScalef(100,5,100);
    glutSolidCube(1);
    glPopMatrix();

    //leftwall
    glPushMatrix();
    glColor3f(1,0,1);
    glRotatef(90,0,0,1);
     glTranslatef(50,0,-50);
    glScalef(100,5,100);
    glutSolidCube(1);
    glPopMatrix();

    //backwall
    glPushMatrix();
    glColor3f(0,1,0);
    glTranslatef(50,50,-100);
    glScalef(100,100,5);
    glutSolidCube(1);
    glPopMatrix();

    //teapot
    glPushMatrix();
    glTranslatef(50,50,-50);
    glRotatef(30,0,1,0);
    glutSolidTeapot(10);
    glPopMatrix();

}
void display()
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1,1,0);
    gluLookAt(25,25,50,0,0,-25,0,1,0);
    drawtable();
    glFlush();

    
}
int main(int argc , char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Tea Pot");
    myinit();
    glutDisplayFunc(display);
    glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0 );
      glShadeModel(GL_SMOOTH);
     glEnable(GL_NORMALIZE);
     glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}
