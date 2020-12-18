#pragma once
#include <string>

class JsonBase
{
public:
	JsonBase(std::string filePath, std::string tiledFileName);
	~JsonBase();

protected:
	std::string StringFileLoad();
};