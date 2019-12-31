#include <iostream>

#include "ExecutionManager.h"
#include "FileManager.h"
#include "Parser.h"

int main()
{
	using ExecutionManagerPtr = std::unique_ptr<executionmanager::ExecutionManager>;

	ExecutionManagerPtr executionManager = std::make_unique<executionmanager::ExecutionManager>("input.v");
	executionManager->Start();

	return 0;
}