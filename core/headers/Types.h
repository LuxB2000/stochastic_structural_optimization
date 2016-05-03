//
// Created by plumat on 3/05/16.
//

#ifndef SSO_TYPES_H
#define SSO_TYPES_H

typedef arma::fmat StiffnessMatrixType;
typedef arma::fmat TransformationMatrixType;
typedef arma::fvec ForceVectorType;

typedef arma::fvec DisplacementVectorType;
typedef struct BoundaryConditionsTyped  {unsigned  int bc[2];} BoundaryConditionsType;
typedef std::vector<BoundaryConditionsType>   BoundaryConditionsVectorType;

#endif //SSO_TYPES_H
