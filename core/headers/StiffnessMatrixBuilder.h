//
// Created by plumat on 20/04/16.
//

#ifndef SSO_STIFFNESSMATRIX_H
#define SSO_STIFFNESSMATRIX_H

#include "armadillo"

class StiffnessMatrixBuilder {
public:

    typedef arma::fmat StiffnessMatrixType;

    StiffnessMatrixBuilder();
    ~StiffnessMatrixBuilder();

    void Build(StiffnessMatrixType* kl);
    const StiffnessMatrixType GetStiffnessMatrix();
    StiffnessMatrixType* GetStiffnessMatrixPointer();

private:
    StiffnessMatrixType* m_kg;
};

#endif //SSO_STIFFNESSMATRIX_H
