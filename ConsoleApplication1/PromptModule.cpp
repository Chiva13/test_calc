#include <iostream>
#include "PromptModule.h"

namespace SAMSPromt
{
	void PauseForUserAcknowledgement()
	{
		char StopCharacter;
		std::cout << std::endl << "Press a key and \"Enter\" ";
		std::cin >> StopCharacter;
	}

	bool UserWantsToContinue(const char *theThingWeAreDoing)
	{
		char DoneCharacter;
		std::cout << std::endl << theThingWeAreDoing << " - Press \"n\" and \"Enter\" to stop: ";
		std::cin >> DoneCharacter;
		return (DoneCharacter != 'n');
	}

	bool UserWantsToContinueYorN(const char *theThingWeAreDoing)
	{
		char DoneCharacter;
		bool InvalidCharacterWasEntered = false;
		do
		{
			std::cout << std::endl << theThingWeAreDoing << " - Press \"n\" and \"Enter\" to stop: ";
			std::cin >> DoneCharacter;
			InvalidCharacterWasEntered = !((DoneCharacter == 'y') || (DoneCharacter == 'n'));
			if (InvalidCharacterWasEntered)
			{
				std::cout << "...Error - " << "please enter \"y\" or \"n\"." << std::endl;
			}
		} 
		while (InvalidCharacterWasEntered);
		return (DoneCharacter != 'n');
	}

}