#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cmath>
using namespace std;
const double pi = std::acos(-1);

//#include "convexhull.hpp"
//-----------------------------------------------------------------------------
// A C++ program to find convex hull of a set of points. Refer
// https://www.geeksforgeeks.org/orientation-3-ordered-points/
// for explanation of orientation()
#include <iostream>
#include <stack>
#include <stdlib.h>
using namespace std;
 
struct Point
{
    double x, y;
};
 
// A globle point needed for  sorting points with reference
// to  the first point Used in compare function of qsort()
Point p0;
 
// A utility function to find next to top in a stack
Point nextToTop(stack<Point> &S)
{
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}
 
// A utility function to swap two points
int swap(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}
 
// A utility function to return square of distance
// between p1 and p2
int distSq(Point p1, Point p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x) +
          (p1.y - p2.y)*(p1.y - p2.y);
}
 
// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
 
    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}
 
// A function used by library function qsort() to sort an array of
// points with respect to the first point
int compare(const void *vp1, const void *vp2)
{
   Point *p1 = (Point *)vp1;
   Point *p2 = (Point *)vp2;
 
   // Find orientation
   int o = orientation(p0, *p1, *p2);
   if (o == 0)
     return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;
 
   return (o == 2)? -1: 1;
}
 
// Prints convex hull of a set of n points.
stack<Point> convexHull(Point points[], int n)
{
   // Find the bottommost point
   int ymin = points[0].y, min = 0;
   for (int i = 1; i < n; i++)
   {
     int y = points[i].y;
 
     // Pick the bottom-most or chose the left
     // most point in case of tie
     if ((y < ymin) || (ymin == y &&
         points[i].x < points[min].x))
        ymin = points[i].y, min = i;
   }
 
   // Place the bottom-most point at first position
   swap(points[0], points[min]);
 
   // Sort n-1 points with respect to the first point.
   // A point p1 comes before p2 in sorted ouput if p2
   // has larger polar angle (in counterclockwise
   // direction) than p1
   p0 = points[0];
   qsort(&points[1], n-1, sizeof(Point), compare);
 
   // If two or more points make same angle with p0,
   // Remove all but the one that is farthest from p0
   // Remember that, in above sorting, our criteria was
   // to keep the farthest point at the end when more than
   // one points have same angle.
   int m = 1; // Initialize size of modified array
   for (int i=1; i<n; i++)
   {
       // Keep removing i while angle of i and i+1 is same
       // with respect to p0
       while (i < n-1 && orientation(p0, points[i],
                                    points[i+1]) == 0)
          i++;
 
 
       points[m] = points[i];
       m++;  // Update size of modified array
   }
 
   // If modified array of points has less than 3 points,
   // convex hull is not possible
   stack<Point> S;
   if (m < 3) return S;
 
   // Create an empty stack and push first three points
   // to it.
   S.push(points[0]);
   S.push(points[1]);
   S.push(points[2]);
 
   // Process remaining n-3 points
   for (int i = 3; i < m; i++)
   {
      // Keep removing top while the angle formed by
      // points next-to-top, top, and points[i] makes
      // a non-left turn
      while (S.size()>1 && orientation(nextToTop(S), S.top(), points[i]) != 2)
         S.pop();
      S.push(points[i]);
   }
 
//    // Now stack has the output points, print contents of stack
//    while (!S.empty())
//    {
//        Point p = S.top();
//        cout << "(" << p.x << ", " << p.y <<")" << endl;
//        S.pop();
//    }

    return S;
}
 
// // Driver program to test above functions
// int main()
// {
//     Point points[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
//                       {0, 0}, {1, 2}, {3, 1}, {3, 3}};
//     int n = sizeof(points)/sizeof(points[0]);
//     convexHull(points, n);
//     return 0;
// }
//-----------------------------------------------------------------------------

// alien cube

void next_rot(double& xr, double &zr)
{
    if (xr<45.) xr+=0.0001;
    else if (zr<45.) zr +=0.0001;
    else exit(0);
}

void face_centers(double xr, double zr)
{
    double x[] = {.5,0,0,};
    double y[] = {0,.5,0,};
    double z[] = {0,0,.5,};

    for (int i=0;i<3;++i)
    {
        // rotate about x
        double cosxr = cos(xr*pi/180.);
        double sinxr = sin(xr*pi/180.);
        // y' = y*cos q - z*sin q
        // z' = y*sin q + z*cos q
        double yp = y[i]*cosxr-z[i]*sinxr;
        double zp = y[i]*sinxr+z[i]*cosxr;
        
        // save rotated coords
        y[i] = yp;
        z[i] = zp;

        // rotate about z
        double coszr = cos(zr*pi/180.);
        double sinzr = sin(zr*pi/180.);
        // x' = x*cos q - y*sin q
        // y' = x*sin q + y*cos q
        double xp = x[i]*coszr-y[i]*sinzr;
        double ypp= x[i]*sinzr+y[i]*coszr;

        // save rotated coords
        x[i] = xp;
        y[i] = ypp;

        cout << (abs(x[i])<0.000001?0:x[i]) << " " << 
                (abs(y[i])<0.000001?0:y[i]) << " " << 
                (abs(z[i])<0.000001?0:z[i]) << "\n";
    }
}

double calc_area(double xr, double zr)
{
    double x[] = {-.5,.5,.5,-.5,-.5,.5,.5,-.5,};
    double z[] = {-.5,-.5,.5,.5,-.5,-.5,.5,.5,};
    double y[] = {.5,.5,.5,.5,-.5,-.5,-.5,-.5,};

    for (int i=0;i<8;++i)
    {
        // rotate about x
        double cosxr = cos(xr*pi/180.);
        double sinxr = sin(xr*pi/180.);
        // y' = y*cos q - z*sin q
        // z' = y*sin q + z*cos q
        double yp = y[i]*cosxr-z[i]*sinxr;
        double zp = y[i]*sinxr+z[i]*cosxr;
        
        // save rotated coords
        y[i] = yp;
        z[i] = zp;

        // rotate about z
        double coszr = cos(zr*pi/180.);
        double sinzr = sin(zr*pi/180.);
        // x' = x*cos q - y*sin q
        // y' = x*sin q + y*cos q
        double xp = x[i]*coszr-y[i]*sinzr;
        double ypp= x[i]*sinzr+y[i]*coszr;

        // save rotated coords
        x[i] = xp;
        y[i] = ypp;
    }

    // copy rotated x,z into points to compute convex hull
    Point points[8];
    for  (int i=0;i<8;++i) {
        points[i] = Point {x[i],z[i]};
    }

    // get a convex hull
    stack<Point> hull = convexHull(points,8);

    // copy into vec of points
    vector<Point> vec;
    while (!hull.empty())
    {
        Point p = hull.top();
        if (!any_of(begin(vec),end(vec),[&](Point& t){
            return abs(p.x-t.x)<0.00000000001 && abs(p.y-t.y)<0.00000000001;
        }))
            vec.push_back(p);
        hull.pop();
    }

    // calculate area using points
    double area=0.;
    for (int i=0,j=vec.size()-1;i<vec.size();j=i,++i) {
        area+=(vec[i].x+vec[j].x)*(vec[j].y-vec[i].y);
    }

    return area;
}

main()
{
    // read count  of tests
    auto cases=0;
    cin >> cases;

    cout.precision(12);

    // for test cases
    for (int i=1;i<=cases;++i)
    {
        // read desired area
        double area=0.;
        cin >> area;

        double xr=0.,zr=0.000001;
        while (abs(calc_area(xr,zr)-area)>0.0000001) {
//            cout << "" << xr << " " << zr << " " << calc_area(xr,zr) << endl;
            next_rot(xr,zr);
        }
        next_rot(xr,zr);
        cout << "Rotations: " << xr << " " << zr << " " << calc_area(xr,zr) << endl;

        // rotate and print face centers
        cout << "Case #" << i << ":\n";
        face_centers(xr,zr);
    }
}

// // Driver program to test convex hull
// int main()
// {
//     Point points[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
//                       {0, 0}, {1, 2}, {3, 1}, {3, 3}};
//     int n = sizeof(points)/sizeof(points[0]);
//     convexHull(points, n);
//     return 0;
// }