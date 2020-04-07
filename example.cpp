/*
#include <GL/glut.h> // Once you include glut.h (you don't need gl.h or glu.h)

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

static double angle = 0.0f;
static double lx=0.0f,lz=-1.0f;
static double x=0.0f, z=10.0f;
static double deltaAngle = 0.0f;
static double deltaMove = 0;

void computePos(double deltaMove) {

    x += deltaMove * lx * 0.2f;
    z += deltaMove * lz * 0.2f;
}

void computeDir(double deltaAngle) {
    angle += deltaAngle;
    lx = sin(angle);
    lz = -cos(angle);
}

void init()
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);


        glEnable(GL_LINE_SMOOTH);
        glHint(GL_LINE_SMOOTH, GL_NICEST);
        glEnable(GL_POINT_SMOOTH);
        glHint(GL_POINT_SMOOTH, GL_NICEST);


        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);

        glEnable(GL_SMOOTH);
        glEnable(GL_LIGHTING);

        // Setup the materials for LIGHT0

        // Enable the light
        glEnable(GL_LIGHT0);
        glEnable(GL_TEXTURE_2D);
}

void display()
{
    glLoadIdentity();

    // Code from http://www.lighthouse3d.com/tutorials/glut-tutorial/the-code-so-far/
    // Accessed 12/06/2015
    //if (deltaMove != 0)
        computePos(deltaMove);
    //if (deltaAngle != 0)
        computeDir(deltaAngle);


    double tall = 2.5;			// Height of player
    gluLookAt(x, tall, z,x+lx, tall, z+lz,0, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);





    static float cube[8][3] = {
            {0.5, 0.5, -0.5},
            {0.5, -0.5, -0.5},
            {-0.5, -0.5, -0.5},
            {-0.5, 0.5, -0.5},
            {-0.5, 0.5, 0.5},
            {0.5, 0.5, 0.5},
            {0.5, -0.5, 0.5},
            {-0.5, -0.5, 0.5}
    };

    glPushMatrix();
    glBegin(GL_QUADS);


        glColor3f(1.0, 0.0, 0.0);
        glVertex3fv(cube[0]);
        glVertex3fv(cube[1]);
        glVertex3fv(cube[2]);
        glVertex3fv(cube[3]);

        glColor3f(0.0, 1.0, 0.0);
        glVertex3fv(cube[3]);
        glVertex3fv(cube[4]);
        glVertex3fv(cube[7]);
        glVertex3fv(cube[2]);

        glColor3f(0.0, 0.0, 1.0);
        glVertex3fv(cube[0]);
        glVertex3fv(cube[5]);
        glVertex3fv(cube[6]);
        glVertex3fv(cube[1]);

        glColor3f(0.0, 1.0, 1.0);
        glVertex3fv(cube[5]);
        glVertex3fv(cube[4]);
        glVertex3fv(cube[7]);
        glVertex3fv(cube[6]);

        glColor3f(1.0, 1.0, 0.0);
        glVertex3fv(cube[5]);
        glVertex3fv(cube[0]);
        glVertex3fv(cube[3]);
        glVertex3fv(cube[4]);

        glColor3f(1.0, 0.0, 1.0);
        glVertex3fv(cube[6]);
        glVertex3fv(cube[1]);
        glVertex3fv(cube[2]);
        glVertex3fv(cube[7]);


    glEnd();
    glPopMatrix();













    glFlush();
    glutSwapBuffers();
    GLenum errCode;
    const GLubyte *errString;
    if((errCode = glGetError()) != GL_NO_ERROR)
    {
       errString = gluErrorString(errCode);
       fprintf (stderr,"OpenGL error : %s\n",errString);
    }








    glutPostRedisplay();
}

void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0,(GLfloat)w/(GLfloat)h,1.0,200.0);
    glMatrixMode(GL_MODELVIEW);
}

void pressKey(int key, int xx, int yy)
{
    switch (key) {
        case GLUT_KEY_LEFT:
            deltaAngle = -0.05f;
            std::cout << "LEFT" << deltaAngle;
        break;
        case GLUT_KEY_RIGHT:
            deltaAngle = 0.05f;
            std::cout << "RIGHT";
        break;
        case GLUT_KEY_UP:
            deltaMove = 0.5f;
            std::cout << "UP";
        break;
        case GLUT_KEY_DOWN:
            deltaMove = -0.5f;
            std::cout << "DOWN";
        break;
    }
}

void releaseKey(int key, int x, int y) {

    switch (key) {
        case GLUT_KEY_LEFT :
            std::cout << "LEFT" << deltaAngle;
        case GLUT_KEY_RIGHT:
            deltaAngle = 0.0f;
        break;
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN:
            deltaMove = 0;
        break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    //glutIdleFunc(spinTorus);

      //glutKeyboardFunc(keyboard);

    glutSpecialFunc(pressKey);


    glutIgnoreKeyRepeat(1);
    glutSpecialUpFunc(releaseKey);

    glutMainLoop();
    return 0;
}
*/
