#include <opencv2/opencv.hpp>
#include <iostream>
#include <main.cpp>

using namespace cv;
using namespace std;

void getPoints(const Mat1b &image, vector<Vec3d> &points) {
    for (int j = 0; j < image.rows; j++) {
        for (int i = 0; i < image.cols; i++) {
            if (image(j, i) == static_cast<uchar>(0)) {
                points.push_back(Vec3d(i, j ,1));
            }
        }
    }
}

void drawLine(Mat1b &img, Vec3d start, Vec3d end ) {
    Point2d ps(start[0], start[1]);
    Point2d pe(end[0], end[1]);
    line(img, ps, pe, Scalar(0, 0, 0));
}

int mainA() {
    Vec3d p0(40, 200, 1);
    Vec3d p1(210, 198, 1);
    Mat1b image = imread("C:\\Users\\Eduardo\\Workspace\\3dConvexHull\\points.png", IMREAD_GRAYSCALE);

    vector<Vec3d> points;
    getPoints(image, points);


    vector<Vec3d*> ptr_points;
    for (int i = 0; i < points.size(); i++) {
        if (points[i] != p0 && points[i] != p1) {
            ptr_points.push_back(&points[i]);
        }
    }

    vector<Vec3d*> hull = giftWrapping2D(&p0, &p1, ptr_points);

    for (int i = 0; i < hull.size(); i++) {
        int index_next = i + 1;
        if (index_next == hull.size()) {
            index_next = 0;
        }
        drawLine(image, *hull[i], *hull[index_next]);
    }
    imshow("teste", image);
    waitKey();
    return 0;

}

