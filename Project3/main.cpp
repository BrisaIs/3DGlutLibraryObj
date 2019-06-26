/*#ifndef UTILITIES_H
  #define UTILITIES_H
  #include "Utilities.h"
#endif
*/
#ifndef POINT3D_H
  #define POINT3D_H
  #include "Point3D.h"
#endif

#ifndef POLYGON3D_H
	#define POLYGON3D_H
	#include "Polygon3D.h"
#endif

#ifndef GLUT_H
 #define GLUT_H
 #include <GL/glut.h>
 #include <GL/gl.h>
#endif

#ifndef MATRIX_H
    #define MATRIX_H
    #include "Matrix.h"
#endif

#ifndef SPHERE_H
  #define SPHERE_H
  #include "Sphere3D.h"
#endif

#ifndef OPERATORS3D_H
  #define OPERATORS3D_H
  #include "Operators3D.h"
#endif

//#include <string.h>
#include <iostream>
#include <stdio.h>
#include "ChargeObject.h"

float Pos_x = 4.5f;//
float Pos_y = 3.0f;// ->Donde esta situado

float Up_x = 0.0f;//
float Up_y = 1.0f;//Vector Orientacion
float Up_z = 0.0f;//

float xMin = -250; float yMin = -250; float zMin = -250;
float xMax = 250;  float yMax = 250; float zMax = 250;

float FOVY = 70.0;
float ZNEAR = 0.01;
float ZFAR= 200;

float Theta = 0.0f;

float steps = 0.5f;

float MouseVelocity = 0.35f ;
bool WarpingMouse = false;

float Pi = 3.141592654f;

int width = 500;
int height = 500;

 void init();
 void idle();
 GLfloat convierteARadian(GLfloat ang);

 void reshape(int width, int height);
 void specialKeys(int key,int x,int y);
 void PassiveMouseMotion(int x, int y);

 void drawAxis();
 void drawOBJ();
 void draw();

int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    //glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(width, height);
    glutInitWindowPosition(250, 120);
    glutCreateWindow("Proyecto 3");

    init();
    glutDisplayFunc(draw);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);
    glutPassiveMotionFunc(PassiveMouseMotion);

    glutMainLoop();

    return 0;
}

void init()
{
  glutSetCursor(GLUT_CURSOR_NONE);

  float k = convierteARadian(Theta);
  float x = Pos_x + steps*sin(k);
  float y = Pos_y + steps*cos(k);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(FOVY, width/height, ZNEAR, ZFAR);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(Pos_x, 0, Pos_y, x, 0, y, Up_x, Up_y, Up_z);
  glClearColor(0.0,0.0,0.0,0.0);
}

void idle()
{
    Sleep(20);
    glutPostRedisplay();
}

GLfloat convierteARadian(GLfloat ang){return (ang*M_PI)/180;}

void reshape(int width, int height)
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
    glViewport(0, 0, width, height);
}

void specialKeys(int key,int x,int y)
{
    switch(key)
    {
   		case GLUT_KEY_DOWN:
      {
            printf("Atras\n");
            float k1 = convierteARadian(Theta);
            float x1 = Pos_x - steps*sin(k1);
            float y1 = Pos_y - steps*cos(k1);
            Pos_x = x1;
            Pos_y = y1;
        break;
        }

   		case GLUT_KEY_UP:
      {
            printf("Adelante\n");
            float k2 = convierteARadian(Theta);
            float x2 = Pos_x + steps*sin(k2);
            float y2 = Pos_y + steps*cos(k2);
            Pos_x = x2;
            Pos_y = y2;
        break;
      }

   		case GLUT_KEY_LEFT:
      {
            printf("Izquierda\n");
            Theta+=3;
        break;
      }

   		case GLUT_KEY_RIGHT:
      {
            printf("Derecha\n");
            Theta-=3;
        break;
      }
    }

    init();
    glutPostRedisplay();

}

void PassiveMouseMotion(int x, int y)
{/*
	int CenterX = glutGet(GLUT_WINDOW_WIDTH) / 2 ;
	int CenterY = glutGet(GLUT_WINDOW_HEIGHT) / 2 ;

	int DiffX = x - CenterX;
	int DiffY = y - CenterY;

	if(!WarpingMouse)
	 {
		WarpingMouse = true;

		Xrotation += (float) DiffY * MouseVelocity ;
		Yrotation += (float) DiffX * MouseVelocity ;

		glutWarpPointer(CenterX, CenterY) ;
	}

	else {WarpingMouse = false ;}*/
}

void drawAxis()
{
  glLineWidth(1);
  glColor3f(0.0, 0.5, 1.0);
  glBegin(GL_LINES);
    glVertex3d(-1000.0, 0.0, 0.0);
    glVertex3d(1000.0, 0.0, 0.0);
  glEnd();

  glColor3f(1.0, 0.0, 1.0);
  glBegin(GL_LINES);
    glVertex3d(0.0, -1000.0, 0.0);
    glVertex3d(0.0, 1000.0, 0.0);
  glEnd();

  glColor3f(1.0, 0.5, 0.0);
  glBegin(GL_LINES);
    glVertex3d(0.0, 0.0, -1000.0);
    glVertex3d(0.0, 0.0, 1000.0);
  glEnd();
}

void drawOBJ()
{
  ChargeObject hermione = "E:/Fac/Graph/Rec/Project3/Objects/skhermionemesh/skhermionemesh.obj";
  glPushMatrix();
  glTranslatef(15, 0, 0);
  glColor3f(0.4f, 0.4f, 0.4f);
  hermione.display();
  glPopMatrix();
}


void draw()
{
  glClear(GL_COLOR_BUFFER_BIT);
    Point3D mainPoints3D[3], pT,pS;
     Operators3D op;

  mainPoints3D[0].setPoint3D((GLdouble) 0, (GLdouble) 0, (GLdouble) 0);
  mainPoints3D[1].setPoint3D((GLdouble) 7, (GLdouble) 0, (GLdouble) 0);
  mainPoints3D[2].setPoint3D((GLdouble) 3, (GLdouble) 6, (GLdouble) 0);

  Polygon3D p1(3, mainPoints3D);

  pT.setPoint3D(1.0,1.0,1.0);
  pS.setPoint3D(2.0,2.0,2.0);

  drawAxis();
  drawOBJ();

  p1.drawPolygon3D();
  glFlush();
  glutSwapBuffers();

  /*
    //p1.printPointsArray();
    //Sleep(300);

    glutPostRedisplay();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxis();


    op.translation3D(p1,pT);
    //op.scale3D(p1,pS);
    //op.rotation2D(p1,90.0);
    //op.reflexX2D(p1);
    //op.reflexY2D(p1);
    //op.reflexXY2D(p1);
    p1.drawPolygon3D();
    //p1.printMainPoints();


    glFlush();
    glutSwapBuffers();
*/

}
