/*
 * =====================================================================================
 *
 *       Filename:  AbstractException.cpp
 *
 *    Description:  AbstractException definition
 *
 *        Version:  1.0
 *        Created:  16/07/16 17:29:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP), j.plumat@auckland.ac.nz
 *        Company:  UoA, Auckand, NZ
 *
 * =====================================================================================
 */

#include "AbstractException.h"

std::ostream& operator<<(std::ostream &os, const AbstractException &exc){
	os << exc.msg << "\n";
	return os;
}

AbstractException::AbstractException(const char* message){
	msg = message;
	code = 0;
}

//AbstractException::~AbstractException(){
//}
//
const char* AbstractException::what() const throw(){
	return msg;
}
