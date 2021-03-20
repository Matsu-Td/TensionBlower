/**
 * @file   ModePause.h
 * @brief  ポーズ画面
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appframe.h"

class ModePause : public ModeBase{
	typedef ModeBase base;

public:
	/**
	 * @brief  初期化
	 * @return 処理の成功or失敗
	 */
	virtual bool Initialize();

	/**
	 * @brief  解放
	 * @return 処理の成功or失敗
	 */
	virtual bool Terminate();

	/**
	 * @brief  フレーム処理：計算
	 * @return 処理の成功or失敗
	 */
	virtual bool Process();

	/**
	 * @brief  フレーム処理：描画
	 * @return 処理の成功or失敗
	 */
	virtual bool Render();

protected:
	int _cg;      // 画像
	int _ui[4];   // UI画像
	int _menuPos; // 選択位置
};