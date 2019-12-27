#include <iostream>
#include "Constants.h"
#include "Interface.h"

int main(size_t argc, char** argv)
{
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