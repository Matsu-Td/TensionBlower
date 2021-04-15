/**
 * @file  ModeBase.h
 * @brief モード基底クラス
 *
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#pragma once

#include <string>

namespace mode {

	class ModeServer;

	/**
	 * @brief モード基底クラス
	 */
	class ModeBase {
	public:
		ModeBase();
		virtual ~ModeBase();

		/**
		 * @brief  初期化、モード管理サーバー登録時に一度だけ実行
		 * @return 処理の成否
		 */
		virtual bool Initialize();

		/**
		 * @brief  解放、モード管理サーバーから削除時に一度だけ実行
		 * @return 処理の成否
		 */
		virtual bool Terminate();

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

	public:
		/**
		 * @brief  このモードが始まってからのカウンタ取得
		 * @return カウント数
		 */
		int	GetModeCount() { return _cntMode; }

		/**
		 * @brief このモードが始まってからの時間(ms)取得
		 * @param 時間(ms)
		 */
		unsigned long GetModeTime() { return _timeMode; }

		/**
		 * @brief 前フレームからの経過時間(ms)取得
		 * @param 経過時間(ms)
		 */
		unsigned long GetStepTime() { return _timeStep; }

		/**
		 * @brief 何フレームに1回Process()を呼ぶか(デフォルト:1)
		 * @param frame フレーム数
		 */
		void SetCallPerFrame(int frame) { _callPerFrame = _callPerFrame_cnt = frame; }

		/**
		 * @brief 回の呼び出しに何回Process()を呼ぶか(デフォルト:1)
		 * @param カウント数(回数)
		 */
		void SetCallOfCount(int count) { _callOfCount = count; }

		/**
		 * @brief  何フレームに1回Process()を呼ぶか、そのフレーム数を取得
		 * @return フレーム数
		 */
		int GetCallPerFrame() { return _callPerFrame; }

		/**
		 * @brief  1回の呼び出しに何回Process()を呼ぶか、そのカウント数(回数)を取得
		 * @return カウント数(回数)
		 */
		int GetCallOfCount() { return _callOfCount; }


	private:
		friend	ModeServer;
		// ModeServer用
		std::string	_szName;
		int			_uid;
		int			_layer;

		/**
		 * @brief 時間経過処理
		 * @param timeNow 現在の時間(ms)
		 */
		void StepTime(unsigned long timeNow);

		/**
		 * @brief カウントを進める
		 */
		void StepCount();

		// モード内処理用
		int	_cntMode;	              // 本モードに入ってからのカウンタ, 0スタート
		unsigned long _timeMode;      // 本モードに入ってからの時間(ms)
		unsigned long _timeStep;      // 前フレームからの経過時間(ms)
		unsigned long _timeModeBase;  // このモードが始まった時間(ms)
		unsigned long _timePauseBase; // ポーズ中のベース時間(ms)
		unsigned long _timePauseStep; // ポーズ中の積算時間(ms) 動作中、この値を _timeMode に用いる
		unsigned long _timeOldFrame;  // 前フレームの時間(ms)

		// CallPerFrame / CallOfCount用
		int	_callPerFrame, _callPerFrame_cnt;
		int	_callOfCount;
	};
}