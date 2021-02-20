#pragma once

/**
 * @file  ResourceServer.h
 * @brief リソース管理サーバ
 * @brief すべて静的メンバで構成する
 * 
 * @date 2020-12-18
 */

#include <unordered_map>

class ResourceServer {
public:
	static void	Init();

	/**
	 * ClearGraph()呼び出し
	 */
	static void	Release();

	/**
	 * すべてのデータ削除
	 */
	static void	ClearGraph();

	/**
	 * 画像データ読み込み
	 * @param fileName 読み込む画像データの文字列ポインタ
	 */
	static int LoadGraph(const TCHAR* fileName);

	/**
	 * 画像データ分割読み込み
	 * @param fileName 読み込む画像データの文字列ポインタ
	 * @param allNum 画像の分割総数
	 * @param xNum 画像の横向きに対する分割数
	 * @param yNum 画像の縦向きに対する分割数
	 * @param xSize 分割された画像1つの横向きの大きさ
	 * @param ySize 分割された画像1つの縦向きの大きさ
	 * @param handleBuf 読み込んだグラフィックハンドルを保存するint型配列へのポインタ
	 */
	static int LoadDivGraph(const TCHAR* fileName, int allNum,
		int xNum, int yNum, int xSize, int ySize, int* handleBuf);

	/**
	 * 音データ読み込み
	 * @param fileName 読み込む画像データの文字列ポインタ
	 */
	static int LoadSoundMem(const TCHAR* fileName);

	/**
	 * 3Dモデルデータ読み込み
     * @param fileName 読み込む画像データの文字列ポインタ
	 */
	static int MV1LoadModel(const TCHAR* fileName);

private:
	static std::unordered_map<std::string, int>	_mapGraph;         // 画像データ格納
	typedef struct {
		int		allNum;
		int*	handle;
	} DIVGRAPH;
	static std::unordered_map<std::string, DIVGRAPH> _mapDivGraph; // 分割画像データ格納

	static std::unordered_map<std::string, int>	_mapSound;   // 音データ格納
	static std::unordered_map<std::string, int>	_mapModel;   // モデルデータ格納
};

