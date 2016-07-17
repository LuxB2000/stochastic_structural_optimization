#include <iostream>


#include "sso_exception.h"
#include "easylogging++.h"

// Initialize the logger 
INITIALIZE_EASYLOGGINGPP
// WARNING: Please note that INITIALIZE_EASYLOGGINGPP should be used once and once-only otherwise you will end up getting compilation errors. This is definiting several extern variables. This means it can be defined only once per application. Best place to put this initialization statement is in file where int main(int, char**) function is defined, right after last include statement.

int main() {

	LOG(INFO) << "Starting the main program.";

	try{
		// here the main program

		//throw FatalException("An exception some where in the main program");
	
	}catch( Exception& ex){
		// catch all the exception by catching the parent type
		LOG(ERROR) << ex << std::endl;
		LOG(INFO) << "Ends the program with an exception: " << ex;
		return EXIT_FAILURE;
	}

	LOG(INFO) << "The main program end properly";
	return EXIT_SUCCESS;
}
