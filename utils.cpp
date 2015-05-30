#ifndef UTILS
#define UTILS

#include <iostream>
#include <fstream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void split(vector<string> &tokens, const string &text, string sep) {
    tokens.clear();
    int start = 0, end = 0;
    while ((end = static_cast<int>(text.find(sep, start))) != string::npos) {
        tokens.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(text.substr(start));
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
void writeFile(string filename, const vector<Vec3d> &points, const vector<Vec3i> &faces) {

    string content = "OFF " + to_string(points.size()) + " " + to_string(faces.size()) + " 0\n";

    for (int i = 0; i < points.size(); i++) {
        content += to_string(points[i][0]) + " " + to_string(points[i][1]) + " " + to_string(points[i][2]) + "\n";
    }

    for (int i = 0; i < faces.size(); i++) {
        content += "3 " + to_string(faces[i][0]) + " " + to_string(faces[i][1]) + " " + to_string(faces[i][2]) + "\n";
    }

    ofstream output;
    output.open(filename);
    output << content;
    output.close();
}

int getMinimalYPoint(vector<Vec3d> &points) {
    double minY = DBL_MAX;

    int index = -1;

    for (int i = 0; i < points.size(); i++) {
        if (points[i][1] < minY) {
            index = i;
            minY = points[i][1];
        }
    }

    return index;
}

#endif // UTILS
