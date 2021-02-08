
/**
 * @file  ModeGame.h
 * @brief ÉQÅ[ÉÄñ{ëÃ
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
#include "BossBullet.h"
#include "PlayerBullet.h"

class ModeGame : public ModeBase{
	typedef ModeBase base;

public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	Camera _cam;
	ObjectServer _objServer;
	std::unique_ptr<CharaData> _charaData;

protected:

	int _shadowMapHandle;


//	std::unique_ptr<Stage> _stg;
}; 
