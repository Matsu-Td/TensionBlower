/**
 * @file   ModeGame.h
 * @brief  ゲーム本体
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appframe.h"
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
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	Camera _cam;
	ObjectServer _objServer;

	std::unique_ptr<CharaData> _charaData; // JSONファイルからキャラデータ読み込み
	bool _stopObjProcess;       // オブジェクト処理をストップ

protected:

	int _shadowMapHandle;
	PlayerStatus _playerStatus;
	BossStatus _bossStatus;
}; 
