#include "glutmanager.h"
#include <GL/glut.h>

void GlutManager::init(int argc, char *argv[], const int &h, const int &w, const char *name) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(h, w);
    glutCreateWindow(name);
    glutDisplayFunc(&(GlutManager::display));
    glEnable(GL_DEPTH_TEST);

    glutMouseFunc(&(GlutManager::mouseWheel));
    glutKeyboardFunc(&(GlutManager::keyPress));
//    glutReshapeFunc(&(GlutManager::handleResize));
    glutMainLoop();
}

void GlutManager::mouseWheel(int button, int state, int x, int y) {
    cout << button << endl;
    if (button == 3 || button == 4)
    {
        cout << "scroll" << endl;
    }
}

void GlutManager::handleResize(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(45.0,                  //The camera angle
                   (double)w / (double)h, //The width-to-height ratio
                   1.0,                   //The near z clipping coordinate
                   200.0);                //The far z clipping coordinate
}

void GlutManager::keyPress(unsigned char key,int x,int y) {


    if(key==27)
          exit(0);
    if (static_cast<int>(key) == 52) {
        GlutManager::signal = -1;
    } else
    if (static_cast<int>(key) == 54) {
        GlutManager::signal = +1;
    }
    display();

}

void GlutManager::display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutWireTeapot(100);

//    glScalef( rotate_x,rotate_x,1.0f );
    //glScalef(1.0f,1.0f,rotate_x);
    glRotated(0.5, 0, GlutManager::signal, 0 );

    for (int i = 0; i < GlutManager::points.size(); i++) {
        glBegin(GL_POINTS);
        glColor3d(1, 1, 1);
        glPointSize(100);
        glVertex3d(points[i][0], points[i][1], points[i][2]);
        glEnd();
    }
    glFlush();
    glutSwapBuffers();
}

