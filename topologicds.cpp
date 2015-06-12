#include <opencv2/opencv.hpp>

using namespace cv;

namespace TopologicDS {

    struct Face;
    struct Vertex;
    struct Edge;

    struct HalfEdge {
        HalfEdge *prev;
        HalfEdge *next;
        Face *face;
        Vertex *source;
        Vertex *target;
        Edge *edge;
        bool visited;
    };

    struct Vertex {
        HalfEdge *in;
        HalfEdge *out;
        Vec3d coordinates;
        int index;
    };

    struct Edge {
        HalfEdge *heA;
        HalfEdge *heB;
        Vec3d pA;
        Vec3d pB;
        bool visited;
    };

    struct Face {
        HalfEdge *he;
        Vec3d normal;
    };

    vector<Edge*> edges;
    vector<Face*> faces;
    vector<Face*> stack;
    vector<Vertex*> vertexes;
    vector<HalfEdge*> halfedges;

    Vec3d normal(Vec3d p1, Vec3d p2, Vec3d p3) {

        Vec3d n = (p3 - p1).cross(p2 - p1);
        return n / norm(n);
    }

    Edge *getEdge(HalfEdge *he) {
        Vec3d p1 = he->source->coordinates;
        Vec3d p2 = he->target->coordinates;

        for (int i = 0; i < edges.size(); i++) {
            if ((edges[i]->heA->source->coordinates == p1 && edges[i]->heA->target->coordinates == p2) ||
                    (edges[i]->heA->source->coordinates == p2 && edges[i]->heA->target->coordinates == p1)) {
                return edges[i];
            }
        }
        Edge *edge = (Edge*) malloc(sizeof(Edge));
        edge->heA = he;
        edge->heB = NULL;
        edge->pA = p1;
        edge->pB = p2;
        edge->visited = false;
        edges.push_back(edge);
        return edge;
    }

    Vertex *getVertex(Vec3d p) {
        for (int i = 0; i < vertexes.size(); i++) {
            if (vertexes[i]->coordinates == p) {
                return vertexes[i];
            }
        }

        Vertex *v = (Vertex*) malloc(sizeof(Vertex));
        v->coordinates = p;
        vertexes.push_back(v);
        return v;
    }

    using namespace std;
    Face *getFace(HalfEdge *he) {
        Face *face = (Face*) malloc(sizeof(Face));
        face->he = he;
        return face;
    }

    HalfEdge *getHalfEdge(vector<Vec3d*> &points) {
        for (int i = 0; i < halfedges.size(); i++) {
            for (int j = 0; j < points.size(); j++) {
                Vec3d p1 = *points[j];
                Vec3d p2;
                if (j + 1 == points.size()) {
                    p2 = *points[0];
                } else {
                    p2 = *points[j + 1];
                }
                if (halfedges[i]->source->coordinates == p1 && halfedges[i]->target->coordinates == p2) {
                    return halfedges[i];
                }
            }
        }
        return NULL;
    }

    HalfEdge *insert(vector<Vec3d*> points) {
        HalfEdge *he = getHalfEdge(points);
        if (he == NULL) {
            vector<HalfEdge*> halfEdgeList;
            for (int i = 0; i < points.size(); i++) {
                Vertex *v0 = getVertex(*points[i]);
                Vertex *v1;
                if (i + 1 == points.size()) {
                    v1 = getVertex(*points[0]);
                } else {
                    v1 = getVertex(*points[i + 1]);
                }

                he = (HalfEdge*) malloc(sizeof(HalfEdge));
                he->source = v0;
                he->target = v1;
                he->visited = false;
                Edge *edge = getEdge(he);
                he->edge = edge;
                if (edge->heA == NULL) {
                    edge->heA = he;
                } else {
                    edge->heB = he;
                }
                halfEdgeList.push_back(he);
            }
            Face *face = getFace(halfEdgeList[0]);
            faces.push_back(face);
            stack.push_back(face);
            face->normal = normal(halfEdgeList[0]->source->coordinates, halfEdgeList[1]->source->coordinates, halfEdgeList[2]->source->coordinates);
            for (int i = 0; i < halfEdgeList.size(); i++) {
                int index_nxt = i + 1;
                if (index_nxt == halfEdgeList.size()) {
                    index_nxt = 0;
                }
                halfEdgeList[i]->next = halfEdgeList[index_nxt];
                halfEdgeList[index_nxt]->prev = halfEdgeList[i];
                halfEdgeList[i]->face = face;
                halfedges.push_back(halfEdgeList[i]);
            }
            halfEdgeList[0]->prev = halfEdgeList[halfEdgeList.size() - 1];

        }
        return he;
    }
}
