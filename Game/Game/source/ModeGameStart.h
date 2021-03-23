/**
 * @file   ModeGameStart.h
 * @brief  MISSION START文字表示
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appframe.h"

class ModeGameStart : public ModeBase{
	using base = ModeBase;

public:
	/**
	 * @brief  初期化
	 * @return 処理の成否
	 */
	bool Initialize() override;

	/**
	 * @brief  解放
	 * @return 処理の成否
	 */
	bool Terminate() override;

	/**
	 * @brief  フレーム処理：計算
	 * @return 処理の成否
	 */
	bool Process() override;

	/**
	 * @brief  フレーム処理：描画
	 * @return 処理の成否
	 */
	bool Render() override;

protected:
	int _cg[2];   // 画像

	static constexpr int POS_Y = 390;  // 画像描画位置：Y座標
};