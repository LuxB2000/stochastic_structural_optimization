#include <iostream>


#include "easylogging++.h"

// Initialize the logger 
INITIALIZE_EASYLOGGINGPP
// WARNING: Please note that INITIALIZE_EASYLOGGINGPP should be used once and once-only otherwise you will end up getting compilation errors. This is definiting several extern variables. This means it can be defined only once per application. Best place to put this initialization statement is in file where int main(int, char**) function is defined, right after last include statement.

int main() {
	std::cout << "Hello, World!" << std::endl;

	LOG(INFO) << "Logging on the info channel";

    return 0;
}
