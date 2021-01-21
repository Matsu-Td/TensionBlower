
#include "appframe.h"

class ApplicationGlobal
{
public:
	ApplicationGlobal();
	virtual ~ApplicationGlobal();

	bool Init();

public:
	int		_cgCursor;
	bool _gameEndFlag;
};

// 他のソースでgGlobalを使えるように
extern ApplicationGlobal gGlobal;