//
// Created by plumat on 4/6/16.
//

#ifndef SSO_STRUCTURALELEMENT_H
#define SSO_STRUCTURALELEMENT_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <armadillo>

#include "PointManager.h"


class StructuralElement {
public:
    StructuralElement();
    virtual ~StructuralElement();
    virtual void Print();

protected:
		//TODO remove
    double m_length, m_width;
};


#endif //SSO_STRUCTURALELEMENT_H
