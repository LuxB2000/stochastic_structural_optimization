/*
 * =====================================================================================
 *
 *       Filename:  AbstractException.h
 *
 *    Description:  Main Exception definition
 *
 *        Version:  1.0
 *        Created:  16/07/16 17:25:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP), j.plumat@auckland.ac.nz
 *        Company:  UoA, Auckand, NZ
 *
 * =====================================================================================
 */

#include <iostream>
#include <exception>

#ifndef sso_ABSTRACTEXCEPTION_H_
#define sso_ABSTRACTEXCEPTION_H_

class AbstractException: public std::exception{

public:
	AbstractException(const char* message);
	AbstractException(const char* message, int code);
	//virtual const char* Print(){};
	virtual const char* what() const throw();
	friend std::ostream& operator<<(std::ostream&, const AbstractException &p);

	// public information
	const char* msg;
	int code;

private:
	
};

#endif
