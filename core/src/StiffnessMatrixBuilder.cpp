//
// Created by plumat on 20/04/16.
//

#include "../headers/StiffnessMatrixBuilder.h"


StiffnessMatrixBuilder::StiffnessMatrixBuilder(int nbr_dof) {
    /* Truss stiffness matrix
     * U, V and W correspond to degree of freedom (translations) in the GLOBAL coordinate system
     *                      U_1 V_1 W_1 .... W_nbf_dof
     *         U_1       |                              |
     *         V_1       |                              |
     *         W_1       |                              |
     * kg =    ...       |                              |
     *         U_nbf_dof |                              |
     *         V_nbf_dof |                              |
     *         W_nbf_dof |                              |
     */
    m_kg_truss = new StiffnessMatrixType();
    m_kg_truss->set_size(nbr_dof,nbr_dof);
    m_kg_truss->fill(arma::fill::zeros);
}

StiffnessMatrixBuilder::~StiffnessMatrixBuilder() {
    if(m_kg_truss) delete m_kg_truss;
}

void StiffnessMatrixBuilder::Build(StiffnessMatrixType* kl, TransformationMatrixType* tm, unsigned int j1, unsigned int j2) {
    /*
     * The stiffness matrix in the global coordinates
     * global stiffness = transformation matrix * local stiffness * transposed transformation matrix
     * kg = tm^t * kl * tm = 6x6 in Truss
     */

    StiffnessMatrixType kg = (*tm) * (*kl) * (*tm).t();
		m_build(&kg,j1,j2);

}

void StiffnessMatrixBuilder::Build(StiffnessMatrixType* kg, JointIdType jointId1, JointIdType jointId2){
		m_build(kg,jointId1,jointId2);
}

const StiffnessMatrixType StiffnessMatrixBuilder::GetStiffnessMatrix() {
    return StiffnessMatrixType(*m_kg_truss);
}

StiffnessMatrixType *StiffnessMatrixBuilder::GetStiffnessMatrixPointer() {
    return m_kg_truss;
}

void StiffnessMatrixBuilder::m_build(StiffnessMatrixType* kg, 
		unsigned int j1, unsigned int j2){

		unsigned int c=0,r=0,k=0,j=0,l1=j1*3,l2=j2*3; // mult by 3 since 3 dof in truss

    for(c=0;c<6;c++)
    for(r=0;r<6;r++)
    {
        if(c<3 && r<3){
            (*m_kg_truss)(l1+r,l1+c) = (*m_kg_truss)(l1+r,l1+c) + (*kg)(r,c);
        }
        else if(c>=3 && r<3){
            (*m_kg_truss)(l1+r,l2+c-3) = (*m_kg_truss)(l1+r,l2+c-3) + (*kg)(r,c);
        }
        else if(c>=3 && r>=3){
            (*m_kg_truss)(l2+r-3,l2+c-3) = (*m_kg_truss)(l2+r-3,l2+c-3) + (*kg)(r,c);
        }
        else if(c<3 && r>=3){
        (*m_kg_truss)(l2+r-3,l1+c) = (*m_kg_truss)(l2+r-3,l1+c) + (*kg)(r,c);
        }
    }

}

void StiffnessMatrixBuilder::Build(
		StiffnessMatrixType* kg, 
		StiffnessMatrixBuilder::JointIdVectorType jointIdList){

	// be sure we the ids are ordered
	std::sort( jointIdList.begin(), jointIdList.end() );

	// construct the new stiffness matrix
	unsigned int c=0, r=0, nbrDOF=3,
							 nc1=kg->n_cols, nr1=kg->n_rows;
	int cc = -1, cr = -1, mc = 0, mr = 0;
	bool found = true;

	for( r=0; r<nr1; r++ ){
		mr = (r % nbrDOF);
		if( mr == 0 ) cr ++;
		cc = -1;
		for( c=0; c<nc1; c++ ){
			mc = (c % nbrDOF);
			if( mc == 0 ) cc ++;
			(*m_kg_truss)(jointIdList[cr]*nbrDOF+mr, jointIdList[cc]*nbrDOF+mc) =
				(*m_kg_truss)(jointIdList[cr]*nbrDOF+mr, jointIdList[cc]*nbrDOF+mc)+
				(*kg)(r,c);
		}
	}

}//end Build function
