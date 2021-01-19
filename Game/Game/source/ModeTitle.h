
#include "appframe.h"

#include <string>

class ModeTitle : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:
	int _cgtitle;
	std::unordered_map <std::string,int> _cg;

	int _menuPos;

	enum MENU {
		START,
		TUTORIAL,
		RANKING,
		OPTION,
		CREDIT,
		END,
	};
}; 
