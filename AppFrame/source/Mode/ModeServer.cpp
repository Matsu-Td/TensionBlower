/**
 * @file  ModeServer.cpp
 * @brief モード管理クラス
 *
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#include <cstddef>
#include "DxLib.h"
#include "ModeServer.h"

ModeServer	*ModeServer::_pInstance = nullptr;

ModeServer::ModeServer(){

	_pInstance = this;
	_uid_count = 1;
	_nowMode	= nullptr;
	_skipProcessMode	= nullptr;
	_skipRenderMode		= nullptr;
	_pauseProcessMode	= nullptr;
}

ModeServer::~ModeServer(){

	Clear();
	_pInstance = nullptr;
}

/*
 * モード管理サーバーに新たなモードを追加予約する、追加実行は1フレーム後
 */
int ModeServer::Add(ModeBase *mode, int layer, const char *name ) {
	_vModeAdd.push_back(mode);		// 登録予約
	mode->_uid = _uid_count;
	_uid_count++;
	mode->_layer = layer;
	mode->_szName = name;
	return mode->_uid;
}

/*
 * 登録しているモードの削除予約をする、削除実行は1フレーム後
 */
int ModeServer::Del(ModeBase *mode) {
	_vModeDel.push_back(mode);
	return 0;
}

/*
 * 指定したモードをモードサーバーから削除、メモリ解放
 */
int ModeServer::Release(ModeBase *mode) {
	lstModeBase::iterator itr = _vMode.begin();
	for (; itr != _vMode.end(); ) {
		if ((*itr) == mode) {
			(*itr)->Terminate();
			delete (*itr);
			itr = _vMode.erase(itr);
		}
		else {
			++itr;
		}
	}
	return 1;
}

/*
 * 登録していたモードをモードサーバーから全て削除、メモリ解放
 */
void ModeServer::Clear() {
	lstModeBase::reverse_iterator itr = _vMode.rbegin();
	for (; itr != _vMode.rend(); ++itr) {
		(*itr)->Terminate();
		delete (*itr);
	}

	lstModeBase::iterator itrAdd = _vModeAdd.begin();
	for (; itrAdd != _vModeAdd.end(); ++itrAdd) {
		(*itrAdd)->Terminate();
		delete (*itrAdd);
	}
	_vMode.clear();
	_vModeAdd.clear();
	_vModeDel.clear();
}

/*
 * 指定したモードが削除予約されているか確認
 */
bool ModeServer::IsDelRegist(ModeBase *mode) {
	if (_vModeDel.size() > 0) {
		lstModeBase::iterator itrDel = _vModeDel.begin();
		for (; itrDel != _vModeDel.end(); ++itrDel) {
			if ((*itrDel) == mode) { return true; }
		}
	}
	return false;
}

/*
 * 指定したモードがリストに登録、登録予約されているか確認
 */
bool ModeServer::IsAdd(ModeBase *mode) {
	// 登録中のもの、登録予約中のものから検索する
	lstModeBase::iterator itr;
	itr = _vMode.begin();
	for (; itr != _vMode.end(); ++itr) {
		if (!IsDelRegist((*itr)) && (*itr) == mode) { return true; }
	}

	itr = _vModeAdd.begin();
	for (; itr != _vModeAdd.end(); ++itr) {
		if (!IsDelRegist((*itr)) && (*itr) == mode) { return true; }
	}
	return false;
}

/*
 * IDから指定したモードを取得
 */
ModeBase *ModeServer::Get(int uid) {
	// 登録中のもの、登録予約中のものから検索する
	lstModeBase::iterator itr;
	itr = _vMode.begin();
	for (; itr != _vMode.end(); ++itr) {
		if (!IsDelRegist((*itr)) && (*itr)->_uid == uid) { return (*itr); }
	}

	itr = _vModeAdd.begin();
	for (; itr != _vModeAdd.end(); ++itr) {
		if (!IsDelRegist((*itr)) && (*itr)->_uid == uid) { return (*itr); }
	}
	return nullptr;
}

/*
 * モードの名前から指定したモードを取得
 */
ModeBase *ModeServer::Get(const char *name) {
	// 登録中のもの、登録予約中のものから検索する
	lstModeBase::iterator itr;
	itr = _vMode.begin();
	for (; itr != _vMode.end(); ++itr) {
		if (!IsDelRegist((*itr)) && (*itr)->_szName == name) { return (*itr); }
	}

	itr = _vModeAdd.begin();
	for (; itr != _vModeAdd.end(); ++itr) {
		if (!IsDelRegist((*itr)) && (*itr)->_szName == name) { return (*itr); }
	}
	return nullptr;
}

/*
 * モードからIDを取得
 */
int ModeServer::GetId(ModeBase* mode) {
	if (IsAdd(mode)) {
		return mode->_uid;
	}
	return 0;
}

/*
 * モードの名前からIDを取得
 */
int ModeServer::GetId(const char *name) {
	return GetId(Get(name));
}

/**
 * モードの名前からIDを取得
 */
const char *ModeServer::GetName(ModeBase* mode) {
	if (IsAdd(mode)) {
		return mode->_szName.c_str();
	}

	return nullptr;
}

/**
 * モードのIDからモードの名前を取得
 */
const char *ModeServer::GetName(int uid) {
	return GetName(Get(uid));
}

// プロセスを回すための初期化
int ModeServer::ProcessInit() {
	// 削除予約されていたものを削除
	if (_vModeDel.size() > 0) {
		lstModeBase::iterator itr = _vModeDel.begin();
		for (; itr != _vModeDel.end(); ++itr) {
			Release((*itr));
		}
		_vModeDel.clear();
	}
	// Add()されたものを有効にし、必要であればソートを行う
	if (_vModeAdd.size() > 0) {
		lstModeBase::iterator itr = _vModeAdd.begin();
		for (; itr != _vModeAdd.end(); ++itr) {
			(*itr)->Initialize();
			_vMode.push_back((*itr));
		}
		_vModeAdd.clear();

		// レイヤーによるソートを行う
		_vMode.sort(modeSort);
	}

	// スキップ、ポーズの解除
	_skipProcessMode  = nullptr;
	_skipRenderMode   = nullptr;
	_pauseProcessMode = nullptr;

	return 0;
}

/**
 * レイヤーの上の方からProcessを回す
 */
int ModeServer::Process() {

	// 現在の時間を取得
	unsigned int t = GetNowCount();
	bool pause = false;

	// レイヤーの上の方から処理
	lstModeBase::reverse_iterator itr = _vMode.rbegin();
	for (; itr != _vMode.rend(); ++itr) {
		if (!IsDelRegist(*itr)) {
			_nowMode = (*itr);

			if (!pause) {
				// 時間経過処理
				(*itr)->StepTime(t);
			}

			// 各モードのProcess呼び出し
			(*itr)->Process();

			// Modeが無い場合 (再起動時)
			if (_vMode.empty()) {
				break;
			}

			if (!pause) {
				// カウンタ処理
				(*itr)->StepCount();
			}
		}
		if (_skipProcessMode == (*itr)) { break; }
		if (_pauseProcessMode == (*itr)) { pause = true; }
	}
	_nowMode = nullptr;

	return 0;
}

/**
 * プロセスを回した後の後始末 
 */
int ModeServer::ProcessFinish() {
	return 0;
}

/**
 * 描画を回すための初期化
 */
int ModeServer::RenderInit() {
	return 0;
}

/**
 * レイヤーの下の方からRenderを回す
 */
int ModeServer::Render() {
	// レイヤーの下の方から処理
	lstModeBase::iterator itr = _vMode.begin();
	for (; itr != _vMode.end(); ++itr) {
		if (_skipRenderMode && _skipRenderMode != (*itr)) { continue; }
		_skipRenderMode = nullptr;

		if (!IsDelRegist(*itr)) {
			_nowMode = (*itr);
			(*itr)->Render();
		}
	}
	_nowMode = nullptr;

	return 0;
}

/**
 * 描画を回した後の後始末
 */
int ModeServer::RenderFinish() {
	return 0;
}

/**
 * 現Processで今処理しているレイヤーより下のレイヤーは処理を呼ばない
 * @return 
 */
int ModeServer::SkipProcessUnderLayer() {
	_skipProcessMode = _nowMode;

	return 0;
}

/**
 * 現Processで今処理しているレイヤーより下のレイヤーは描画を呼ばない
 * @return 
 */
int ModeServer::SkipRenderUnderLayer() {
	_skipRenderMode = _nowMode;

	return 0;
}

/**
 * 現Processで今処理しているレイヤーより下のレイヤーの時間経過を止める
 */
int ModeServer::PauseProcessUnderLayer() {
	_pauseProcessMode = _nowMode;

	return 0;
}

