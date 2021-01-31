
#include "appframe.h"

class ModeOption : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:

	int _cg;
	int _ui[4];
	int _menuPos;
};