#define	_CRT_SECURE_NO_WARNINGS
#include "PlayerData.h"

#include "picojson/picojson.h"

PlayerData::PlayerData(std::string filePath, std::string fileName)
{
	JsonLoad(filePath, fileName + ".json");
}

PlayerData::~PlayerData()
{

}

std::string PlayerData::StringFileLoad(std::string fileName)
{
	FILE* fp;
	fp = fopen(fileName.c_str(), "rb");
	if (fp == NULL)
	{
		// ファイルが開けなかった
		return "";
	}
	// ファイルのサイズを取得
	fseek(fp, 0, SEEK_END); int size = ftell(fp); fseek(fp, 0, SEEK_SET);

	char* p;
	p = new char[size + 1];
	fread(p, 1, size, fp);

	fclose(fp);
	p[size] = '\0';

	// 読み込んだデータをstringにする
	std::string s = (char*)p;

	delete[] p;

	return s;
}

int PlayerData::JsonLoad(std::string filePath, std::string fileName)
{
	// ファイルを開いてstringを取得する
	std::string strJson = StringFileLoad(filePath + fileName);
	if (strJson == "")
	{
		// ファイルが開けなかった
		return 0;
	}

	// 読み込んだstringをjsonオブジェクト化する
	picojson::value json;
	picojson::parse(json, strJson);
	picojson::object jsRoot = json.get<picojson::object>();

	picojson::object data = jsRoot["[0]"].get<picojson::object>();
	_hitpoint = static_cast<int>(data["hitpoint"].get<double>());
	
//	hitpoint = (int)jsRoot["height"].get<double>();
	return 1;
}