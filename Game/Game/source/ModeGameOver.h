
/**
 * @file  ModeGameOver.h
 * @brief ゲームオーバー画面
 *
 * @date 2021-02-08
 */

#include "appframe.h"

class ModeGameOver : public ModeBase{
	typedef ModeBase base;

public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:
	int	_cg;	// 画像
};
