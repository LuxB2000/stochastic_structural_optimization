//
// Created by plumat on 4/6/16.
//
// A truss is a structure that consists of axial members connected by pin joints.
// The loads on a truss are assumed to be concentrated at the joints.
// The members of a truss support the external load through axial force as they do not undergo bending deformation.
// Therefore, no bending moments are present in truss members.
//
// A truss is characterised by
// - 2 points (2 joints, from which we deduce the length L=sqrt((p1_x-p2_x)^2+(p1_y-p2_y)^2+(p1_z-p2_z)^2)
// - a cross section A
// - Young’s modulus E (specified by the material)
//

#ifndef SSO_TRUSS_H
#define SSO_TRUSS_H

#include <vector>

#include "StructuralElement.h"

class Truss: StructuralElement {
public:
    Truss(Point* starting_pt, Point* ending_pt); //todo: enum to specific material, A
    ~Truss();

    typedef arma::fmat StiffnessMatrixType;
    typedef arma::fmat TransformationMatrixType;

    bool check(){ return true;}

    StiffnessMatrixType*      GetLocalStiffnessMatrix();
    TransformationMatrixType* GetLocalTransformationMatrix();

private:
    Point *m_start_p, *m_end_p;
    StiffnessMatrixType      *m_k;
    TransformationMatrixType *m_c;
};


#endif //SSO_TRUSS_H
