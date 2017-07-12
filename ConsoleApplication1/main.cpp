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

void Tape(const char theOperator, const int theOperand)
{
	static const int myTapeChunk = 3;

	static char *myOperator = new char[myTapeChunk];
	static int *myOperand = new int[myTapeChunk];

	static int myTapeSize = myTapeChunk;
	static int myNumberOfEntries = 0;
	
	switch (theOperator)
	{
	case '?':
		for (int i = 0; i < myNumberOfEntries; i++)
		{
			std::cout << myOperator[i] << ',' << myOperand[i] << std::endl;
		}
		break;
	case '.':
		delete[] myOperator;
		delete[] myOperand;
		break;
	default:
		if (myNumberOfEntries == myTapeSize)
		{
			char *ExpandedOperator = new char[myNumberOfEntries + myTapeChunk];
			int *ExpandedOperand = new int[myNumberOfEntries + myTapeChunk];
			char *FromOperator = myOperator;
			int *FromOperand = myOperand;

			char *ToOperator = ExpandedOperator;
			int *ToOperand = ExpandedOperand;
			
			for (int i = 0; i < myNumberOfEntries; i++)
			{
				ToOperator[i] = FromOperator[i];
				ToOperand[i] = FromOperand[i];
			}

			delete[] myOperator;
			delete[] myOperand;

			myOperator = ExpandedOperator;
			myOperand = ExpandedOperand;

			myTapeSize += myTapeChunk;
		}
		myOperator[myNumberOfEntries] = theOperator;
		myOperand[myNumberOfEntries] = theOperand;
		myNumberOfEntries++;
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