#include <iostream>
#include "ErrorHandlingModule.h"

namespace SAMSErrorHandling
{
	void Initialize()
	{
		std::cin.exceptions(std::cin.failbit);
	}

	int HandleNotANumberError()
	{
		std::cerr << "Input error - input may not have a number." << std::endl;
		std::cin.clear();

		char BadInput[5];
		std::cin >> BadInput;
		return 1;
	}
}