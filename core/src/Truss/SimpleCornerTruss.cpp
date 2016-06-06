/*
 * =====================================================================================
 *
 *       Filename:  SimpleCornerTruss.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/06/16 11:20:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP), j.plumat@auckland.ac.nz
 *        Company:  UoA, Auckand, NZ
 *
 * =====================================================================================
 */

#include "SimpleCornerTruss.h"

SimpleCornerTruss::SimpleCornerTruss(Point* starting_pt, Point* middle_pt, Point* ending_pt, double cross_section, Material type_material){

}

SimpleCornerTruss::~SimpleCornerTruss(){
	if( m_start_p ) delete m_start_p;
	if( m_end_p ) delete m_end_p;
	if( m_mid_p ) delete m_mid_p;
}

void SimpleCornerTruss::SetDisplacementInGlobalCoordinates(
		DisplacementVectorType disp){
	// TODO
}
