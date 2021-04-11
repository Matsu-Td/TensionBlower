/**
 * @file  CFile.cpp
 * @brief 外部ファイルへのアクセス(読み書き)
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#include <fstream>
#include <iostream>
#include "CFile.h"
#include "../Utility/UtilMacro.h"

 /*
　* ファイル読み込み
　*/
CFile::CFile(const std::string fileName) {
	// メンバの初期化
	Init();

	_fileName = fileName;

	// ファイルを開く
	std::ifstream ifs(fileName, std::ios::in | std::ios::binary);	// 入力をバイナリ形式で
	if (!ifs) {
		return;
	}

	// ファイルサイズの取得
	ifs.seekg(0, std::ios_base::end);
	_size = (int)ifs.tellg();
	ifs.seekg(0, std::ios_base::beg);

	// メモリを確保
	_data = new char[_size + 1];

	ifs.read(_data, _size);

	ifs.close();

	// 文字列として利用できるように、データの末端に \0 を付ける
	_data[_size] = '\0';

	_success = true;
}

/*
 * ファイル書き込み
 */
CFile::CFile(const std::string fileName, void* data, int size) {
	// メンバの初期化
	Init();

	_fileName = fileName;

	// ファイルを開く
	std::ofstream ofs(fileName, std::ios::out | std::ios::binary);	// 出力をバイナリ形式で
	if (!ofs) {
		return;
	}

	// データの書き込み
	ofs.write(static_cast<char*>(data), size);

	ofs.close();

	_success = true;
}

/*
 * 解放
 */
CFile::~CFile() {
	SAFE_DELETE(_data);
}

/*
 * 初期化
 */
void CFile::Init() {
	_size = 0;
	_data = nullptr;
	_fileName = "";
	_success = false;
}
