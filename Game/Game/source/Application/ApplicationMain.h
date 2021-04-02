/**
 * @file   ApplicationMain.h
 * @brief  プロジェクトのメイン処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appframe.h"

/**
 * プロジェクトのメイン処理
 */
class ApplicationMain : public ApplicationBase{
	using base = ApplicationBase;

public:
	/**
	 * 初期化
	 * @param hInstance WinMain第一引数
	 * @return 処理の成否
	 */
	virtual bool Initialize(HINSTANCE hInstance);

	/**
	 * 解放
	 * @return 処理の成否 
	 */
	virtual bool Terminate();

	/**
	 * 入力
	 * @return 処理の成否
	 */
	virtual bool Input();

	/**
	 * フレーム処理：計算
	 * @return 
	 */
	virtual bool Process();

	/**
	 * フレーム処理：描画
	 * @return 
	 */
	virtual bool Render();

	/**
	 * 
	 * @return 
	 */
	virtual bool AppWindowed() { return true; }

	/**
	 * 表示するウィンドウの横幅
	 * @return サイズ
	 */
	virtual int DispSizeW() { return 1920; }

	/**
	 * 表示するウィンドウの縦幅
	 * @return サイズ
	 */
	virtual int DispSizeH() { return 1080; }

}; 
