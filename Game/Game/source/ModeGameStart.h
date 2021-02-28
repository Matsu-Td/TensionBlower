/**
 * @file   ModeGameStart.h
 * @brief  MISSION START�����\��
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appframe.h"

class ModeGameStart : public ModeBase{
	typedef ModeBase base;

public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:
	int _cg[2];   // �摜
	int _posX;

	static constexpr int POS_Y = 390;  // �摜�`��ʒu�FY���W
};