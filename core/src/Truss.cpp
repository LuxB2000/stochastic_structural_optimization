//
// Created by plumat on 4/6/16.
//

#include "../headers/Truss.h"

Truss::Truss(Point* s_pt, Point *e_pt) {
    m_start_p = s_pt;
    m_end_p = e_pt;
    m_k = new StiffnessVectorType(9,0); // 3x3 matrix with 0 values
    m_c = new TransformationVectorType(36,0); // 6x6 matrix with 0 values
}

Truss::~Truss() {
    if(m_k) delete m_k;
    if(m_c) delete m_c;
}

Truss::StiffnessVectorType* Truss::GetLocalStiffnessMatrix() {
    return m_k;
}

Truss::StiffnessVectorType* Truss::GetLocalTransformationMatrix() {
    return m_c;
}
