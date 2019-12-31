#pragma once
#include <iostream>
#include <map>

#include "FileManager.h"
#include "Tokenizer.h"

namespace parser
{ 

using FileManagerPtr = std::weak_ptr<filemanager::FileManager>;
using TokenizerPtr = std::shared_ptr<tokenizer::Tokenizer>;

class Parser final
{
public:
	explicit Parser(const FileManagerPtr& fileManager);

	void Start();

	enum class Operators
	{
		And = 0,
		Nand = 1,
		Or = 2,
		Nor = 3,
		Xor = 4,
		Xnor = 5,
		Not = 6
	};

	struct OperatorsMap : std::map<std::string, Operators>
	{
		OperatorsMap()
		{
			this->operator[]("and") = Operators::And;
			this->operator[]("nand") = Operators::Nand;
			this->operator[]("or") = Operators::Or;
			this->operator[]("nor") = Operators::Nor;
			this->operator[]("xor") = Operators::Xor;
			this->operator[]("xnor") = Operators::Xnor;
			this->operator[]("not") = Operators::Not;
		}
		~OperatorsMap() = default;
	};

private:
	FileManagerPtr m_fileManager;
	TokenizerPtr m_tokenizer;
	OperatorsMap m_operatorsMap;
};

} // namespace parser
