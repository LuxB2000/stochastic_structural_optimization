//
// Created by plumat on 4/8/16.
//

#include "../headers/Point.h"

Point::Point(float x_coord, float y_coord, float z_coord, unsigned long id){
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
		index = p.index;
}

bool Point::operator==(const Point &p) const {
	return (this->x==p.x && this->y==p.y && this->z==p.z);
}

bool Point::operator!=(const Point &p) const {
	return (this->x!=p.x || this->y!=p.y || this->z!=p.z);
}

std::ostream& operator<<(std::ostream &os, const Point &p){
	os << "[" << p.x << ", " << p.y << ", " << p.z << "]";
	return os;
}
