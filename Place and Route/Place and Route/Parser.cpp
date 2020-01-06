#include "Parser.h"
#include "decl.h"

#include <cassert>

namespace parser
{

Parser::Parser(const FileManagerPtr& fileManager)
	: m_fileManager(fileManager)
	, m_tokenizer(std::make_shared<tokenizer::Tokenizer>())
{
	RegisterLogicGates();
}

void Parser::Start()
{
	if (auto fileManagerWeak = m_fileManager.lock())
	{
		std::vector<std::string> file = fileManagerWeak->ReadFromFile();
		
		std::vector<std::string>::iterator LogicGatesIt = Check(std::move(file));

		uint8_t index = 0u;
		for (; LogicGatesIt != file.end(); ++LogicGatesIt)
		{

			std::vector<std::string> tokens = m_tokenizer->Tokenize(std::move(*LogicGatesIt));

			if (tokens[0] == "endmodule")
			{
				break;
			}

			switch (m_logicGatesMap[tokens[0]])
			{
			case LogicGateType::And:
			case LogicGateType::Nand:
			case LogicGateType::Or:
			case LogicGateType::Nor:
			case LogicGateType::Xor:
			case LogicGateType::Xnor:
			case LogicGateType::Not:
			{
				m_logicGatesNamesMap.insert({ tokens[1], index++ });

				// tokens[2]
				// tokens[3]
				// tokens[4]
				
				break;
			}
			default:
				assert(false);
			}
		}
	}
}

std::vector<std::string>::iterator Parser::Check(std::vector<std::string>&& file)
{
	Wires wires;
	InputWires inputWires;
	OutputWires outputWires;
	InputArgs inputArgs;

	bool isFileEnd = false;
	bool isFristTime = false;

	std::vector<std::string>::iterator LogicGatesIt;

	for (auto fileIt = file.begin(); fileIt != file.end(); ++fileIt)
	{
		std::vector<std::string> tokens = m_tokenizer->Tokenize(std::move(*fileIt));

		if (tokens.empty())
		{
			continue;
		}
		if (isFileEnd)
		{
			throw std::exception("The file should end with the 'endmodule'.");
		}

		if (tokens[0] == "module")
		{
			if (!inputWires.empty() || !outputWires.empty() || !wires.empty())
			{
				throw std::exception("The file should start with the module definition.");
			}

			for (size_t i = 2; i < tokens.size(); ++i)
			{
				inputArgs.push_back(tokens[i]);
			}
		}
		else if (tokens[0] == "input")
		{
			for (size_t i = 1; i < tokens.size(); ++i)
			{
				auto it = std::find(inputArgs.begin(), inputArgs.end(), tokens[i]);
				if (it == inputArgs.end())
				{
					throw std::exception("Unknown variable.");
				}

				inputWires.push_back(tokens[i]);
			}
		}
		else if (tokens[0] == "output")
		{
			for (size_t i = 1; i < tokens.size(); ++i)
			{
				auto it = std::find(inputArgs.begin(), inputArgs.end(), tokens[i]);
				if (it == inputArgs.end())
				{
					throw std::invalid_argument("Unknown variable.");
				}

				outputWires.push_back(tokens[i]);
			}
		}
		else if (tokens[0] == "wire")
		{
			for (size_t i = 1; i < tokens.size(); ++i)
			{
				wires.push_back(tokens[i]);
			}
		}
		else if(tokens[0] == "endmodule")
		{
			isFileEnd = true;
		}
		else
		{
			if (!isFristTime)
			{
				isFristTime = true;
				LogicGatesIt = fileIt;
			}
			auto it = m_logicGatesMap.find(tokens[0]);
			if (it == m_logicGatesMap.end())
			{
				throw std::exception("Syntax error");
			}

			switch (m_logicGatesMap[tokens[0]])
			{
			case LogicGateType::And:
			case LogicGateType::Nand:
			case LogicGateType::Or:
			case LogicGateType::Nor:
			case LogicGateType::Xor:
			case LogicGateType::Xnor:
			case LogicGateType::Not:
			{
				assert(tokens.size() > 2);

				auto outIt = std::find(inputArgs.begin(), inputArgs.end(), tokens[2]);
				auto outIt2 = std::find(outputWires.begin(), outputWires.end(), tokens[2]);
				auto outIt3 = std::find(wires.begin(), wires.end(), tokens[2]);

				if (outIt == inputArgs.end() || outIt2 == outputWires.end())
				{
					if (outIt3 == wires.end())
					{
						throw std::exception("Undefined variable.");
					}
				}

				for (size_t i = 3; i < tokens.size(); ++i)
				{
					auto inpIt = std::find(inputArgs.begin(), inputArgs.end(), tokens[i]);
					auto inpIt1 = std::find(inputWires.begin(), inputWires.end(), tokens[i]);
					auto inpIt2 = std::find(outputWires.begin(), outputWires.end(), tokens[i]);
					auto inpIt3 = std::find(wires.begin(), wires.end(), tokens[i]);

					if (inpIt == inputArgs.end() || inpIt1 == inputWires.end())
					{
						if (inpIt3 == wires.end())
						{
							throw std::exception("Undefined variable.");
						}
					}
				}

				tokens.clear();
				continue;
			}
			default:
				assert(false);
			}
		}

		tokens.clear();
	}

	return LogicGatesIt;
}

void Parser::RegisterLogicGates()
{
	m_logicGatesMap = {
		{"and", LogicGateType::And},
		{"nand", LogicGateType::Nand},
		{"or", LogicGateType::Or},
		{"nor", LogicGateType::Nor},
		{"xor", LogicGateType::Xor},
		{"xnor", LogicGateType::Xnor},
		{"not", LogicGateType::Not}
	};
}

} // namespace parser
