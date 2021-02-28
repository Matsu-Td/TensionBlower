/**
 * @file   ModePause.h
 * @brief  É|Å[ÉYâÊñ 
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appframe.h"

class ModePause : public ModeBase{
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