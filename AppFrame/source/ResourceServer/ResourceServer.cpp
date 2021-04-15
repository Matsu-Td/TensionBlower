
/**
 * @file  ResourceServer.cpp
 * @brief ���\�[�X�Ǘ��N���X
 *
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#include "DxLib.h"
#include "ResourceServer.h"
#include "EffekseerForDXLib.h"

using namespace resource;

// �ÓI�����o����
std::unordered_map<std::string, int> ResourceServer::_mapGraph;  // �摜�f�[�^
std::unordered_map<std::string, ResourceServer::DIVGRAPH> ResourceServer::_mapDivGraph;  // �����摜�f�[�^
std::unordered_map<std::string, int> ResourceServer::_mapSound;  // �����f�[�^
std::unordered_map<std::string, int> ResourceServer::_mapModel;  // ���f���f�[�^
std::unordered_map<std::string, int> ResourceServer::_mapEffect; // �G�t�F�N�g�f�[�^

/*
 * ������
 */
void ResourceServer::Init(){

	_mapGraph.clear();
    _mapDivGraph.clear();
    _mapSound.clear();
    _mapModel.clear();
}

/*
 * ClearGraph()�Ăяo���A���ׂẴf�[�^�폜
 */
void ResourceServer::Release(){

    ClearGraph();
}

/*
 * ���ׂẴf�[�^�폜
 */
void ResourceServer::ClearGraph(){
    // �摜�f�[�^�폜
    for (auto&& itr : _mapGraph){
        DeleteGraph(itr.second);
    }
    _mapGraph.clear();

    // �����摜�f�[�^�폜
    for (auto itr : _mapDivGraph){
        for (int i = 0; i < itr.second.allNum; i++) {
            DeleteGraph(itr.second.handle[i]);
        }
        delete[] itr.second.handle;
    }
    _mapDivGraph.clear();

    // �����f�[�^�폜
    for (auto&& itr : _mapSound){
        DeleteSoundMem(itr.second);
    }
    _mapSound.clear();

    // ���f���f�[�^�폜
    for (auto&& itr : _mapModel){
        MV1DeleteModel(itr.second);
    }
    _mapModel.clear();

    // �G�t�F�N�g�f�[�^�폜
    for (auto&& itr : _mapEffect) {
        DeleteEffekseerEffect(itr.second);
    }
    _mapEffect.clear();
}

/*
 * �摜�f�[�^�ǂݍ���
 */
int	ResourceServer::LoadGraph(const TCHAR* fileName){
    // �L�[�̌���
    auto itr = _mapGraph.find(fileName);
    if (itr != _mapGraph.end())
    {
        // �L�[���������炻�̃L�[��Ԃ�
        return itr->second;
    }
    // �L�[���Ȃ������ꍇ�A�f�[�^�ǂݍ���
    int cg = ::LoadGraph(fileName);     // DxLib��API
    // �L�[�ƃf�[�^��map�ɓo�^
    _mapGraph[fileName] = cg;

    return cg;
}

/*
 * �摜�f�[�^�����ǂݍ���
 */
int	ResourceServer::LoadDivGraph(const TCHAR* fileName, int allNum,
    int xNum, int yNum,
    int xSize, int ySize, int* handleBuf)
{
    // �L�[�̌���
    auto itr = _mapDivGraph.find(fileName);
    if (itr != _mapDivGraph.end()){
        // �f�[�^���R�s�[
        for (int i = 0; i < itr->second.allNum; i++) {
            handleBuf[i] = itr->second.handle[i];
        }
        return 0;
    }

    int* hbuf = new int[allNum];
    int err = ::LoadDivGraph(fileName, allNum, xNum, yNum, xSize, ySize, hbuf);     // DxLib��API
    if (err == 0) {
        // �L�[�ƃf�[�^��map�ɓo�^
        _mapDivGraph[fileName].allNum = allNum;
        _mapDivGraph[fileName].handle = hbuf;
        // �f�[�^���R�s�[
        for (int i = 0; i < allNum; i++) {
            handleBuf[i] = hbuf[i];
        }
    }

    return err;
}

/*
 * �����f�[�^�ǂݍ���
 */
int	ResourceServer::LoadSoundMem(const TCHAR* fileName) {
    // �L�[�̌���
    auto itr = _mapSound.find(fileName);
    if (itr != _mapSound.end()){
        // �L�[���������炻�̃L�[��Ԃ�
        return itr->second;
    }
    // �L�[���Ȃ������ꍇ�A�f�[�^�ǂݍ���
    int snd = ::LoadSoundMem(fileName);     // DxLib��API
    // �L�[�ƃf�[�^��map�ɓo�^
    _mapSound[fileName] = snd;

    return snd;
}

/*
 * 3D���f���f�[�^�ǂݍ���
 */
int ResourceServer::MV1LoadModel(const TCHAR* fileName){
    // �L�[�̌���
    auto itr = _mapModel.find(fileName);
    if (itr != _mapModel.end()) {
        // �L�[���������炻�̃L�[��Ԃ�
        return itr->second;
    }
    // �L�[���Ȃ������ꍇ�A�f�[�^�ǂݍ���
    int mh = ::MV1LoadModel(fileName);  // DxLib��API
    // �L�[�ƃf�[�^��map�ɓo�^
    _mapModel[fileName] = mh;

    return mh;
}

/*
 * �G�t�F�N�g�f�[�^�ǂݍ��� 
 */
int ResourceServer::LoadEffekseerEffect(const char* fileName, float mag) {

    auto itr = _mapEffect.find(fileName);
    if (itr != _mapEffect.end()) {
        // �L�[���������炻�̃L�[��Ԃ�
        return itr->second;
    }
    // �L�[���Ȃ������ꍇ�A�f�[�^�ǂݍ���
    int effect = ::LoadEffekseerEffect(fileName, mag);  // DxLib��API
    // �L�[�ƃf�[�^��map�ɓo�^
    _mapEffect[fileName] = effect;

    return effect;
}