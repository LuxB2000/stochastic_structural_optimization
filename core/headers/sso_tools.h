/*
 * =====================================================================================
 *
 *       Filename:  sso_tools.h
 *
 *    Description:  A simple library setting together some simple functions
 *
 *        Version:  1.0
 *        Created:  21/07/16 11:33:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
		        ( std::ostringstream() << std::dec << x ) ).str()

