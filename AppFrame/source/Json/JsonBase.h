#pragma once
#include <string>

class JsonBase
{
public:
	JsonBase(std::string filePath, std::string tiledFileName);
	~JsonBase();

protected:
	std::string StringFileLoad(std::string filePath, std::string tiledFileName);
	int JsonLoad(std::string filePath, std::string strFileName);
};