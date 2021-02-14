
/**
 * @file  ModeGameStart.h
 * @brief MISSION START文字表示
 *
 * @date 2021-02-14
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
	int _cg[2];   // 画像
	int _posX;

	static constexpr int POS_Y = 390;  // 画像描画位置：Y座標
};