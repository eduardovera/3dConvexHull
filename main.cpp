#include <QCoreApplication>
#include <iostream>
#include <GL/glut.h>
#include <glutmanager.cpp>
#include <utils.cpp>

vector<Vec3d> GlutManager::points;
vector<Vec3i> GlutManager::faces;
double GlutManager::signal = 1;


int main(int argc, char *argv[])
{
    readFile("C:\\Users\\eduardovera.PROGRAF\\Workspace\\3dConvexHull\\samples\\socket_cloud.off", GlutManager::points);
//    std::cout << GlutManager::points.size() << std::endl;
//    GlutManager::points.push_back(Vec3d(0, 0, 0));
//    GlutManager::init(argc, argv, 640, 480, "Teste");

    int indexMinY = getMinimalYPoint(GlutManager::points);
    Vec3d MinYPoint = GlutManager::points[indexMinY];

    Vec3d virtualPoint1 = MinYPoint - Vec3d(-1, 0, -1);
    Vec3d virtualPoint2 = MinYPoint - Vec3d(+1, 0, +1);

    GlutManager::points.insert(GlutManager::points.begin(), virtualPoint2);
    GlutManager::points.insert(GlutManager::points.begin(), virtualPoint1);

//    GlutManager::faces.push_back(Vec3i(0, 1, indexMinY));

    writeFile("test.off", GlutManager::points, GlutManager::faces);

    return 0;
}
