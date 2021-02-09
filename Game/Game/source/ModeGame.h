
/**
 * @file  ModeGame.h
 * @brief ゲーム本体
 *
 * @date 2021-02-08
 */

#include "appframe.h"
#include "Camera.h"
#include "Stage.h"
#include "Player.h"
#include "Boss.h"
#include "ModeOption.h"
#include "CharaData.h"

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

protected:

	int _shadowMapHandle;


//	std::unique_ptr<Stage> _stg;
}; 
