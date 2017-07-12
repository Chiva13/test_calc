#include <iostream>
#include "PromptModule.h"
#include "ErrorHandlingModule.h"

char GetOperator();
float GetOperand();
float Divide(const float , const float);
void Tape(const char , const int);
bool TestOK(const char , const float , const float );
void SelfTest();
float Accumulator(const char , const float);

char GetOperator()
{
	char Operator;
	std::cin >> Operator;
	return Operator;
}

float GetOperand()
{
	float Operand;
	std::cin >> Operand;
	return Operand;
}


float Divide(const float theDividend, const float theDivisor)
{
	return (theDividend / theDivisor);
}

void Tape(const char theOperator, const int theOperand = 0)
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

bool TestOK(const char theOperator, const float theOperand, const float theExpectedResult)
{
	float Result = Accumulator(theOperand, theOperand);

	if (Result == theExpectedResult)
	{
		std::cout << theOperator << theOperand << " - succeeded." << std::endl;
		return true;
	}
	else
	{
		std::cout << theOperator << theOperand << " - failed." 
			<< "Excepted " << theExpectedResult << ", gor " << Result << std::endl;
		return false;
	}
}

void SelfTest()
{
	float OldValue = Accumulator('=');
	try 
	{
		if (
			TestOK('@', 0, 0) &&
			TestOK('+', 3, 3) &&
			TestOK('-', 2, 1) &&
			TestOK('*', 4, 4) &&
			TestOK('/', 2, 2)
			)
		{
			std::cout << "Test completed successfully" << std::endl;
		}
		else
		{
			std::cout << "Test failed." << std::endl;
		}
	}
	catch (...)
	{
		std::cout << "An exception occured during self test." << std::endl;
	}
	Accumulator('@', OldValue);
}

float Accumulator(const char theOperator, const float theOperand = 0)
{
	static float myAccumulator = 0;
	switch(theOperator)
	{
		case '+':
			myAccumulator = myAccumulator + theOperand;
			Tape(theOperator, theOperand);
			break;
		case '-':
			myAccumulator = myAccumulator - theOperand;
			Tape(theOperator, theOperand);
			break;
		case '*':
			myAccumulator = myAccumulator * theOperand;
			Tape(theOperator, theOperand);
			break;
		case '/':
			myAccumulator = myAccumulator / theOperand;
			Tape(theOperator, theOperand);
			break;
		case '@':
			myAccumulator = theOperand;
			Tape(theOperator, theOperand);
			break;
		case '=':
			std::cout << std::endl << myAccumulator << std::endl;
			break;
		case '?':
			Tape(theOperator);
			break;
		default:
			throw
				std::runtime_error("Error - invalid operator");
	}
	return myAccumulator;
}

int main(int argc, char* argv[])
{
	SAMSErrorHandling::Initialize();
	char Operator;
	do
	{
		try
		{
			Operator = GetOperator();
			if (Operator == '+' ||
				Operator == '-' ||
				Operator == '*' ||
				Operator == '/' ||
				Operator == '@'
				)
			{
				float Operand = GetOperand();
				Accumulator(Operator, Operand);
			}
			else if (Operator == '!')
			{
				SelfTest();
			}
			else if (Operator == '.')
			{

			}
			else
			{
				Accumulator(Operator);
			}
		}
		catch (std::runtime_error RuntimeError)
		{
			SAMSErrorHandling::HandleRuntimeError(RuntimeError);
		}
		catch (...)
		{
			SAMSErrorHandling::HandleNotANumberError();
		}
	} while (Operator != '.');
	Tape('.');
	return 0;
}