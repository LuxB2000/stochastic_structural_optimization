/*
 * =====================================================================================
 *
 *       Filename:  Structure.h
 *
 *    Description:  Object representing the building structure
 *			A structure is defined a set of Frame, each frame is composed of 
 *			trusses or beams. Each Structure has an origin
 *
 *        Version:  1.0
 *        Created:  02/06/16 11:04:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP), j.plumat@gmail.com
 *
 * =====================================================================================
 */

#ifndef sso_STRUCTURE_H
#define sso_STRUCTURE_H

#include "Point.h"

class Structure{
public:
	Structure();
	~Structure();

private:
	Point* m_origine;

};

#endif

