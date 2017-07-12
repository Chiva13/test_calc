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

float GetOperand()
{
	float Operand = 0;
	std::cout << "Operand: ";
	std::cin >> Operand;
	return Operand;
}

char GetOperator()
{
	char Operator = ' ';
	std::cout << "Operator: ";
	std::cin >> Operator;
	return Operator;
}

float Divide(const float theDividend, const float theDivisor)
{
	return (theDividend / theDivisor);
}

void Tape(const char theOperator, const float theOperand)
{
	static const int myTapeSize = 3;
	static char myOperator[myTapeSize];
	static float myOperand[myTapeSize];
	static int myNumberOfEntries = 0;

	if (theOperator != '?')
	{
		if (myNumberOfEntries < myTapeSize)
		{
			myOperator[myNumberOfEntries] = theOperator;
			myOperand[myNumberOfEntries] = theOperand;
			myNumberOfEntries++;
		}
		else
		{
			throw std::runtime_error("Error - Out of room on the tape.");
		}
	}
	else
	{
		for (int Index = 0; Index < myNumberOfEntries; Index++)
		{
			std::cout << myOperator[Index] << "," << myOperand[Index] << std::endl;
		}
	}
}

float Accumulate(const char theOperator, const float theOperand)
{
	static float myAccumulator = 0;
	switch(theOperator)
	{
		case '+':
			myAccumulator = myAccumulator + theOperand;
			break;
		case '-':
			myAccumulator = myAccumulator - theOperand;
			break;
		case '*':
			myAccumulator = myAccumulator * theOperand;
			break;
		case '/':
			myAccumulator = myAccumulator / theOperand;
			break;
		case '?':
			break;
		default:
			throw
				std::runtime_error("Error - invalid operator");
	}

	Tape(theOperator, theOperand);

	return myAccumulator;
}



int main(int argc, char* argv[])
{

	SAMSErrorHandling::Initialize();
	do
	{

		try
		{
			char Operator = GetOperator();
			float Operand = GetOperand();
			std::cout << Accumulate(Operator, Operand) << std::endl;
		}
		catch (std::runtime_error RuntimeError)
		{
			SAMSErrorHandling::HandleRuntimeError(RuntimeError);
		}
		catch (...)
		{
			SAMSErrorHandling::HandleNotANumberError();
		}
	} while (SAMSPromt::UserWantsToContinueYorN("More? "));
	return 0;
}