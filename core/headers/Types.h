//
// Created by plumat on 3/05/16.
//

#ifndef SSO_TYPES_H
#define SSO_TYPES_H

#include "armadillo"
#include <vector>

typedef arma::fmat StiffnessMatrixType;
typedef arma::fmat TransformationMatrixType;
typedef arma::fvec ForceVectorType;
typedef arma::fvec InternalForceVectorType;

typedef arma::fvec DisplacementVectorType;
typedef struct BoundaryConditionsTyped  {unsigned  int bc[2];} BoundaryConditionsType;
typedef std::vector<BoundaryConditionsType>   BoundaryConditionsVectorType;
typedef std::vector<float> FrameParametersVectorType;
typedef std::vector<InternalForceVectorType*> ElementVectorType;

#endif //SSO_TYPES_H
