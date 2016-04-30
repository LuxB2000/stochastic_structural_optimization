//
// Created by plumat on 4/8/16.
//
// A simple class representing a point in space

#ifndef SSO_POINT_H
#define SSO_POINT_H

class Point{
public:
    // coordinates are given in millimeters in the GLOBAL system.
    Point(float x_coord, float y_coord, float z_coord);
    Point(const Point& p);
    ~Point();

    float x, y, z;
};

#endif //SSO_POINT_H
