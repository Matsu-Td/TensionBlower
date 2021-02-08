
/**
 * @file  ModePlugin.h
 * @brief �v���O�C�����
 *
 * @date 2021-02-08
 */

#include "appframe.h"

class ModePlugin : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:
	int _cg;   // �摜
};