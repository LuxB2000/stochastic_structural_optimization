//
// Created by plumat on 4/6/16.
//

#include "../headers/Truss.h"

Truss::Truss(Point* s_pt, Point *e_pt, double cross_sect, Truss::material mat) {

    // init the Truss
    m_start_p = new Point(*s_pt);
    m_end_p = new Point(*e_pt);
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
     * nodal forces    stiffness matrix    displacements
     * | qxl_1 |     | 1  0  0 -1  0  0 |    | u_1 |
     * | qyl_1 |     | 0  0  0  0  0  0 |    | v_1 |
     * | qzl_1 |     | 0  0  0  0  0  0 |    | w_1 |
     * | qxl_2 |  =  | -1 0  0  1  0  0 |  * | u_2 |
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
    // global system
    arma::vec x={1,0,0}, y={0,1,0}, z={0,0,1};
    // local system of the truss
    arma::vec e1 = arma::vec(3,arma::fill::zeros),
            e2 = arma::vec(3,arma::fill::zeros),
            e3 = arma::vec(3,arma::fill::zeros),
            u = arma::vec(3,arma::fill::zeros);
    double xl=0.0, yl=0.0, zl=0.0,theta_x=0.0, theta_y=0.0, theta_z=0.0, e1x=0.0, e1y=0.0, e1z=0.0;
    e1.at(0) = (m_end_p->x-m_start_p->x)/m_L;
    e1.at(1) = (m_end_p->y-m_start_p->y)/m_L;
    e1.at(2) = (m_end_p->z-m_start_p->z)/m_L;
    u.at(0) = 1; // u=(1,0,0), linearly independent of e1
    if(dot(e1,u)!=0){
        u.at(0) = 0;
        u.at(1) = 1; // u=(0,1,0)
    }
    e2 = cross(e1,u);
    e3 = cross(e1,e2);
    // fill the transformation matrix
    m_c->at(0,0) = dot(x,e1);
    m_c->at(0,1) = dot(x,e2);
    m_c->at(0,2) = dot(x,e3);
    m_c->at(1,0) = dot(y,e1);
    m_c->at(1,1) = dot(y,e2);
    m_c->at(1,2) = dot(y,e3);
    m_c->at(2,0) = dot(z,e1);
    m_c->at(2,1) = dot(z,e2);
    m_c->at(2,2) = dot(z,e3);

    m_c->at(3,3) = dot(x,e1);
    m_c->at(3,4) = dot(x,e2);
    m_c->at(3,5) = dot(x,e3);
    m_c->at(4,3) = dot(y,e1);
    m_c->at(4,4) = dot(y,e2);
    m_c->at(4,5) = dot(y,e3);
    m_c->at(5,3) = dot(z,e1);
    m_c->at(5,4) = dot(z,e2);
    m_c->at(5,5) = dot(z,e3);
}

Truss::~Truss() {
    if(m_k) delete m_k;
    if(m_c) delete m_c;
    if(m_start_p) delete m_start_p;
    if(m_end_p) delete m_end_p;
}

Truss::StiffnessMatrixType* Truss::GetLocalStiffnessMatrix() {
    return m_k;
}

Truss::TransformationMatrixType* Truss::GetLocalTransformationMatrix() {
    return m_c;
}
