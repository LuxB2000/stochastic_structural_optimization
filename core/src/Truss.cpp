//
// Created by plumat on 4/6/16.
//

#include "../headers/Truss.h"

Truss::Truss(Point* s_pt, Point *e_pt) {
    m_start_p = s_pt;
    m_end_p = e_pt;
    m_k = new StiffnessMatrixType(3,3,arma::fill::zeros); // 3x3 matrix with 0 values
    m_c = new TransformationMatrixType(6,6,arma::fill::zeros); // 6x6 matrix with 0 values
}

Truss::~Truss() {
    if(m_k) delete m_k;
    if(m_c) delete m_c;
}

Truss::StiffnessMatrixType* Truss::GetLocalStiffnessMatrix() {
    return m_k;
}

Truss::TransformationMatrixType* Truss::GetLocalTransformationMatrix() {
    return m_c;
}
