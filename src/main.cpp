#include <iostream>
#include "Constants.h"
#include "Interface.h"
#include "GOLConfig.h"

int main(int argc, char** argv)
{
	std::cout << "GOL Version: " 
		<< GOL_VERSION_MAJOR << "." 
		<< GOL_VERSION_MINOR << "." 
		<< GOL_VERSION_PATCH << std::endl;

	try
	{
		Interface iface;
		iface.run();
	}
	catch (std::exception & e)
	{
		std::cerr << "Caught: " << e.what() << std::endl;
	
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
