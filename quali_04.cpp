#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cmath>
using namespace std;
const double pi = std::acos(-1);

#include "convexhull.hpp"

// alien cube

void next_rot(double& xr, double &zr)
{
    if (xr<45) xr+=0.1;
    else zr+=0.1;
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

    // sort x and z by distance from origin
    int indices[] = {0,1,2,3,4,5,6,7,};
    sort(begin(indices),end(indices),[&](int& l,int& r){
        return x[indices[l]]*x[indices[l]]+z[indices[l]]*z[indices[l]]<
                x[indices[r]]*x[indices[r]]+z[indices[r]]*z[indices[r]];
    });

    // reorder
    double xp[8], zp[8];
    for (int i=0;i<8;++i) {
        xp[i] = x[indices[i]];
        zp[i] = z[indices[i]];
        cout << i << " " << xp[i] << " " << zp[i] << "\n";
    }

    // calculate area using 6 points
    double area=0.;
    for (int i=4,j=7;i<8;j=i,++i) {
        area+=(xp[i]+xp[j])*(zp[j]-zp[i]);
    }

    return area;
}

main()
{
    double xr=0.,zr=45.;
    cout << "Area: " << calc_area(xr,zr) << endl;
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