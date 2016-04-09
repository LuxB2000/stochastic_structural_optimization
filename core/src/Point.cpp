//
// Created by plumat on 4/8/16.
//

#include "../headers/Point.h"

Point::Point(float x_coord, float y_coord, float z_coord){
    x = x_coord;
    y = y_coord;
    z = z_coord;
}

Point::~Point() {

}

Point::Point(const Point &p) {
    x = p.x;
    y = p.y;
    z = p.z;

}


