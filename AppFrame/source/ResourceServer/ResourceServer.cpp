
/**
 * @file  ResourceServer.cpp
 * @brief リソース管理クラス
 * @brief すべて静的メンバで構成する
 *
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#include "DxLib.h"
#include "ResourceServer.h"
#include "EffekseerForDXLib.h"

// 静的メンバ実体
std::unordered_map<std::string, int> ResourceServer::_mapGraph;
std::unordered_map<std::string, ResourceServer::DIVGRAPH> ResourceServer::_mapDivGraph;
std::unordered_map<std::string, int> ResourceServer::_mapSound;
std::unordered_map<std::string, int> ResourceServer::_mapModel;
std::unordered_map<std::string, int> ResourceServer::_mapEffect;

void ResourceServer::Init(){

	_mapGraph.clear();
    _mapDivGraph.clear();
    _mapSound.clear();
    _mapModel.clear();
}

/**
 * ClearGraph()呼び出し
 */
void ResourceServer::Release(){

    ClearGraph();
}

/**
 * すべてのデータ削除
 */
void ResourceServer::ClearGraph(){

    for (auto itr = _mapGraph.begin(); itr != _mapGraph.end(); itr++){
        DeleteGraph(itr->second);
    }
    _mapGraph.clear();

    for (auto itr = _mapDivGraph.begin(); itr != _mapDivGraph.end(); itr++){
        for (int i = 0; i < itr->second.allNum; i++) {
            DeleteGraph(itr->second.handle[i]);
        }
        delete[] itr->second.handle;
    }
    _mapDivGraph.clear();

    for (auto itr = _mapSound.begin(); itr != _mapSound.end(); itr++){
        DeleteSoundMem(itr->second);
    }
    _mapSound.clear();

    for (auto itr = _mapModel.begin(); itr != _mapModel.end(); itr++){
        MV1DeleteModel(itr->second);
    }
    _mapModel.clear();

    for (auto itr = _mapEffect.begin(); itr != _mapEffect.end(); itr++) {
        DeleteEffekseerEffect(itr->second);
    }
    _mapEffect.clear();
}


int	ResourceServer::LoadGraph(const TCHAR* fileName){
    // キーの検索
    auto itr = _mapGraph.find(fileName);
    if (itr != _mapGraph.end())
    {
        // キーがあった
        return itr->second;
    }
    // キーが無かった
    int cg = ::LoadGraph(fileName);     // DxLibのAPI
    // キーとデータをmapに登録
    _mapGraph[fileName] = cg;

    return cg;
}

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

/**
 * 音データ読み込み
 */
int	ResourceServer::LoadSoundMem(const TCHAR* fileName) {
    // キーの検索
    auto itr = _mapSound.find(fileName);
    if (itr != _mapSound.end()){
        // キーがあった
        return itr->second;
    }
    // キーが無かった
    int snd = ::LoadSoundMem(fileName);     // DxLibのAPI
    // キーとデータをmapに登録
    _mapSound[fileName] = snd;

    return snd;
}

/**
 * 3Dモデルデータ読み込み
 */
int ResourceServer::MV1LoadModel(const TCHAR* fileName){
    // キーの検索
    auto itr = _mapModel.find(fileName);
    if (itr != _mapModel.end()) {
        return itr->second;
    }
    int mh = ::MV1LoadModel(fileName);  // DxLibのAPI

    _mapModel[fileName] = mh;

    return mh;
}

int ResourceServer::LoadEffekseerEffect(const char* fileName, float mag) {

    auto itr = _mapEffect.find(fileName);
    if (itr != _mapEffect.end()) {
        return itr->second;
    }
    int effect = ::LoadEffekseerEffect(fileName, mag);  // DxLibのAPI

    _mapEffect[fileName] = effect;

    return effect;
}