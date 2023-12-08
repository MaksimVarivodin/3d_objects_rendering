#pragma once
#include"Point.h"
class KochCurve
{
private:
    static void countNewPoints(const Point& v1,  const Point & v2, Point & pA, Point &pB, Point &pC) {
        // counting new Points
        pA = Point((2 * v1.x + v2.x) / 3, (2 * v1.y + v2.y) / 3);
        pB = Point((v1.x + v2.x) / 2 + (v2.y - v1.y) / (2 * (float)sqrt(3)), (v1.y + v2.y) / 2 + (v1.x - v2.x) / (2 * (float)sqrt(3)));
        pC = Point((v1.x + 2 * v2.x) / 3, (v1.y + 2 * v2.y) / 3);
    }
    static list<Point> recursiveCount(const Point & v1, const Point & v2, const int& depth)
    {

        list<Point> list;
        if (depth != 0)
        {
            Point pA,pB,pC;
            // counting new Points
            countNewPoints( v1, v2, pA, pB, pC );

            // passing to the function to continue recursive count
			list.append_range(recursiveCount(v1, pA, depth - 1));
			list.append_range(recursiveCount(pA, pB, depth - 1));
			list.append_range(recursiveCount(pB, pC, depth - 1));
			list.append_range(recursiveCount(pC, v2, depth - 1));

        }
        else {
            list.push_back(v1);
        }
        return list;
    }
public:
    static  list<Point> encreaseDepth(const Point &v1, const Point &v2, int depth) {
        return recursiveCount(v1, v2, depth);
    }

};

