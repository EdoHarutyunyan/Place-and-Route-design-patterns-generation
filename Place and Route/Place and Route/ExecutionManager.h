#pragma once

#include "FileManager.h"
#include "Parser.h"

namespace executionmanager
{

using FileManagerPtr = std::shared_ptr<filemanager::FileManager>;
using ParserPtr = std::shared_ptr<parser::Parser>;
using AdjacencyMatrix = std::vector<std::vector<bool>>;

class ExecutionManager
{
public:
	explicit ExecutionManager(const std::string& path);

	void Start();
private:
	FileManagerPtr m_fileManager;
	ParserPtr m_parser;
	AdjacencyMatrix m_adjacencyMatrix;
};

} // namespace executionmanager
