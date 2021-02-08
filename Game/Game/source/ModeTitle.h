
/**
 * @file  ModeTitle.h
 * @brief タイトル画面
 *
 * @date 2021-02-08
 */

#include "appframe.h"

#include <string>

class ModeTitle : public ModeBase{
	typedef ModeBase base;

public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:
	int _cgtitle;
	std::unordered_map <std::string,int> _cg;  // UI画像

	int _menuPos;  // メニュー選択

	enum MENU {
		START,
		TUTORIAL,
		RANKING,
		OPTION,
		CREDIT,
		END,
	};
}; 
