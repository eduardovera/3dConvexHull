#ifndef GLUTMANAGER_H
#define GLUTMANAGER_H

#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;


class GlutManager {
    public:
        static double signal;
        static void init(int argc, char *argv[], const int &h, const int &w, const char *name);
        static void display(void);
        static void keyPress(unsigned char key, int x, int y);
        static void mouseWheel(int button, int state, int x, int y);
        static void handleResize(int w, int h);
        static vector<Vec3d> points;
        static vector<Vec3i> faces;
};

#endif // GLUTMANAGER_H
