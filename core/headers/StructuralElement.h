//
// Created by plumat on 4/6/16.
//

#ifndef SSO_STRUCTURALELEMENT_H
#define SSO_STRUCTURALELEMENT_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

class Point{
public:
    Point(float x_coord, float y_coord, float z_coord){
        x = x_coord;
        y = y_coord;
        z = z_coord;
    }
    ~Point(){

    }

    float x, y, z;
};

class StructuralElement {
public:
    StructuralElement();
    virtual ~StructuralElement();
    virtual void Print();

protected:
    double m_length, m_width;
};


#endif //SSO_STRUCTURALELEMENT_H
