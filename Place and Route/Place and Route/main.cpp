#include <iostream>

#include "ExecutionManager.h"
#include "FileManager.h"
#include "Parser.h"

int main()
try
{
	using ExecutionManagerPtr = std::unique_ptr<executionmanager::ExecutionManager>;

	ExecutionManagerPtr executionManager = std::make_unique<executionmanager::ExecutionManager>("input.v");
	executionManager->Start();

	return 0;
}
catch (const std::exception & e)
{
	std::cout << e.what() << std::endl;
	system("pause");
}