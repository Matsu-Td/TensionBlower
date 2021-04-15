/**
 * @file  CFile.h
 * @brief 外部ファイルへのアクセス(読み書き)
 *
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#pragma once

#include <string>

namespace cfile {

	/**
	 * @brief 外部ファイルへのアクセス(読み書き)
	 */
	class CFile {
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

		/**
		 * @brief  ファイルの名前を返す
		 * @return ファイル名
		 */
		std::string	FileName() const { return _fileName; }

		/**
		 * @brief  ファイルのデータを返す
		 * @return ファイルデータ
		 */
		void* Data() const { return _data; }

		/**
		 * @brief  ファイルデータを文字列として返す
		 * @return ファイルデータの文字列
		 */
		std::string DataStr() const { return std::string(_data); }

		/**
		 * @brief  ファイルのサイズを返す
		 * @return ファイルのサイズ
		 */
		int Size() const { return _size; }

		/**
		 * @brief  ファイルが開けたかどうか
		 * @return 成否結果_success
		 */
		bool Success() const { return _success; }

	private:
		/**
		 * @brief 初期化
		 */
		void Init();

		std::string	_fileName; // ファイル名

		int	  _size;     // ファイルのサイズ
		char* _data;     // ファイルデータを格納
		bool  _success;  // ファイルが開けたかどうか(true:ファイルを開くのに成功)
	};
}