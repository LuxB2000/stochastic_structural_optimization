/*
 * =====================================================================================
 *
 *       Filename:  Structure.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/06/16 11:08:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP)
 *
 * =====================================================================================
 */

#include "Structure.h"

Structure::Structure(){
	this->m_init();
}

Structure::Structure(Point origin){
	this->m_init();
	m_origin = new Point(origin);
}

Structure::~Structure(){
	if(m_origin) delete m_origin;
}

void Structure::m_init(){
	m_origin = new Point(0.0,0.0,0.0);
	m_numOfFrames = 0;
}

