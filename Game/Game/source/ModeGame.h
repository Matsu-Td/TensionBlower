/**
 * @file   ModeGame.h
 * @brief  ゲーム本体
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appframe.h"
#include "ObjectServer.h"
#include "Camera.h"
#include "Stage.h"
#include "Player.h"
#include "Boss.h"
#include "ModePause.h"
#include "CharaData.h"
#include "PlayerStatus.h"
#include "BossStatus.h"

class ModeGame : public ModeBase{
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

	Camera       _cam;
	ObjectServer _objServer;

	std::unique_ptr<CharaData> _charaData; // JSONファイルからキャラデータ読み込み
	bool _stopObjProcess;       // オブジェクト処理をストップ

private:
	PlayerStatus _playerStatus;
	BossStatus   _bossStatus;
}; 
