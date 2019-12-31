#include "Tokenizer.h"
#include <sstream>

namespace tokenizer
{

std::vector<std::string> Tokenizer::split(std::string&& line)
{
	std::vector<std::string> tokens;
	std::stringstream stream(line);
	std::string item;

	while (std::getline(stream, item, ' '))
	{
		if (!item.empty())
		{
			if (item.back() == ',' || item.back() == ')')
			{
				item.pop_back();
			}
			else if (item.front() == '(')
			{
				item = item.substr(1, item.size());
			}
			tokens.push_back(item);
		}
	}

	return tokens;
}

} // namespace tokenizer