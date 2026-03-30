#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;


struct Point {
    double x, y;

    Point(double _x = 0, double _y = 0) {
        x = _x;
        y = _y;
    }
};

struct Edge {
    Point a;
    Point b;

    Edge(Point _a, Point _b) : a(_a), b(_b) {}

    bool isEqual(Edge other) {
        return (a.x == other.a.x && a.y == other.a.y && b.x == other.b.x && b.y == other.b.y) ||
               (a.x == other.b.x && a.y == other.b.y && b.x == other.a.x && b.y == other.a.y);
    }
};

struct Triangle {
    Point p1, p2, p3;

    Triangle(Point _p1, Point _p2, Point _p3) : p1(_p1), p2(_p2), p3(_p3) {}
    
    bool containsInCircumcircle(Point p) const {
        double x1 = p1.x, y1 = p1.y;
        double x2 = p2.x, y2 = p2.y;
        double x3 = p3.x, y3 = p3.y;

        double D = 2 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
        double ux = ((x1 * x1 + y1 * y1) * (y2 - y3) + (x2 * x2 + y2 * y2) * (y3 - y1) + (x3 * x3 + y3 * y3) * (y1 - y2)) / D;
        double uy = ((x1 * x1 + y1 * y1) * (x3 - x2) + (x2 * x2 + y2 * y2) * (x1 - x3) + (x3 * x3 + y3 * y3) * (x2 - x1)) / D;
        
        double radiusSq = pow(x1 - ux, 2) + pow(y1 - uy, 2);
        double distSq = pow(p.x - ux, 2) + pow(p.y - uy, 2);
        
        return distSq < radiusSq;
    }
};



vector<Triangle> bowyerWatson(vector<Point> points) {
  
    Point s1(-1000, -1000);
    Point s2(1000, -1000);
    Point s3(0, 1000);
    Triangle super(s1, s2, s3);

    vector<Triangle> triangulation;
    triangulation.push_back(super);

    for (int i = 0; i < points.size(); i++) {
        Point p = points[i];
        vector<Triangle> badTriangles;

        for (int j = 0; j < triangulation.size(); j++) {
            if (triangulation[j].containsInCircumcircle(p)) {
                badTriangles.push_back(triangulation[j]);
            }
        }

    
        vector<Edge> polygon;
        for (int j = 0; j < badTriangles.size(); j++) {
            Triangle t = badTriangles[j];
            Edge edges[3] = { Edge(t.p1, t.p2), Edge(t.p2, t.p3), Edge(t.p3, t.p1) };

            for (int e = 0; e < 3; e++) {
                bool isShared = false;
                for (int other = 0; other < badTriangles.size(); other++) {
                    if (j == other) continue;
                    Triangle ot = badTriangles[other];
                    Edge otherEdges[3] = { Edge(ot.p1, ot.p2), Edge(ot.p2, ot.p3), Edge(ot.p3, ot.p1) };
                    for (int oe = 0; oe < 3; oe++) {
                        if (edges[e].isEqual(otherEdges[oe])) isShared = true;
                    }
                }
                if (!isShared) polygon.push_back(edges[e]);
            }
        }

        
        vector<Triangle> nextTriangulation;
        for (int j = 0; j < triangulation.size(); j++) {
            bool isBad = false;
            for (int k = 0; k < badTriangles.size(); k++) {
                if (triangulation[j].p1.x == badTriangles[k].p1.x && 
                    triangulation[j].p1.y == badTriangles[k].p1.y &&
                    triangulation[j].p2.x == badTriangles[k].p2.x) {
                    isBad = true;
                }
            }
            if (!isBad) nextTriangulation.push_back(triangulation[j]);
        }
        triangulation = nextTriangulation;

      
        for (int j = 0; j < polygon.size(); j++) {
            triangulation.push_back(Triangle(polygon[j].a, polygon[j].b, p));
        }
    }

    vector<Triangle> finalTriangulation;
    for (int i = 0; i < triangulation.size(); i++) {
    Triangle t = triangulation[i];
    
  
    bool touchesSuper = false;
    Point superPoints[3] = { Point(-1000, -1000), Point(1000, -1000), Point(0, 1000) };
    
    for (int sp = 0; sp < 3; sp++) {
        if ((t.p1.x == superPoints[sp].x && t.p1.y == superPoints[sp].y) ||
            (t.p2.x == superPoints[sp].x && t.p2.y == superPoints[sp].y) ||
            (t.p3.x == superPoints[sp].x && t.p3.y == superPoints[sp].y)) {
            touchesSuper = true;
        }
    }

    if (!touchesSuper) {
        finalTriangulation.push_back(t);
    }
}

    return finalTriangulation;

}

int main() {
    vector<Point> points = {
        {10, 10}, {150, 10}, {75, 120}, {80, 40}, {30, 80}
    };

    vector<Triangle> result = bowyerWatson(points);

    cout << result.size() << endl;
    for (size_t i = 0; i < result.size(); ++i) {
        cout << "Triangle " << i + 1 << ": "
                  << "(" << result[i].p1.x << "," << result[i].p1.y << ") "
                  << "(" << result[i].p2.x << "," << result[i].p2.y << ") "
                  << "(" << result[i].p3.x << "," << result[i].p3.y << ")\n";
    }

    return 0;
}
