/*
 * =====================================================================================
 *
 *       Filename:  math_tools.h
 *
 *    Description:  mathematical toolbox setting simple functions.
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
#include "Point.h"
#include "math.h"

/*
inline float Pythagoria( const Point a, const Point b ){
	return Pythagoria(&a,&b);
}
*/
inline float Pythagoria( const Point* a, const Point *b ){
	return (float) sqrt( pow((float)(a->x-b->x),2.0) + pow((float)(a->y-b->y),2.0) + pow((float)(b->z-a->z),2.0) );
}

inline float ComputeAnglePlaneXY(Point* a, Point *b){
	return (float) atan( (b->y-a->y) / (b->x-a->x) );
}
