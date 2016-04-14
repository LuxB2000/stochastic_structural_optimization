//
// Created by plumat on 4/13/16.
//

#include "../headers/GramSchmidtProcess.h"

GramSchmidtProcess::GramSchmidtProcess() {

}

GramSchmidtProcess::~GramSchmidtProcess() {

}

void GramSchmidtProcess::ComputeOrthonormalBasisFromVector(VectorType *v, VectorType *e1, VectorType *e2,
                                                           VectorType *e3) {

}

void GramSchmidtProcess::Proj(VectorType *u, VectorType *v, VectorType* p) {
    (*p) = (dot(*u,*v)/dot(*u,*u)) * (*u);
}

