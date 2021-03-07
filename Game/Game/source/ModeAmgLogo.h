/**
 * @file   ModeAmgLogo.h
 * @brief  AMG���S�\��
 * 
 * @author matsuo tadahiko
 * @date   2021/03/07
 */

#pragma once
#include "appframe.h"

class ModeAmgLogo :public ModeBase {
	typedef ModeBase base;

public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:
	int _bg;      // �w�i
	int _cg;      // �摜
	int _mode;    // �t�F�[�h���䃂�[�h
	int _fadeCnt; // �t�F�[�h�J�E���g 
	int _dispCnt; // �\���J�E���g
	int _alpha;   // �摜�̃��l

	static constexpr int MAX_ALPHA = 255;
	static constexpr int MAX_FADE_CNT = 30;
	static constexpr int MAX_DISP_CNT = 90;
	static constexpr int LOGO_POS_X = 460;
	static constexpr int LOGO_POS_Y = 425;
};