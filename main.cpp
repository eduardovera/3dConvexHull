#include <QCoreApplication>
#include <iostream>
#include <topologicds.cpp>
#include <utils.cpp>

#define DEBUG

using namespace std;
using namespace TopologicDS;
using namespace cv;

vector<Vec3d> points;
vector<FaceOff> facesOFFFile;

bool isOnList(Vec3d *p, vector<Vec3d*> &list) {
    for (int i = 0; i < list.size(); i++) {
        if (p == list[i]) {
            return true;
        }
    }
    return false;
}

vector<Vec3d*> giftWrapping2D(Vec3d* p_source, Vec3d* p_target, vector<Vec3d*> &points) {
    Vec3d* p_it_source = p_source;
    Vec3d* p_it_target = p_target;
    double dot;

    if (points.size() != 1) {
        points.push_back(p_target);
        points.push_back(p_source);
    }

    vector<Vec3d*> hullPoints;
    hullPoints.push_back(p_source);
    hullPoints.push_back(p_target);

    vector<Vec3d*> evaluated;
    evaluated.push_back(p_target);

    do {
        double minDot = DBL_MAX;
        Vec3d v1 = *p_it_source - *p_it_target;
        Vec3d *p_minDot = NULL;
        for (int i = 0; i < points.size(); i++) {
            if (!isOnList(points[i], evaluated)) {
                Vec3d v2 = *points[i] - *p_it_target;
                v1 = normalize(v1);
                v2 = normalize(v2);
                dot = v1.dot(v2);
                if (dot < minDot) {
                    minDot = dot;
                    p_minDot = points[i];
                }
            }
        }

        if (p_minDot == NULL) {
            break;
        }
        evaluated.push_back(p_minDot);
        hullPoints.push_back(p_minDot);
        p_it_source = p_it_target;
        p_it_target = p_minDot;
    } while (*p_it_target != *p_source);
    return (hullPoints);
}

vector<Vec3d*> evaluatedPoints;

void giftWrapping(const HalfEdge *he) {
    Vec3d v1 = he->target->coordinates;
    Vec3d v2 = he->source->coordinates;

    map<double, vector<Vec3d*>> pointsDot;

    Vec3d n1 = he->face->normal;
    double maxDot = DBL_MIN;
    double dot;
    for (int i = 0; i < points.size(); i++) {
        Vec3d n2 = normal(v1, v2, points[i]);
        dot = n1.dot(n2);
        if (dot >= maxDot) {
            maxDot = dot;
            pointsDot[dot].push_back(&points[i]);
        }
    }

    if (pointsDot[maxDot].size() == 0) {
        return;
    }

    vector<Vec3d*> pointsOnHull = giftWrapping2D(&v1, &v2, pointsDot[maxDot]);
    insert(pointsOnHull);
}

void draw(const vector<Face*> &hull, vector<Vec3d> &points) {
    #ifdef DEBUG
        cout << "\t";
    #endif
    cout << "Generating OFF file...... ";
    facesToOffFormat(hull, points, facesOFFFile);
    writeFile("teste.off", points, facesOFFFile);
    cout << "Done!" << endl;
}

int main() {

    readFile("C:\\Users\\Eduardo\\Workspace\\3dConvexHull\\samples\\dodec_cloud.off", points);
    int index = generateVirtualPoints(points);

    vector<Vec3d*> pointsOnHull;
    pointsOnHull.push_back(&points[0]);
    pointsOnHull.push_back(&points[1]);
    index += 2;
    pointsOnHull.push_back(&points[index]);

    cout << "Initializing hull...... ";

    HalfEdge *he = insert(pointsOnHull);

    cout << "Done!" << endl;

    HalfEdge *iterator = NULL;
    vector<Face*> hull;

    int count = 0;

    cout << "Calculating hull faces...... ";
    while (stack.size() != 0) {
        he = stack[0]->he;
        stack.erase(stack.begin());
        iterator = he;
        count ++;
        hull.push_back(iterator->face);
        #ifdef DEBUG
            cout << endl;
            draw(hull, points);
            getchar();
        #endif
        do {
            if (!iterator->edge->visited) {
                giftWrapping(iterator);
                iterator->edge->visited = true;
            }
            iterator = iterator->next;
        } while (iterator->source->coordinates != he->source->coordinates && iterator->target->coordinates != he->target->coordinates );
    }
    cout << "Done!" << endl;
    draw(hull, points);
    return 0;

}
