/**
 * @file  ApplicationBase.h
 * @brief アプリケーション基底クラス
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

namespace appframe {

	/**
	 * @brief アプリケーション基底クラス
	 */
	class ApplicationBase {
	public:
		ApplicationBase();
		virtual ~ApplicationBase();

		/**
		 * @brief 初期化
		 * @param hInstance WinMain関数の第一引数
		 * @return 処理の成否
		 */
		virtual bool Initialize(HINSTANCE hInstance);

		/**
		 * @brief  解放
		 * @return 処理の成否
		 */
		virtual bool Terminate();

		/**
		 * @brief  フレーム処理：入力
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
		 * @brief  ウィンドウモード、フルスクリーンモードの設定を行う
		 * @return true
		 */
		virtual bool AppWindowed() { return true; }

		/**
		 * @brief  表示するウィンドウの横幅
		 * @return サイズ
		 */
		virtual int DispSizeW() { return 640; }

		/**
		 * @brief  表示するウィンドウの縦幅
		 * @return サイズ
		 */
		virtual int DispSizeH() { return 480; }

		/**
		 * @brief  インスタンスを取得
		 * @return ApplicationBaseのインスタンス
		 */
		static	ApplicationBase* GetInstance() { return _pInstance; }

		/**
		 * @brief  キー入力情報取得
		 * @return キー入力情報
		 */
		virtual int GetKey() { return _key; }

		/**
		 * @brief  キーのトリガ情報取得
		 * @return キーのトリガ情報
		 */
		virtual int GetKeyTrg() { return _keyTrg; }

		/**
		 * @brief  DINPUTコントローラー入力情報取得
		 * @return DINPUTコントローラー入力情報
		 */
		virtual DINPUT_JOYSTATE GetDInputState() { return _dInput; }

		/**
		 * @brief  ゲーム終了フラグを返す
		 * @return ゲーム終了フラグ
		 */
		bool GameEndFlag() const { return _gameEnd; }

		/**
		 * @brief ゲーム終了フラグを立てる
		 */
		void IsGameEnd() { _gameEnd = true; }

	protected:
		static	ApplicationBase* _pInstance;

		std::unique_ptr<mode::ModeServer> _serverMode;

		int	 _key;                // キー入力情報
		int  _keyTrg;             // キー入力のトリガ情報
		DINPUT_JOYSTATE _dInput;  // DINPUTコントローラーの入力情報 
		bool _gameEnd = false;    // ゲーム終了フラグ
	};
}