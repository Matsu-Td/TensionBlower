#pragma once
#include "appframe.h"

class PlayerData{
public:
	PlayerData(std::string filePath, std::string fileName);
	~PlayerData();

	int _hitpoint;
	int _energy;
	int _mvSpdNorm;
	int _mvSpdChrg;

private:
	std::string StringFileLoad(std::string fileName);
	int JsonLoad(std::string filePath, std::string fileName);
};
