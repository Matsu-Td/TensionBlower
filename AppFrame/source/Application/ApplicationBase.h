
#include "dxlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Mode//ModeServer.h"
#include "EffekseerForDXLib.h"

class ApplicationBase{
public:
	ApplicationBase();
	virtual ~ApplicationBase();

	virtual bool Initialize(HINSTANCE hInstance);
	virtual bool Terminate();
	virtual bool Input();
	virtual bool Process();
	virtual bool Render();

	virtual bool AppWindowed() { return true; }
	virtual int DispSizeW() { return 640; }
	virtual int DispSizeH() { return 480; }

	static	ApplicationBase	*GetInstance() { return _pInstance; }
	virtual int GetKey() { return _gKey; }
	virtual int GetTrg() { return _gTrg; }

	bool GameEndFlag() { return _gameEnd; }
	void GameEnd() { _gameEnd = true; }

protected:
	static	ApplicationBase	*_pInstance;

	int	_gKey, _gTrg;

	ModeServer* _serverMode;

	bool _gameEnd = false;
};
