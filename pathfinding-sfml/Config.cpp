#include <fstream>

#include "Config.h"

Config* Config::m_instance = nullptr;
std::mutex Config::m_mutex;

Config* Config::Instance()
{
	std::lock_guard lock(m_mutex);

	if (!m_instance) m_instance = new Config();
	return m_instance;
}

Config::Config() = default;
Config::~Config() = default;

const nlohmann::json& Config::GetConfig(const std::string& path)
{
	if (!Instance()->m_configs.contains(path))
	{
		nlohmann::json data;
		std::ifstream file(path);
		file >> data;

		Instance()->m_configs[path] = data;
	}

	return Instance()->m_configs[path];
}