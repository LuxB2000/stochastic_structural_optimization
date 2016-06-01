//
// Created by plumat on 4/8/16.
//

#include "../headers/Point.h"

Point::Point(float x_coord, float y_coord, float z_coord){
    x = x_coord;
    y = y_coord;
    z = z_coord;
		index = -1;
}

Point::Point(float x_coord, float y_coord, float z_coord, int id){
    x = x_coord;
    y = y_coord;
    z = z_coord;
		index = id;
}

Point::~Point() {

}

Point::Point(const Point &p) {
    x = p.x;
    y = p.y;
    z = p.z;
		index = -1; //TODO: find solution here
}

bool Point::operator==(const Point &p) const {
	return (this->x==p.x && this->y==p.y && this->z==p.z);
}

bool Point::operator!=(const Point &p) const {
	return (this->x!=p.x || this->y!=p.y || this->z!=p.z);
}

