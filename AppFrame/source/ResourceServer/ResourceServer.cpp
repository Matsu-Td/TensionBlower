
/**
 * @file  ResourceServer.cpp
 * @brief リソース管理クラス
 *
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#include "DxLib.h"
#include "ResourceServer.h"
#include "EffekseerForDXLib.h"

using namespace resource;

// 静的メンバ実体
std::unordered_map<std::string, int> ResourceServer::_mapGraph;  // 画像データ
std::unordered_map<std::string, ResourceServer::DIVGRAPH> ResourceServer::_mapDivGraph;  // 分割画像データ
std::unordered_map<std::string, int> ResourceServer::_mapSound;  // 音声データ
std::unordered_map<std::string, int> ResourceServer::_mapModel;  // モデルデータ
std::unordered_map<std::string, int> ResourceServer::_mapEffect; // エフェクトデータ

/*
 * 初期化
 */
void ResourceServer::Init(){

	_mapGraph.clear();
    _mapDivGraph.clear();
    _mapSound.clear();
    _mapModel.clear();
}

/*
 * ClearGraph()呼び出し、すべてのデータ削除
 */
void ResourceServer::Release(){

    ClearGraph();
}

/*
 * すべてのデータ削除
 */
void ResourceServer::ClearGraph(){
    // 画像データ削除
    for (auto&& itr : _mapGraph){
        DeleteGraph(itr.second);
    }
    _mapGraph.clear();

    // 分割画像データ削除
    for (auto itr : _mapDivGraph){
        for (int i = 0; i < itr.second.allNum; i++) {
            DeleteGraph(itr.second.handle[i]);
        }
        delete[] itr.second.handle;
    }
    _mapDivGraph.clear();

    // 音声データ削除
    for (auto&& itr : _mapSound){
        DeleteSoundMem(itr.second);
    }
    _mapSound.clear();

    // モデルデータ削除
    for (auto&& itr : _mapModel){
        MV1DeleteModel(itr.second);
    }
    _mapModel.clear();

    // エフェクトデータ削除
    for (auto&& itr : _mapEffect) {
        DeleteEffekseerEffect(itr.second);
    }
    _mapEffect.clear();
}

/*
 * 画像データ読み込み
 */
int	ResourceServer::LoadGraph(const TCHAR* fileName){
    // キーの検索
    auto itr = _mapGraph.find(fileName);
    if (itr != _mapGraph.end())
    {
        // キーがあったらそのキーを返す
        return itr->second;
    }
    // キーがなかった場合、データ読み込み
    int cg = ::LoadGraph(fileName);     // DxLibのAPI
    // キーとデータをmapに登録
    _mapGraph[fileName] = cg;

    return cg;
}

/*
 * 画像データ分割読み込み
 */
int	ResourceServer::LoadDivGraph(const TCHAR* fileName, int allNum,
    int xNum, int yNum,
    int xSize, int ySize, int* handleBuf)
{
    // キーの検索
    auto itr = _mapDivGraph.find(fileName);
    if (itr != _mapDivGraph.end()){
        // データをコピー
        for (int i = 0; i < itr->second.allNum; i++) {
            handleBuf[i] = itr->second.handle[i];
        }
        return 0;
    }

    int* hbuf = new int[allNum];
    int err = ::LoadDivGraph(fileName, allNum, xNum, yNum, xSize, ySize, hbuf);     // DxLibのAPI
    if (err == 0) {
        // キーとデータをmapに登録
        _mapDivGraph[fileName].allNum = allNum;
        _mapDivGraph[fileName].handle = hbuf;
        // データをコピー
        for (int i = 0; i < allNum; i++) {
            handleBuf[i] = hbuf[i];
        }
    }

    return err;
}

/*
 * 音声データ読み込み
 */
int	ResourceServer::LoadSoundMem(const TCHAR* fileName) {
    // キーの検索
    auto itr = _mapSound.find(fileName);
    if (itr != _mapSound.end()){
        // キーがあったらそのキーを返す
        return itr->second;
    }
    // キーがなかった場合、データ読み込み
    int snd = ::LoadSoundMem(fileName);     // DxLibのAPI
    // キーとデータをmapに登録
    _mapSound[fileName] = snd;

    return snd;
}

/*
 * 3Dモデルデータ読み込み
 */
int ResourceServer::MV1LoadModel(const TCHAR* fileName){
    // キーの検索
    auto itr = _mapModel.find(fileName);
    if (itr != _mapModel.end()) {
        // キーがあったらそのキーを返す
        return itr->second;
    }
    // キーがなかった場合、データ読み込み
    int mh = ::MV1LoadModel(fileName);  // DxLibのAPI
    // キーとデータをmapに登録
    _mapModel[fileName] = mh;

    return mh;
}

/*
 * エフェクトデータ読み込み 
 */
int ResourceServer::LoadEffekseerEffect(const char* fileName, float mag) {

    auto itr = _mapEffect.find(fileName);
    if (itr != _mapEffect.end()) {
        // キーがあったらそのキーを返す
        return itr->second;
    }
    // キーがなかった場合、データ読み込み
    int effect = ::LoadEffekseerEffect(fileName, mag);  // DxLibのAPI
    // キーとデータをmapに登録
    _mapEffect[fileName] = effect;

    return effect;
}