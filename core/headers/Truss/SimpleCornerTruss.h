/*
 * =====================================================================================
 *
 *       Filename:  SimpleCornerTruss.h
 *
 *    Description:  A simple corner truss composed of 2 InternalTrussObject
 *
 *        Version:  1.0
 *        Created:  07/06/16 11:13:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP)
 *
 * =====================================================================================
 */

#ifndef sso_SIMPLECORNERTRUSS_H
#define sso_SIMPLECORNERTRUSS_H

#include "AbstractTruss.h"
#include "InternalTrussObject.h"
#include "StiffnessMatrixBuilder.h"

class SimpleCornerTruss : public AbstractTruss{
public:
	// constructor
	SimpleCornerTruss(Point* starting_pt, Point* middle_pt, Point* ending_pt, double cross_section, Material type_material);
	~SimpleCornerTruss();
	
	void SetDisplacementInGlobalCoordinates(DisplacementVectorType disp);

private:
    Material m_material;
    Point *m_start_p, *m_end_p, *m_mid_p;

};

#endif


