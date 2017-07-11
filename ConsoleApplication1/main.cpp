#include <iostream>
#include "PromptModule.h"
#include "ErrorHandlingModule.h"

float GetDividend()
{
	float Dividend = 0;
	std::cout << "Dividend: ";
	std::cin >> Dividend;
	return Dividend;
}

float GetDivisor()
{
	float Divisor = 1;
	std::cout << "Divisor: ";
	std::cin >> Divisor;
	return Divisor;
}

float Divide(const float theDividend, const float theDivisor)
{
	return (theDividend / theDivisor);
}



int main(int argc, char* argv[])
{
	SAMSErrorHandling::Initialize();


	while (SAMSPromt::UserWantsToContinueYorN("Divide? "))
	{

		try
		{
			float Dividend = GetDividend();
			float Divisor = GetDivisor();
			std::cout << Divide(Dividend, Divisor) << std::endl;
		}
		catch (...)
		{
			SAMSErrorHandling::HandleNotANumberError();
		}
	}
	return 0;
}