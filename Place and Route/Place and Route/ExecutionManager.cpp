#include "ExecutionManager.h"

namespace executionmanager
{

ExecutionManager::ExecutionManager(const std::string& path)
	: m_fileManager(std::make_shared<filemanager::FileManager>(path))
	, m_parser(std::make_shared<parser::Parser>(m_fileManager))
{
}

void ExecutionManager::Start()
{
	m_parser->Start();
}

} // namespace executionmanager