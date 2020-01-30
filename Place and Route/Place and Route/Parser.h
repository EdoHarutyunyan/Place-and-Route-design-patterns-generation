#pragma once
#include <iostream>
#include <map>

#include "FileManager.h"
#include "Tokenizer.h"

namespace parser
{

enum class LogicGateType
{
	And = 0,
	Nand = 1,
	Or = 2,
	Nor = 3,
	Xor = 4,
	Xnor = 5,
	Not = 6
};

using LogicGatesMap = std::map<std::string /*name*/, LogicGateType /*type*/>;
using LogicGatesNamesMap = std::map<std::string /*name*/, uint8_t /*line*/>;
using FileManagerPtr = std::weak_ptr<filemanager::FileManager>;
using TokenizerPtr = std::shared_ptr<tokenizer::Tokenizer>;
using AdjacencyMatrix = std::vector<std::vector<bool>>;

class Parser
{
public:
	explicit Parser(const FileManagerPtr& fileManager);

	AdjacencyMatrix Start();
	std::vector<std::string>::iterator Check(std::vector<std::string>&& file);

	void RegisterLogicGates();

private:
	FileManagerPtr m_fileManager;
	TokenizerPtr m_tokenizer;

	LogicGatesMap m_logicGatesMap;
	LogicGatesNamesMap m_logicGatesNamesMap;
};

} // namespace parser
