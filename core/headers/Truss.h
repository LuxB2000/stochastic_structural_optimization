//
// Created by plumat on 4/6/16.
//

#ifndef SSO_TRUSS_H
#define SSO_TRUSS_H

#include <vector>

#include "StructuralElement.h"

class Truss: StructuralElement {
public:
    Truss(Point* starting_pt, Point* ending_pt); //todo: enum to specific material
    ~Truss();

    typedef std::vector<double> StiffnessVectorType;
    typedef std::vector<double> TransformationVectorType;

    bool check(){ return true;}

    StiffnessVectorType* GetLocalStiffnessMatrix();
    TransformationVectorType* GetLocalTransformationMatrix();

private:
    Point *m_start_p, *m_end_p;
    StiffnessVectorType *m_k;
    TransformationVectorType *m_c;
};


#endif //SSO_TRUSS_H
