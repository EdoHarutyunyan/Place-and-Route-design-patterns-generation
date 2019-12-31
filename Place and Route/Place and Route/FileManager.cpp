#include "FileManager.h"
#include <iostream>

namespace filemanager
{

FileManager::FileManager(const std::string& path)
	: m_file(path, std::ios::in | std::ios::out)
{
	if (!m_file.is_open())
	{
		std::cerr << "FileManager::FileManager(): Problem during open " << path << " file." << std::endl;
	}
}

std::vector<std::string> FileManager::ReadFromFile()
{
	std::vector<std::string> file;
	std::string line;

	while (getline(m_file, line))
	{
		if (!line.empty())
		{
			file.push_back(line);
		}
	}

	return file;
}

void FileManager::WriteToFile(const std::vector<std::string>& lines)
{
	for (const auto& line : lines)
	{
		m_file << line << std::endl;
	}
}

} // namespace filemanager
