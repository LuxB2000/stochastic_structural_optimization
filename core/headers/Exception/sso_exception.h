/*
 * =====================================================================================
 *
 *       Filename:  WarningException.h
 *
 *    Description:  WarningException should be use to inform without 
 *
 *        Version:  1.0
 *        Created:  17/07/16 11:49:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP), j.plumat@auckland.ac.nz
 *        Company:  UoA, Auckand, NZ
 *
 * =====================================================================================
 */

#ifndef sso_WARNINGEXCEPTION_H_
#define sso_WARNINGEXCEPTION_H_

#include "AbstractException.h"

class Exception : public AbstractException{
public:
	Exception(const char* message) : AbstractException(message) {
	}
};

class FatalException : public Exception{
public:
	FatalException(const char* message) : Exception(message){}
};

class WrongNumberOfParametersException : public Exception{
	public:
		WrongNumberOfParametersException(const char* msg) : Exception( msg ){
		}
};
#endif

