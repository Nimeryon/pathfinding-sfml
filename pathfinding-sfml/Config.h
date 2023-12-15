#pragma once
#include <mutex>

#include "json.hpp"

class Config final
{
public:
	static Config* Instance();

	Config(Config const&) = delete;
	void operator=(Config const&) = delete;

	static const nlohmann::json& GetConfig(const std::string& path);
	template <typename T>
	static T GetConfig(const std::string& path, const std::string& category, const std::string& value)
	{
		return GetConfig(path)[category][value].get<T>();
	}

protected:
	Config();
	~Config();

private:
	static Config* m_instance;
	static std::mutex m_mutex; // For allowing multithreaded use

	std::map<std::string, nlohmann::json> m_configs;
};

