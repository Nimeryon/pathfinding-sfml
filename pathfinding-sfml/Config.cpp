#include <fstream>

#include "Config.h"

Config::Config(const std::string& filePath)
{
	std::ifstream file(filePath);
	file >> m_jsonData;
}
Config::~Config() = default;

nlohmann::json& Config::GetConfig() { return m_jsonData; }