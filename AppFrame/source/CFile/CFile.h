#pragma once

/**
 * @file CFile.h
 * @brief 外部ファイルの読み込み、書き込み
 *
 * @date 2020-12-18
 */

#include <string>

class CFile{
public:
	/**
	 * @brief ファイル読み込み
	 * @param fileName ファイル名
	 */
	CFile(const std::string fileName);

	/**
	 * @brief ファイル書き込み
	 * @param fileName ファイル名
	 * @param data データ格納
	 * @param size 書き込むデータサイズ
	 */
	CFile(const std::string fileName, void* data, int size);		// バイナリデータ

	~CFile();

	std::string	FileName() { return _fileName; }
	void* Data() { return _data; }
	std::string DataStr() { return std::string(_data); }
	int Size() { return _size; }
	bool Success() { return _success; }

private:
	void Init();

	std::string	_fileName;

	int	  _size;
	char* _data;
	bool  _success;
};
