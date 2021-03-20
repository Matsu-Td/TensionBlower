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

	Camera       _cam;
	ObjectServer _objServer;

	std::unique_ptr<CharaData> _charaData; // JSONファイルからキャラデータ読み込み
	bool _stopObjProcess;       // オブジェクト処理をストップ

protected:
	PlayerStatus _playerStatus;
	BossStatus   _bossStatus;
}; 
