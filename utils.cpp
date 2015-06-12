#include <iostream>
#include <fstream>
#include <string>
#include <opencv2/opencv.hpp>
//#include <topologicds.cpp>

using namespace std;
using namespace cv;
using namespace TopologicDS;

struct FaceOff {
    vector<int> points;
};

void facesToOffFormat(const vector<Face*> &hull, const vector<Vec3d> &points, vector<FaceOff> &facesOFF) {


    for (int i = 0; i < hull.size(); i++) {
        FaceOff off;
        HalfEdge *iterator = hull[i]->he->next;

        do {
            for (int i = 0; i < points.size(); i++) {

                    if (points[i] == iterator->source->coordinates) {
                        off.points.push_back(i);
                    }
            }
            iterator = iterator->next;
        } while (iterator->source->coordinates != hull[i]->he->next->source->coordinates &&
                 iterator->target->coordinates != hull[i]->he->next->target->coordinates);
        if (off.points.size() >= 3) {
            facesOFF.push_back(off);
        }
    }
}

void split(vector<string> &tokens, const string &text, string sep) {
    tokens.clear();
    int start = 0, end = 0;
    while ((end = static_cast<int>(text.find(sep, start))) != string::npos) {
        tokens.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(text.substr(start));
}

int getMinimalZPoint(vector<Vec3d> &points) {
    double minZ = DBL_MAX;

    int index = -1;

    for (int i = 0; i < points.size(); i++) {
        if (points[i][2] < minZ) {
            index = i;
            minZ = points[i][2];
        }
    }
    return index;
}

int generateVirtualPoints(vector<Vec3d> &points) {
    int index = getMinimalZPoint(points);
    Vec3d p0 = points[index];
    Vec3d v0 = p0 + Vec3d(0.001, 0, 0);
    Vec3d v1 = p0 + Vec3d(0, -0.001, 0);
    points.insert(points.begin(), v1);
    points.insert(points.begin(), v0);
    return index;
}

void readFile(string filename, vector<Vec3d> &points) {
    ifstream infile(filename);
    string line;
    vector<string> tokens;
    while (getline(infile, line)) {
        split(tokens, line, " ");
        if (tokens[0] == "OFF") {
            continue;
        }
        points.push_back(Vec3d(stof(tokens[0]), stof(tokens[1]), stof(tokens[2])));
        tokens.empty();
    }
}

using namespace TopologicDS;

void writeFile(string filename, const vector<Vec3d> &points, const vector<FaceOff> &faces) {

    string content = "OFF " + to_string(points.size()) + " " + to_string(faces.size()) + " 0\n";
    for (int i = 0; i < points.size(); i++) {
        content += to_string(points[i][0]) + " " + to_string(points[i][1]) + " " + to_string(points[i][2]) + "\n";
    }

    for (int i = 0; i < faces.size(); i++) {
        content += to_string(faces[i].points.size());
        for (int j = 0; j < faces[i].points.size(); j++) {
            content += " " + to_string(faces[i].points[j]);
        }
        content += "\n";
    }

    ofstream output;
    output.open(filename);
    output << content;
    output.close();
}

