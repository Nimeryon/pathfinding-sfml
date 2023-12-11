#pragma once
#include "json.hpp"

class Config final
{
public:
	Config(const std::string& filePath);
	~Config();

	Config(Config const&) = delete;
	void operator=(Config const&) = delete;

	nlohmann::json& GetConfig();
	template <typename T>
	T GetConfig(const std::string& category, const std::string& value)
	{
		return GetConfig()[category][value].get<T>();
	}

private:
	std::string m_filePath;
	nlohmann::json m_jsonData;
};

