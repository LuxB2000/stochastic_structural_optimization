//
// Created by plumat on 20/04/16.
//

#include "../headers/StiffnessMatrixBuilder.h"


StiffnessMatrixBuilder::StiffnessMatrixBuilder() {
    /* Truss stiffness matrix
     * x, y and z axis correspond to the GLOBAL coordinate system
     * nodal forces    stiffness matrix    displacements
     * | qxl_1 |     | k00 k01 k02 k03 k04 k05 |    | u_1 |
     * | qyl_1 |     | k10 k11 k12 k13 k14 k15 |    | v_1 |
     * | qzl_1 |     | k20 k21 k22 k23 k24 k25 |    | w_1 |
     * | qxl_2 |  =  | k30 k31 k32 k33 k34 k35 |  * | u_2 |
     * | qyl_2 |     | k40 k41 k42 k43 k44 k45 |    | v_2 |
     * | qzl_2 |     | k50 k51 k52 k53 k54 k55 |    | w_2 |
     */
    m_kg_truss = new StiffnessMatrixType(6,6,arma::fill::zeros);
}

StiffnessMatrixBuilder::~StiffnessMatrixBuilder() {
    if(m_kg_truss) delete m_kg_truss;
}

void StiffnessMatrixBuilder::Build(StiffnessMatrixType* kl, TransformationMatrixType* tm) {
    /*
     * global stiffness = transformation matrix * local stiffness * transposed transformation matrix
     *
     *      | tm^t  0   |        | tm  0 |
     * kg = |           | * kl * |       |
     *      | 0    tm^t |        | 0  tm |
     */

}

const StiffnessMatrixBuilder::StiffnessMatrixType StiffnessMatrixBuilder::GetStiffnessMatrix() {
    return StiffnessMatrixType(*m_kg_truss);
}

StiffnessMatrixBuilder::StiffnessMatrixType *StiffnessMatrixBuilder::GetStiffnessMatrixPointer() {
    return m_kg_truss;
}



