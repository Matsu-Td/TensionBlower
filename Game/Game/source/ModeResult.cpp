/**
 * @file   ModeResult.cpp
 * @brief  ���U���g���
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeResult.h"

/**
 * ������
 */
bool ModeResult::Initialize() {
	if (!base::Initialize()) { return false; }

	_cg = ResourceServer::LoadGraph("res/result.png");
	SetFontSize(64);
	_score = 0;

	return true;
}

/**
 * ���
 */
bool ModeResult::Terminate() {
	base::Terminate();

	return true;
}

/**
 * �t���[�������F�v�Z
 */
bool ModeResult::Process() {
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	// �Q�[���p�b�h�uB�v�{�^���Ń��U���g���[�h���폜���A�^�C�g�����[�h�ǉ�
	if (trg & PAD_INPUT_2) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(NEW ModeTitle(), 1, "title");
	}

	return true;
}

/**
 * �t���[�������F�`��
 */
bool ModeResult::Render() {
	base::Render();

	DrawGraph(0, 0, _cg, FALSE);

#if 1  // ������
	int x = 800;
	int y = 90;
	int size = 200;
	int color = GetColor(0, 0, 0);
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);
	DrawString(0, 0, "�X�R�A�v�Z������", GetColor(255, 255, 255)); 
	DrawFormatString(x, y, color, "%4d �b", gGlobal._gameTime / 1000); y += size;
	DrawFormatString(x, y, color, "%4d", gGlobal._remainingHP); y += size;
	DrawFormatString(x, y, color, "%4d ��", gGlobal._totalRepelCnt); y += size;
	DrawFormatString(x, y, color, "%4d", gGlobal._totalGetEnergy); y += size;
	DrawFormatString(x, y, color, "%4d", _score);

#endif

	return true;
}