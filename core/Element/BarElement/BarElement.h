/*
 * =====================================================================================
 *
 *       Filename:  BarElement.h
 *
 *    Description:  :
 *
 *        Version:  1.0
 *        Created:  21/09/16 14:44:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef SSO_BARELEMENT_H
#define SSO_BARELEMENT_H

#include "AbstractElement.h"

template<class StructuralElementType>
class BarElement: public AbstractElement<StructuralElementType>{
public:
	BarElement(Point* starting_pt, Point* ending_pt, double cross_section, Material type_material, double alpha = 0.0);
	~BarElement();
private:
    Material m_material;
    Point *m_start_p, *m_end_p;
		double m_A, m_alpha;
};

#include "BarElement.cxx"

#endif

