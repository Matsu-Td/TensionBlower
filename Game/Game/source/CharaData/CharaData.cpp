/**
 * @file   CharaData.cpp
 * @brief  キャラデータ(プレイヤー、ボス)JSONファイル読み込み処理
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#define	_CRT_SECURE_NO_WARNINGS
//#include "picojson/picojson.h"
#include "CharaData.h"

using namespace tensionblower::charadata;

/*
 * コンストラクタで読み込むJSONファイル指定
 */
CharaData::CharaData(std::string filePath, std::string fileName){

	JsonLoad(filePath, fileName + ".json");
}

CharaData::~CharaData(){
	// 何もしない
}

/*
 * JSONファイルを開いてデータを取得
 */
std::string CharaData::StringFileLoad(std::string fileName){

	FILE* fp;
	fp = fopen(fileName.c_str(), "rb");

	if (fp == nullptr){
		// ファイルが開けなかった
		return "";
	}

	// ファイルのサイズを取得
	fseek(fp, 0, SEEK_END); int size = ftell(fp); fseek(fp, 0, SEEK_SET);

	char* p;
	p = NEW char[size + 1];
	fread(p, 1, size, fp);

	fclose(fp);
	p[size] = '\0';

	// 読み込んだデータをstringにする
	std::string s = static_cast<char*>(p);

	delete[] p;

	return s;
}

/*
 * JSONファイルのデータ読み込み
 */
int CharaData::JsonLoad(std::string filePath, std::string fileName){

	// ファイルを開いてstringを取得する
	std::string strJson = StringFileLoad(filePath + fileName);

	if (strJson == ""){
		// ファイルが開けなかった
		return 0;
	}

	// 読み込んだstringをjsonオブジェクト化する
	picojson::value json;
	picojson::parse(json, strJson);
	picojson::object jsRoot = json.get<picojson::object>();

	// プレイヤー関連データ読み込み
	picojson::object playerData = jsRoot["[0]"].get<picojson::object>();

	_maxHP     = static_cast<int>(playerData["maxHP"].get<double>());
	_maxEnergy = static_cast<int>(playerData["maxEnergy"].get<double>());
	_mvSpdNorm = static_cast<float>(playerData["mvSpdNorm"].get<double>());
	_mvSpdChrg = static_cast<float>(playerData["mvSpdChrg"].get<double>());
	_mvSpdDash = static_cast<float>(playerData["mvSpdDash"].get<double>());

	_egJump  = static_cast<int>(playerData["egJump"].get<double>());
	_egDash  = static_cast<int>(playerData["egDash"].get<double>());
	_egMLS   = static_cast<int>(playerData["egMLS"].get<double>());
	_egAtck1 = static_cast<int>(playerData["egAtck1"].get<double>());
	_egAtck2 = static_cast<int>(playerData["egAtck2"].get<double>());
	_egAtck3 = static_cast<int>(playerData["egAtck3"].get<double>());
	_egAtck4 = static_cast<int>(playerData["egAtck4"].get<double>());

	_egAutoRec   = static_cast<int>(playerData["egAutoRec"].get<double>());
	_egAutoXChrg = static_cast<int>(playerData["egAutoXChrg"].get<double>());
	_egAutoXArea = static_cast<int>(playerData["egAutoXArea"].get<double>());
	_egAvoid     = static_cast<int>(playerData["egAvoid"].get<double>());
	_egShotNum   = static_cast<int>(playerData["egShotNum"].get<double>());

	_wkDmgHP1    = static_cast<int>(playerData["wkDmgHP1"].get<double>());
	_wkDmgHP2    = static_cast<int>(playerData["wkDmgHP2"].get<double>());
	_wkDmgHP3    = static_cast<int>(playerData["wkDmgHP3"].get<double>());
	_wkDmgHP4    = static_cast<int>(playerData["wkDmgHP4"].get<double>());
	_stDmgHP1    = static_cast<int>(playerData["stDmgHP1"].get<double>());
	_stDmgHP2    = static_cast<int>(playerData["stDmgHP2"].get<double>());
	_stDmgHP3    = static_cast<int>(playerData["stDmgHP3"].get<double>());
	_stDmgHP4    = static_cast<int>(playerData["stDmgHP4"].get<double>());
	_repelDmgHP  = static_cast<int>(playerData["repelDmgHP"].get<double>());

	_wkDmgSld1   = static_cast<int>(playerData["wkDmgSld1"].get<double>());
	_wkDmgSld2   = static_cast<int>(playerData["wkDmgSld2"].get<double>());
	_wkDmgSld3   = static_cast<int>(playerData["wkDmgSld3"].get<double>());
	_wkDmgSld4   = static_cast<int>(playerData["wkDmgSld4"].get<double>());
	_stDmgSld1   = static_cast<int>(playerData["stDmgSld1"].get<double>());
	_stDmgSld2   = static_cast<int>(playerData["stDmgSld2"].get<double>());
	_stDmgSld3   = static_cast<int>(playerData["stDmgSld3"].get<double>());
	_stDmgSld4   = static_cast<int>(playerData["stDmgSld4"].get<double>());
	_repelDmgSld = static_cast<int>(playerData["repelDmgSld"].get<double>());

	_wkDmg1   = static_cast<int>(playerData["wkDmg1"].get<double>());
	_wkDmg2   = static_cast<int>(playerData["wkDmg2"].get<double>());
	_wkDmg3   = static_cast<int>(playerData["wkDmg3"].get<double>());
	_wkDmg4   = static_cast<int>(playerData["wkDmg4"].get<double>());
	_stDmg1   = static_cast<int>(playerData["stDmg1"].get<double>());
	_stDmg2   = static_cast<int>(playerData["stDmg2"].get<double>());
	_stDmg3   = static_cast<int>(playerData["stDmg3"].get<double>());
	_stDmg4   = static_cast<int>(playerData["stDmg4"].get<double>());
	_repelDmg = static_cast<int>(playerData["repelDmg"].get<double>());

	// ボス関連データ読み込み
	picojson::object bossData = jsRoot["[1]"].get<picojson::object>();

	_boss.maxHP        = static_cast<int>(bossData["maxHP"].get<double>());
	_boss.maxShield    = static_cast<int>(bossData["maxShield"].get<double>());
	_boss.shotDmg      = static_cast<int>(bossData["bsShotDmg"].get<double>());
	_boss.explosionDmg = static_cast<int>(bossData["explosionDmg"].get<double>());
	_boss.laserDmg     = static_cast<int>(bossData["laserDmg"].get<double>());

	return 1;
}