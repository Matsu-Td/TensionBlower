
#include "appframe.h"

class ApplicationGlobal
{
public:
	ApplicationGlobal();
	virtual ~ApplicationGlobal();

	bool Init();

public:
	bool _gameEndFlag;
	int _gameTime;
	int _remainingHP;
	int _totalGetEnergy;
	int _totalRepelCnt;
};

// 他のソースでgGlobalを使えるように
extern ApplicationGlobal gGlobal;