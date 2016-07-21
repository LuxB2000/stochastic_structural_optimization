//
// Created by plumat on 4/8/16.
//
// A simple class representing a point in space

#ifndef SSO_POINT_H
#define SSO_POINT_H

#include <iostream>
#include "sso_tools.h"

class Point{
public:
    // coordinates are given in millimeters in the GLOBAL system.
    Point(float x_coord, float y_coord, float z_coord, unsigned long id);
    Point(const Point& p);
    ~Point();

		// operator
		bool operator==(const Point &p) const;
		bool operator!=(const Point &p) const;

		//typedef long double IndexType;
		typedef unsigned long int IndexType;

    float x, y, z;
		IndexType index;

		// print Point values in standard display
		friend std::ostream& operator<<(std::ostream&, const Point &p);
};


#endif //SSO_POINT_H
