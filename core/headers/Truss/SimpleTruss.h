/*
 * =====================================================================================
 *
 *       Filename:  SimpleTruss.h
 *
 *    Description:  The simplest truss
 *				It is made of one AbstractTruss
 *				inputs parameters: 2 points, section and material
 *
 *        Version:  1.0
 *        Created:  03/06/16 13:45:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP)
 *
 * =====================================================================================
 */

#ifndef sso_SIMPLETRUSS_H
#define sso_SIMPLETRUSS_H

#include "AbstractTruss.h"
#include "InternalTrussObject.h"
#include "StiffnessMatrixBuilder.h"

class SimpleTruss : public AbstractTruss{
public:
	// constructor
	SimpleTruss(Point* starting_pt, Point* ending_pt, double cross_section, Material type_material);
	~SimpleTruss();
	
	// getters
	double GetLength();
	double GetCrossSection();
	double GetYoungModulus();

  //void SetNodalDisplacementInGlobalCoordinates(DisplacementVectorType disp);

private:
    Material m_material;
    Point *m_start_p, *m_end_p;

};

#endif

