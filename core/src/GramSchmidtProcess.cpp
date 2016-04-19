//
// Created by plumat on 4/13/16.
//

#include "../headers/GramSchmidtProcess.h"
#include <stdlib.h>

GramSchmidtProcess::GramSchmidtProcess() {

}

GramSchmidtProcess::~GramSchmidtProcess() {

}

void GramSchmidtProcess::ComputeOrthonormalBasisFromVector(VectorType *v, VectorType *e1, VectorType *e2,
                                                           VectorType *e3) {

    //TODO: check v!={0,0,0}

    VectorType s1 = {0.0,0.0,0.0}, s2 = {0.0,0.0,0.0}; // will be a basis (with input v)
    VectorType p = {0,0,0}, p2 = {0,0,0}; // the projections

    s1 = {-(*v)(1),(*v)(0),0}; s2 = {-(*v)(2),0,(*v)(0)}; // find 2 vectors linearly independent of v

    // prevent s1 or s2 == {0,0,0}
    if( norm(s1) == 0 ){
        s1 = {0,-(*v)(2),(*v)(1)};
    }else if(norm(s2)==0){ // both can't be equal to {0,0,0}, if so, v is {0,0,0}
        s2 = {0,-(*v)(2),(*v)(1)};
    }

    // Gram Schmidt Process
    // compute the orthonormal basis
    *e1 = VectorType(*v);
    *e1 = (*e1) / norm(*e1); // normalisation

    Proj(e1,&s1,&p);
    *e2 = s1 - p;
    *e2 = (*e2) / norm(*e2); // normalisation

    Proj(e1,&s2,&p); Proj(e2,&s2,&p2);
    *e3 = s2 - p - p2;
    *e3 = (*e3) / norm(*e3); // normalisation

    // is basis right handed
    if( dot(*e3,cross(*e1,*e2)) <0 ){
        (*e3) = (*e3) * -1; // change any of the vector
    }

}

void GramSchmidtProcess::Proj(VectorType *u, VectorType *v, VectorType* p) {
    (*p) = (dot(*u,*v)/dot(*u,*u)) * (*u);
}

