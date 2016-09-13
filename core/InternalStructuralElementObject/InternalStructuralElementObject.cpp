
#include "InternalStructuralElementObject.h"

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
		Material type_material)
{
		m_start = starting_pt;
		m_end = ending_pt;
    m_material = type_material;
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
		// create a connexion in PointManager
		PointManager::GetInstance().SetConnexion(m_start,m_end);
		// length
		m_L = sqrt(pow(m_start->x-m_end->x,2) + pow(m_start->y-m_end->y,2) + pow(m_start->z-m_end->z,2));
		// stfiness matrix
		m_k = StiffnessMatrixType(m_nbrOfPoints*StructuralElementType::NDOF,m_nbrOfPoints*StructuralElementType::NDOF,arma::fill::zeros);
		// local displacement vector
		m_disp_local_coord = DisplacementVectorType(m_nbrOfPoints*StructuralElementType::NDOF);
		// local forces vector
		m_f = ForceVectorType(StructuralElementType::NDOF);
}


