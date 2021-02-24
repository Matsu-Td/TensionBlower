
/**
 * @file  ModeResult.cpp
 * @brief ���U���g���
 *
 * @date 2021-02-08
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

#if 1  // ������
	int y = 0;
	int size =200;
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);
	DrawString(0, y, "���U���g���", GetColor(255, 255, 255)); y += 200;
	DrawFormatString(0, y, GetColor(255, 255, 255), "�o�ߎ���           : %d�b", gGlobal._gameTime / 1000); y += size;
	DrawFormatString(0, y, GetColor(255, 255, 255), "�c��̗�           : %d", gGlobal._remainingHP); y += size;
	DrawFormatString(0, y, GetColor(255, 255, 255), "�e���Ԃ���       : %d ��", gGlobal._totalRepelCnt); y += size;
	DrawFormatString(0, y, GetColor(255, 255, 255), "���l���G�l���M�[�� : %d", gGlobal._totalGetEnergy); y += size;
	DrawFormatString(0, y, GetColor(255, 255, 255), "���X�R�A �@�@�@�@�@: %d", _score);

#endif

	DrawGraph(0, 0, _cg, FALSE);
	return true;
}