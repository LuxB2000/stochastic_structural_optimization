//
// Created by plumat on 4/6/16.
//

#include "InternalTrussObject.h"
#include "GramSchmidtProcessTest.h"

InternalTrussObject::InternalTrussObject(Point* s_pt, Point *e_pt, double cross_sect, Material mat) {

    // init the InternalTrussObject
    m_start_p = s_pt;
    m_end_p = e_pt;
		
		//
		// create a connexion in PointManager
		PointManager::GetInstance().SetConnexion(m_start_p,m_end_p);
    
		// compute the length
		m_L = sqrt(pow(m_start_p->x-m_end_p->x,2) + pow(m_start_p->y-m_end_p->y,2) + pow(m_start_p->z-m_end_p->z,2));
    m_material = mat;
    m_A = cross_sect;

    // two points for a truss, three dimensions to move around
    m_disp_local_coord = new DisplacementVectorType(6,arma::fill::zeros);

    // truss: 3 translations possible
    m_f = new ForceVectorType(3,arma::fill::zeros);

    // specified the Young's modulus based on the material type
    switch (m_material){
        case BASIC:
            m_E = 1.0;
            break;
        case TEST:
            // numbers coming from "Introduction to Finite Element Analysis Using Matlab and Abacus" Amar Khennane 2013
            m_E = 2E5; // in MPa
            break;
        default:
            m_E = 1.0;
            std::cerr << "Material is not supported, default value is used." <<std::endl;
            break;
    }

    // local stiffness matrix
    m_k = new StiffnessMatrixType(6,6,arma::fill::zeros); // 6x6 matrix with 0 values
    /*
     * x, y and z axis correspond to the coordinate system
     * nodal forces    stiffness matrix    displacements
     * | qxl_1 |     | 1  0  0 -1  0  0 |    | u_1 |
     * | qyl_1 |     | 0  0  0  0  0  0 |    | v_1 |
     * | qzl_1 |     | 0  0  0  0  0  0 |    | w_1 |
     * | qxl_2 |  =  | -1 0  0  1  0  0 |  * | u_2 |
     * | qyl_2 |     | 0  0  0  0  0  0 |    | v_2 |
     * | qzl_2 |     | 0  0  0  0  0  0 |    | w_2 |
     */
    double coef = m_A*m_E/m_L;
    (*m_k)(0,0) = coef * 1;
    (*m_k)(0,3) = coef * -1;
    (*m_k)(3,0) = coef * -1;
    (*m_k)(3,3) = coef * 1;

    // local transformation matrix
    m_c = new TransformationMatrixType(6,6,arma::fill::zeros); // 6x6 matrix with 0 values
    // global system //TODO: ask for it to an other Object
    arma::vec x={1,0,0}, y={0,1,0}, z={0,0,1};
    // local system of the truss
    typedef GramSchmidtProcess::VectorType VectorType;
    VectorType e1 = VectorType(3,arma::fill::zeros),
            e2 = VectorType(3,arma::fill::zeros),
            e3 = VectorType(3,arma::fill::zeros),
            u  = VectorType(3,arma::fill::zeros);
    u(0) = (m_end_p->x-m_start_p->x)/m_L;
    u(1) = (m_end_p->y-m_start_p->y)/m_L;
    u(2) = (m_end_p->z-m_start_p->z)/m_L;
    //u(0) = 1; // u=(1,0,0), should be linearly independent of e1
    GramSchmidtProcess p = GramSchmidtProcess();
    p.ComputeOrthonormalBasisFromVector(&u,&e1,&e2,&e3);
            /*
    if(dot(e1,u)!=0){ // if not, take an other one
        u(0) = 0;
        u(2) = -1; // u=(0,0,-1)
    }
    e2 = cross(e1,u);
    e3 = cross(e1,e2);
             */
    // fill the transformation matrix
    // m(raw,column)
    (*m_c)(0,0) = dot(x,e1);
    (*m_c)(0,1) = dot(x,e2);
    (*m_c)(0,2) = dot(x,e3);
    (*m_c)(1,0) = dot(y,e1);
    (*m_c)(1,1) = dot(y,e2);
    (*m_c)(1,2) = dot(y,e3);
    (*m_c)(2,0) = dot(z,e1);
    (*m_c)(2,1) = dot(z,e2);
    (*m_c)(2,2) = dot(z,e3);

    (*m_c)(3,3) = dot(x,e1);
    (*m_c)(3,4) = dot(x,e2);
    (*m_c)(3,5) = dot(x,e3);
    (*m_c)(4,3) = dot(y,e1);
    (*m_c)(4,4) = dot(y,e2);
    (*m_c)(4,5) = dot(y,e3);
    (*m_c)(5,3) = dot(z,e1);
    (*m_c)(5,4) = dot(z,e2);
    (*m_c)(5,5) = dot(z,e3);
}

InternalTrussObject::~InternalTrussObject() {
		// remove the connexion
		PointManager::GetInstance().RemoveConnexion(m_start_p,m_end_p);

    if(m_k) delete m_k;
    if(m_c) delete m_c;
    if(m_disp_local_coord) delete m_disp_local_coord;
    if(m_f) delete m_f;
}

StiffnessMatrixType* InternalTrussObject::GetLocalStiffnessMatrixPointer() {
    return m_k;
}

const StiffnessMatrixType InternalTrussObject::GetLocalStiffnessMatrix() {
    return StiffnessMatrixType(*m_k);
}

TransformationMatrixType* InternalTrussObject::GetLocalTransformationMatrixPointer() {
    return m_c;
}

const TransformationMatrixType InternalTrussObject::GetLocalTransformationMatrix() {
    return TransformationMatrixType(*m_c);
}

void InternalTrussObject::SetNodalDisplacementInGlobalCoordinates(DisplacementVectorType disp_global_coord) {
    *m_disp_local_coord = m_c->t() * disp_global_coord;
    *m_f = *m_k * *m_disp_local_coord;
}




