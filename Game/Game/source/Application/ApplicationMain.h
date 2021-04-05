/**
 * @file   ApplicationMain.h
 * @brief  プロジェクトのメイン処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appframe.h"

/**
 * @brief プロジェクトのメイン処理
 */
class ApplicationMain : public ApplicationBase{
	using base = ApplicationBase;

public:
	/**
	 * @brief 初期化
	 * @param hInstance WinMain第一引数
	 * @return 処理の成否
	 */
	virtual bool Initialize(HINSTANCE hInstance);

	/**
	 * @brief  解放
	 * @return 処理の成否 
	 */
	virtual bool Terminate();

	/**
	 * @brief  入力
	 * @return 処理の成否
	 */
	virtual bool Input();

	/**
	 * @brief  フレーム処理：計算
	 * @return 処理の成否
	 */
	virtual bool Process();

	/**
	 * @brief  フレーム処理：描画
	 * @return 処理の成否
	 */
	virtual bool Render();

	/**
	 * @brief  ウィンドウモード、フルスクリーンモード指定
	 * @return true
	 */
	virtual bool AppWindowed() { return true; }

	/**
	 * @brief  表示するウィンドウの横幅
	 * @return サイズ
	 */
	virtual int DispSizeW() { return 1920; }

	/**
	 * @brief  表示するウィンドウの縦幅
	 * @return サイズ
	 */
	virtual int DispSizeH() { return 1080; }

}; 
