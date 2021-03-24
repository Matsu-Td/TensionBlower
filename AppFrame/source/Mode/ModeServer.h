#pragma once

/**
 * @file  ModeServer.h
 * @brief モード管理クラス
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#include <list>
#include "ModeBase.h"

class ModeServer{
	using lstModeBase = std::list<ModeBase*>;

public:
	ModeServer();
	virtual	~ModeServer();
	static ModeServer * _pInstance;
	static ModeServer*GetInstance() { return (ModeServer*)_pInstance; }

	int Add(ModeBase *mode, int layer, const char *name);		// 登録はするが、一度メインを回さないといけない
	int Del(ModeBase *mode);		// 削除予約
	ModeBase *Get(int uid);
	ModeBase *Get(const char *name);
	int GetId(ModeBase* mode);
	int GetId(const char *name);
	const char *GetName(ModeBase* mode);
	const char *GetName(int uid);
	void Clear();
	int	LayerTop() { return INT32_MAX; }

	static bool modeSort(const ModeBase *x, const ModeBase *y) {
		return x->_layer < y->_layer;
	}

	/**
	 * プロセスを回すための初期化
	 */
	int ProcessInit();	

	/**
	 * レイヤーの上の方からProcessを回す
	 */
	int Process();		     

	/**
	 * プロセスを回した後の後始末
	 */
	int ProcessFinish(); 

	/**
	 * 描画を回すための初期化
	 */
	int RenderInit();

	/**
	 * レイヤーの下の方からRenderを回す
	 */
	int Render();	

	/**
	 * 描画を回した後の後始末
	 */
	int RenderFinish();

	/**
	 * 現Processで、今処理しているレイヤーより下のレイヤーの処理は呼ばない
	 */
	int SkipProcessUnderLayer();

	/**
	 * 現Processで、今処理しているレイヤーより下のレイヤーの描画は呼ばない
	 */
	int SkipRenderUnderLayer();

	/**
	 * 現Processで、今処理しているレイヤーより下のレイヤーの時間経過を止める
	 */
	int PauseProcessUnderLayer();

private:
	/**
	 * 削除、delete
	 */
	int Release(ModeBase *mode); 

	/**
	 * 削除予約されているか確認
	 */
	bool IsDelRegist(ModeBase *mode);

	/**
	 * リストに登録されているか確認
	 */
	bool IsAdd(ModeBase *mode);	

private:
	lstModeBase	_vMode;		 	// モードリスト
	int			_uid_count;		// uidカウンタ
	lstModeBase	_vModeAdd;		// 追加予約
	lstModeBase	_vModeDel;		// 削除予約

	ModeBase	*_nowMode;		    // 現在呼び出し中のモード
	ModeBase	*_skipProcessMode;	// このモードより下はProcessを呼ばない
	ModeBase	*_skipRenderMode;	// このモードより下はRenderを呼ばない
	ModeBase	*_pauseProcessMode;	// このモードより下はProcess時に時間経過をさせない

};
