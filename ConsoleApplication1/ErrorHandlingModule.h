#ifndef ErrorHandlingModuleH
#define ErrorHandlingModuleH
namespace SAMSErrorHandling
{
	void Initialize();
	int HandleNotANumberError();
	int HandleRuntimeError(std::runtime_error theRuntimeError);
}
#endif // !ErrorHandlingModuleH
