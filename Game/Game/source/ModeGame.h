
#include "appframe.h"
#include "Camera.h"
#include "Stage.h"
#include "Player.h"
#include "Boss.h"
#include "ModeOption.h"
#include "BulletServer.h"
#include "CharaData.h"

class ModeGame : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	Camera _cam;
	ObjectServer _objServer;
	CharaData* _charaData;

protected:

	int _shadowMapHandle;
//	std::unique_ptr<Stage> _stg;
}; 
