//
// Created by plumat on 4/6/16.
//

#include "../headers/Truss.h"

Truss::Truss(Point* s_pt, Point *e_pt, double cross_sect, Truss::material mat) {

    // init the Truss
    m_start_p = s_pt;
    m_end_p = e_pt;
    m_L = sqrt(pow(m_start_p->x-m_end_p->x,2) + pow(m_start_p->y-m_end_p->y,2) + pow(m_start_p->z-m_end_p->z,2));
    m_material = mat;
    m_A = cross_sect;

    // specified the Young's modulus based on the material type
    switch (m_material){
        case BASIC:
            m_E = 1.0;
            break;
        default:
            m_E = 1.0;
            std::cerr << "Material is not supported, default value is used." <<std::endl;
            break;
    }

    // local stiffness matrix
    m_k = new StiffnessMatrixType(6,6,arma::fill::zeros); // 6x6 matrix with 0 values

    /*
     * | qxl_1 |     | 1  0  0 -1  0  0 |    | u_1 |
     * | qyl_1 |     | 0  0  0  0  0  0 |    | v_1 |
     * | qzl_1 |     | 0  0  0  0  0  0 |    | w_1 |
     * | qxl_2 | =   | -1 0  0  1  0  0 | *  | u_2 |
     * | qyl_2 |     | 0  0  0  0  0  0 |    | v_2 |
     * | qzl_2 |     | 0  0  0  0  0  0 |    | w_2 |
     */
    double coef = m_A*m_E/m_L;
    m_k->at(0,0) = coef * 1;
    m_k->at(0,3) = coef * -1;
    m_k->at(3,0) = coef * -1;
    m_k->at(3,3) = coef * 1;

    // local transformation matrix
    m_c = new TransformationMatrixType(6,6,arma::fill::zeros); // 6x6 matrix with 0 values
}

Truss::~Truss() {
    if(m_k) delete m_k;
    if(m_c) delete m_c;
    // warning: we don't deallocate the points. TODO?
}

Truss::StiffnessMatrixType* Truss::GetLocalStiffnessMatrix() {
    return m_k;
}

Truss::TransformationMatrixType* Truss::GetLocalTransformationMatrix() {
    return m_c;
}
