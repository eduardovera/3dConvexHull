#include <QCoreApplication>
#include <GL/glut.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    glutSetWindow(glutCreateWindow("teste"));
    glutShowWindow();

    return 0;
}
