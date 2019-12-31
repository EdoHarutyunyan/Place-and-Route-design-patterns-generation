#include "Parser.h"

#include <vector>
#include <string>

using std::vector;
using std::string;

namespace parser
{

Parser::Parser(const FileManagerPtr& fileManager)
	: m_fileManager(fileManager)
	, m_tokenizer(std::make_shared<tokenizer::Tokenizer>())
{
}

void Parser::Start()
{
	if (auto fileManagerWeak = m_fileManager.lock())
	{
		vector<string> file = fileManagerWeak->ReadFromFile();

		for (auto& line : file)
		{
			vector<string> tokens = m_tokenizer->split(std::move(line));

			switch (m_operatorsMap[tokens[0]])
			{
			case Operators::And:
				break;
			case Operators::Nand:
				break;
			case Operators::Or:
				break;
			case Operators::Nor:
				break;
			case Operators::Xor:
				break;
			case Operators::Xnor:
				break;
			case Operators::Not:
				break;
			default:
				break;
			}
		}

		// TO DO
	}
}

} // namespace parser
