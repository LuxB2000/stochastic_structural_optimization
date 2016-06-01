/*
 * =====================================================================================
 *
 *       Filename:  Structure.h
 *
 *    Description:  Object representing the building structure.
 *			A structure is defined a set of frames, each frame is composed of 
 *			trusses or beams. Each Structure has an origin.
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
#include "Frame.h"

class Structure{
public:
	Structure();
	Structure(Point* origin);
	~Structure();

	// setter
	void SetOrigin(Point* new_origin){ m_origin = new_origin;}

	// getter
	Point* GetOrigin(){return m_origin;}
	const unsigned int GetNumberOfFrames(){ return m_numOfFrames; }
private:
	void m_init();
	Point* m_origin;
	unsigned int m_numOfFrames;

};

#endif

