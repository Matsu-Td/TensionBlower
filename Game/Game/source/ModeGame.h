
#include "appframe.h"
#include "Camera.h"
#include "Stage.h"
#include "Player.h"
#include "Boss.h"
#include "ModeOption.h"
#include "BulletServer.h"


class ModeGame : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	Camera _cam;
	BulletServer _bltServer;
protected:
	int mh;

	std::unique_ptr<Stage> _stg;
	std::unique_ptr<Player> _pl;
	std::unique_ptr<Boss> _bs;


}; 
