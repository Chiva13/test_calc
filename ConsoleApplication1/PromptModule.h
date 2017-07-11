#ifndef PrompModuleH
#define PrompModuleH
namespace SAMSPromt
{
	void PauseForUserAcknowledgement();
	bool UserWantsToContinue(const char *theThingWeAreDoing);
	bool UserWantsToContinueYorN(const char *theThingWeAreDoing);
}
#endif // !PrompModuleH
