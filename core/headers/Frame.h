/*
 * =====================================================================================
 *
 *       Filename:  Frame.h
 *
 *    Description:  A frame constituting the building
 *
 *        Version:  1.0
 *        Created:  02/06/16 12:59:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP)
 *
 * =====================================================================================
 */

#ifndef sso_FRAME_H
#define sso_FRAME_H

#include "Point.h"
#include "Types.h"

class Frame{
public:
	Frame();
	~Frame();

};

class TrussFrame : public Frame{
public:
	TrussFrame();
	~TrussFrame();
};

/*
 * The structure of the SimpleTrussFrame
 * Truss 1 and 5 are SimpleTruss (1 param: length)
 * Truss 2 and 4 are SimpleCornerTruss (3 params: 2 lengths and 1 angle)
 * Truss 3 is a TopCornerTruss (2 params: 1 length and 1 angle)
 * Total params: 2*(1+3+2)
 *    3/\
 *    o  o
 * 2 /    \ 4
 *   |    |
 *   o    o
 * 1 |    | 5
 *   |    |
 */
class Simple5TrussFrame : public TrussFrame{
	Simple5TrussFrame(Point origin, FrameParametersVectorType params );
	~Simple5TrussFrame();
private:
	Simple5TrussFrame();
	Point* m_origin;
	FrameParametersVectorType* m_truss_params;
	static const unsigned int m_number_of_inputs_params = 12;
};

#endif

