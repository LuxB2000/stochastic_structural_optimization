
//#include "InternalStructuralElementObject.h"
template class InternalStructuralElementObject<TrussType>;
template class InternalStructuralElementObject<BeamType>;


/*
 * @public
 * constructor
 */
template<class StructuralElementType>
InternalStructuralElementObject<StructuralElementType>::
InternalStructuralElementObject(
		Point* starting_pt,
		Point* ending_pt, 
		double cross_section, 
		Material type_material,
		double alpha)
{
		m_start = starting_pt;
		m_end = ending_pt;
    m_material = type_material;
		m_A = cross_section;
		m_alpha = alpha;
		this->m_init();
}

/*
 * @public
 * destructor
 */
template<class StructuralElementType>
InternalStructuralElementObject<StructuralElementType>::~InternalStructuralElementObject()
{
}

/*
 * @private
 * m_init function
 */
template<class StructuralElementType>
void
InternalStructuralElementObject<StructuralElementType>::
m_init()
{
	double EPS = 1E-8; // use to force 0 values with <EPS
	float theta = 0.0, c = 0.0, s = 0.0;
	// create a connexion in PointManager
	PointManager::GetInstance().SetConnexion(m_start,m_end);
	// length
	m_L = sqrt(pow(m_start->x-m_end->x,2) + pow(m_start->y-m_end->y,2) + pow(m_start->z-m_end->z,2));

	// Matrix and vector initializations
	// stfiness matrix
	m_k = StiffnessMatrixType(m_nbrOfPoints*StructuralElementType::NDOF,m_nbrOfPoints*StructuralElementType::NDOF,arma::fill::zeros);
	// local displacement vector
	m_disp_local_coord = DisplacementVectorType(m_nbrOfPoints*StructuralElementType::NDOF);
	// local forces vector
	m_f = ForceVectorType(StructuralElementType::NDOF);
	// transformation matrix
	m_c = TransformationMatrixType(StructuralElementType::NDOF*m_nbrOfPoints,StructuralElementType::NDOF*m_nbrOfPoints,arma::fill::zeros);

	// specified the Young's modulus based on the material type
	// TODO: move values into a const structure in Material.h
	switch (m_material){
			case BASIC:
					m_E = 1.0;
					break;
			case TEST:
					// numbers coming from "Introduction to Finite Element Analysis Using Matlab and Abacus" Amar Khennane 2013
					m_E = 2E5*1E6; // in Pa
					break;
			default:
					m_E = 1.0;
					std::cerr << "Material " << m_material << " is not supported, default value is used." <<std::endl;
					break;
	}

	// initialate the stiffness matrix
	theta= atan(sqrt(pow(m_start->y-m_end->y,2.0))/sqrt(pow(m_start->x-m_end->x,2)));
	// we are dealing with hight number, if cos or sin < EPS than we
	// set the value to 0
	c = cos( theta )<EPS ? 0 : cos(theta);
	s = sin( theta )<EPS ? 0 : sin(theta);
	if( StructuralElementType::NDOF == 3 ){
		// TRUSSTYPE element
		// stiffness matrix
		/*
		 * x, y and z axis correspond to the LOCAL coordinate system
		 * nodal forces    stiffness matrix    displacements
		 * | qxl_1 |     | 1  0  0 -1  0  0 |    | u_1 |
		 * | qyl_1 |     | 0  0  0  0  0  0 |    | v_1 |
		 * | qzl_1 |     | 0  0  0  0  0  0 |    | w_1 |
		 * | qxl_2 |  =  | -1 0  0  1  0  0 |  * | u_2 |
		 * | qyl_2 |     | 0  0  0  0  0  0 |    | v_2 |
		 * | qzl_2 |     | 0  0  0  0  0  0 |    | w_2 |
		 */
		float coef = m_A*m_E/m_L;
		m_k(0,0) = coef * 1;
		m_k(0,3) = coef * -1;
		m_k(3,0) = coef * -1;
		m_k(3,3) = coef * 1;
		// local transformation matrix
		m_c = {
				{c  ,  -s , 0.0, 0.0,  0.0, 0.0},
				{s  ,   c , 0.0, 0.0,  0.0, 0.0},
				{0.0,  0.0, 1.0, 0.0,  0.0, 0.0},
				{0.0,  0.0, 0.0, c  , -s  , 0.0},
				{0.0,  0.0, 0.0, s  ,  c  , 0.0},
				{0.0,  0.0, 0.0, 0.0,  0.0, 1.0}
		};
	}else if( StructuralElementType::NDOF == 6 ){
		// BEAMTYPE element
		// stiffness matrix
		float coef = m_E/m_L, c = 0.0, s = 0.0, J = 0.0, G = 0.0; //TODO: determine values for J and G
		m_k(0,0) = coef * m_A;
		m_k(0,6) = coef * -m_A;

		m_k(1,1) = coef * 12/pow(m_L,2);
		m_k(1,5) = coef * 6/m_L;
		m_k(1,7) = coef * -12/pow(m_L,2);
		m_k(1,11) = coef * 6/m_L;

		m_k(2,2) = coef * 12/pow(m_L,2);
		m_k(2,4) = coef * -6/m_L;
		m_k(2,8) = coef * -12/pow(m_L,2);
		m_k(2,10) = coef * -6/m_L;

		m_k(3,3) = G*J/m_L;
		m_k(3,9) = -G*J/m_L;

		m_k(4,2) = coef * -6/m_L;
		m_k(4,4) = coef * 4;
		m_k(4,8) = coef * 6/m_L;
		m_k(4,10) = coef * 2;

		m_k(5,1) = coef * 6/m_L;
		m_k(5,5) = coef * 4;
		m_k(5,7) = coef * -6/m_L;
		m_k(5,11) = coef * 2;

		m_k(6,0) = coef * -m_A;
		m_k(6,6) = coef * m_A;

		m_k(7,1) = coef * -12/pow(m_L,2);
		m_k(7,5) = coef * -6/m_L;
		m_k(7,7) = coef * 12/pow(m_L,2);
		m_k(7,11) = coef * -6/m_L;

		m_k(8,2) = coef * -12/pow(m_L,2);
		m_k(8,4) = coef * 6/m_L;
		m_k(8,8) = coef * 12/pow(m_L,2);
		m_k(8,10) = coef * 6/m_L;

		m_k(9,3) = -G*J/m_L;
		m_k(9,9) = G*J/m_L;

		m_k(10,2) = coef * -6/m_L;
		m_k(10,4) = coef * 2;
		m_k(10,8) = coef * 6/m_L;
		m_k(10,10) = coef * 4;

		m_k(11,1) = coef * 6/m_L;
		m_k(11,5) = coef * 2;
		m_k(11,7) = coef * -6/m_L;
		m_k(11,11) = coef * 4;

		// local transformation matrix
		float Cx = 0.0, Cy = 0.0, Cz = 0.0, Cxz = 0.0;

		Cx = (m_end->x - m_start->x)/m_L;
		Cy = (m_end->y - m_start->y)/m_L;
		Cz = (m_end->z - m_start->z)/m_L;
		s = sin(m_alpha);
		c = cos(m_alpha);
		Cxz = sqrt(pow(Cx,2) + pow(Cz,2));
		TransformationMatrixType R = {
			{Cx, Cy, Cz},
			{(-Cx*Cy*s-Cz*s)/Cxz, Cxz*c, (-Cy*Cz*+Cx*s)/Cxz},
			{(Cx*Cy*s -Cz*c)/Cxz, -Cxz*s,(Cx*Cz*s+Cx*c)/Cxz}
		};
		//std::cout << "R00:" << R(0,0) << " R01:" << R(0,1) << " R02:" << R(0,2) << "\n"
		//				 << "R10:" << R(1,0) <<  " R11:" << R(1,1) << " R12:" << R(1,2) << "\n"
		//				 << std::endl;
		//we are dealing with hight numbers, so everything <1E-6 will be set as 0
		m_c(0,0) = m_c(3,3) = m_c(6,6) = m_c(9,9) = R(0,0);
		m_c(1,0) = m_c(4,3) = m_c(7,6) = m_c(10,9) = R(1,0);
		m_c(1,1) = m_c(4,4) = m_c(7,7) = m_c(10,10) = R(1,1);
		m_c(1,2) = m_c(4,5) = m_c(7,8) = m_c(10,11) = R(1,2);
		m_c(2,0) = m_c(5,3) = m_c(8,6) = m_c(11,9) = R(2,0);
		m_c(2,1) = m_c(5,4) = m_c(8,7) = m_c(11,10) = R(2,1);
		m_c(2,2) = m_c(5,5) = m_c(8,8) = m_c(11,11) = R(2,2);
	} //end if

}// end of m_init

