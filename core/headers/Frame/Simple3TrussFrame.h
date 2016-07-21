/*
 * =====================================================================================
 *
 *       Filename:  Simple3TrussFrame.h
 *
 *    Description:  A simple truss frame with only 3 elements
 *
 *        Version:  1.0
 *        Created:  20/07/16 13:27:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP)
 *
 * A simple 3 trusses frame
 * Truss 1 and 3 are SimpleTruss (1 param: length)
 * Truss 2 is TopCornerTruss (2 params: x and y length)
 *    2/\
 *   o   o
 * 1 |   | 3
 *   |   |
 * =====================================================================================
 */

#ifndef sso_SIMPLE3TRUSSFRAME_H
#define sso_SIMPLE3TRUSSFRAME_H

#include "TrussFrame.h"
#include "sso_exception.h"

class Simple3TrussFrame : public TrussFrame{
public: 
	Simple3TrussFrame();
	~Simple3TrussFrame();
	Simple3TrussFrame(Point* origin, const FrameParametersVectorType v, double cross_sec, Material mat_type);
private:
	void m_BuildFrame();
	static const unsigned int m_numberOfInputsParams = 3;
};

#endif
