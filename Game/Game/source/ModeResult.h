
/**
 * @file  ModeResult.h
 * @brief ���U���g���
 *
 * @date 2021-02-08
 */

#include "appframe.h"

class ModeResult : public ModeBase{
	typedef ModeBase base;

public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:
	int _cg;     // �摜
	int _score;  // �X�R�A�l
};
