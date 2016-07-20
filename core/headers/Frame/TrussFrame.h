/*
 * =====================================================================================
 *
 *       Filename:  TrussFrame.h
 *
 *    Description:  A Frame made only with Truss
 *
 *        Version:  1.0
 *        Created:  20/07/16 13:05:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP)
 *
 * =====================================================================================
 */

#ifndef sso_TRUSSFRAME_H
#define sso_TRUSSFRAME_H

#include "Frame.h"

class TrussFrame : public Frame{
public:
	TrussFrame();
	~TrussFrame();
protected:
	typedef std::vector<AbstractTruss*> TrussVector;
	TrussVector* m_trusses;
	static const unsigned int m_dof = 3;
	static const unsigned int m_nbrOfPoint = 5;
};


#endif
