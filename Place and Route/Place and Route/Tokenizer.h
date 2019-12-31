#pragma once

#include <vector>
#include <string>

namespace tokenizer
{

class Tokenizer
{
public:
	Tokenizer() = default;
	~Tokenizer() = default;

	std::vector<std::string> split(std::string&& line);
};

} // namespace tokenizer 
