/**
 * @file   ModeResult.h
 * @brief  リザルト画面
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appframe.h"

class ModeResult : public ModeBase{
	typedef ModeBase base;

public:
	/**
	 * @brief  初期化
	 * @return 処理の成否
	 */
	virtual bool Initialize();

	/**
	 * @brief  解放
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

protected:
	int _cg;          // 画像
	int _timeScore;   // スコア：経過時間用
	int _hpScore;     // スコア：残りHP量用
	int _repelScore;  // スコア：総弾き回数
	int _energyScore; // スコア：総獲得エネルギー量用
	int _allScore;    // スコア：総スコア(全スコアの合計)

	static constexpr int MMSEC2SEC = 1000;      // ミリ秒⇒秒変換用
	static constexpr int MAX_SCORE = 100000;    // スコア最大値(経過時間、残りHP量用)
	static constexpr int TIME_LOWER = 120;      // 経過時間スコア計算用
};
