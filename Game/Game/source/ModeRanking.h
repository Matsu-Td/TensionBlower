/**
 * @file   ModeRanking.h
 * @brief  ランキング画面
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appframe.h"

class ModeRanking : public ModeBase{
	typedef ModeBase base;

public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:
	int _cg;  // 画像
};
