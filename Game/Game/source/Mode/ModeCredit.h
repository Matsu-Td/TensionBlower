/**
 * @file   ModeCredit.h
 * @brief  クレジットモードクラス
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appframe.h"

/**
 * クレジットモードクラス
 */
class ModeCredit : public ModeBase{
	using base = ModeBase;

public:
	/**
	 * 初期化
	 * @return 処理の成否
	 */
	bool Initialize() override;

	/**
	 * 解放
	 * @return 処理の成否
	 */
	bool Terminate() override;

	/**
	 * フレーム処理：計算
	 * @return 処理の成否
	 */
	bool Process() override;

	/**
	 * フレーム処理：描画
	 * @return 処理の成否
	 */
	bool Render() override;

private:
	int _cg;  // 画像
};
