/**
 * @file  ResourceServer.h
 * @brief リソース管理クラス
 *
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#pragma once

#include <unordered_map>

/**
 * @brief リソース管理クラス
 */
class ResourceServer {
public:
	/**
	 * @brief 初期化
	 */
	static void	Init();

	/**
	 * @brief ClearGraph()呼び出し、すべてのデータ削除
	 */
	static void	Release();

	/**
	 * @brief すべてのデータ削除
	 */
	static void	ClearGraph();

	/**
	 * @brief 画像データ読み込み
	 * @param fileName 読み込む画像データの文字列ポインタ
	 * @return 画像のハンドル
	 */
	static int LoadGraph(const TCHAR* fileName);

	/**
	 * @brief 画像データ分割読み込み
	 * @param fileName 読み込む画像データの文字列ポインタ
	 * @param allNum 画像の分割総数
	 * @param xNum 画像の横向きに対する分割数
	 * @param yNum 画像の縦向きに対する分割数
	 * @param xSize 分割された画像1つの横向きの大きさ
	 * @param ySize 分割された画像1つの縦向きの大きさ
	 * @param handleBuf 読み込んだグラフィックハンドルを保存するint型配列へのポインタ
	 * @return 画像のハンドル
	 */
	static int LoadDivGraph(const TCHAR* fileName, int allNum,
	int xNum, int yNum, int xSize, int ySize, int* handleBuf);

	/**
	 * @brief 音声データ読み込み
	 * @param fileName 読み込むデータの文字列ポインタ
	 * @return 音声データのハンドル
	 */
	static int LoadSoundMem(const TCHAR* fileName);

	/**
	 * @brief 3Dモデルデータ読み込み
     * @param fileName 読み込むデータの文字列ポインタ
     * @return モデルのハンドル
	 */
	static int MV1LoadModel(const TCHAR* fileName);

	/**
	 * @brief エフェクトデータ読み込み
	 * @param  fileName  読み込むデータの文字列ポインタ
	 * @param  mag　エフェクトの拡大率
	 * @return エフェクトのハンドル
	 */
	static int LoadEffekseerEffect(const char* fileName, float mag);

private:
	static std::unordered_map<std::string, int>	_mapGraph;         // 画像データ格納

	struct DIVGRAPH {
		int		allNum;
		int*	handle;
	};
	static std::unordered_map<std::string, DIVGRAPH> _mapDivGraph; // 分割画像データ格納

	static std::unordered_map<std::string, int>	_mapSound;   // 音声データ格納
	static std::unordered_map<std::string, int>	_mapModel;   // モデルデータ格納
	static std::unordered_map<std::string, int>	_mapEffect;  // エフェクトデータ格納
};

