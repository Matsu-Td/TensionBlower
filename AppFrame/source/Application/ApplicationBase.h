
/**
 * @file  ApplicationBase.h
 * @brief アプリケーションベース
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#include "dxlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Mode//ModeServer.h"
#include "EffekseerForDXLib.h"

class ApplicationBase{
public:
	ApplicationBase();
	virtual ~ApplicationBase();

	virtual bool Initialize(HINSTANCE hInstance);
	virtual bool Terminate();
	virtual bool Input();
	virtual bool Process();
	virtual bool Render();

	virtual bool AppWindowed() { return true; }

	/**
	 * @brief  ウィンドウ横向きサイズ指定
	 * @return サイズ
	 */
	virtual int DispSizeW() { return 640; }

	/**
	 * @brief  ウィンドウ縦向きサイズ指定
	 * @return サイズ
	 */
	virtual int DispSizeH() { return 480; }

	static	ApplicationBase	*GetInstance() { return _pInstance; }

	/**
	 * @brief  キー入力情報取得
	 * @return キー入力情報
	 */
	virtual int GetKey() { return _gKey; }

	/**
	 * @brief  キーのトリガ情報取得
	 * @return キーのトリガ情報
	 */
	virtual int GetTrg() { return _gTrg; }

	/**
	 * @brief ゲーム終了フラグ.
	 * @return _gameEnd ゲーム終了フラグ
	 */
	bool GameEndFlag() { return _gameEnd; }

	/**
	 * @brief ゲーム終了フラグを立てる
	 */
	void GameEnd() { _gameEnd = true; }

protected:
	static	ApplicationBase	*_pInstance;

	std::unique_ptr<ModeServer> _serverMode;

	int	 _gKey;              // キー入力の情報
	int  _gTrg;              // キー入力のトリガ情報
	bool _gameEnd = false;   // ゲーム終了フラグ
};
