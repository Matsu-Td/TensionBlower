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
#include "Sound.h"

/**
 * ������
 */
bool ModeResult::Initialize() {
	if (!base::Initialize()) { return false; }

	_cg = ResourceServer::LoadGraph("res/result.png");

	_allScore = 0;
	_timeScore = MAX_SCORE;
	_hpScore = MAX_SCORE;
	_repelScore = 0;
	_energyScore = 0;

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
		PlaySoundMem(gSound._se["decision"], DX_PLAYTYPE_BACK);
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(NEW ModeTitle(), 1, "title");
	}

	// �X�R�A�v�Z�F�o�ߎ���
	int timepoint = gGlobal._gameTime / MMSEC2SEC - 120;  // 120�ȏ㎞�Ԍo�߂ŃX�R�A���_
	if (timepoint > 0) {
		_timeScore = MAX_SCORE - timepoint * 200;
	}

	// �X�R�A�v�Z�F�c��̗�
	_hpScore = gGlobal._remainingHP * 100;

	// �X�R�A�v�Z�F���v�e����
	_repelScore = gGlobal._totalRepelCnt * 3000;

	// �X�R�A�v�Z�F���l���G�l���M�[��
	_energyScore = gGlobal._totalGetEnergy * 5;

	//// �X�R�A�v�Z�F���X�R�A
	_allScore = _timeScore + _hpScore + _repelScore + _energyScore;

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
	SetFontSize(64);
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);
	DrawFormatString(x, y, color, "%4d", gGlobal._gameTime / MMSEC2SEC); y += size;
	DrawFormatString(x, y, color, "%4d", gGlobal._remainingHP); y += size;
	DrawFormatString(x, y, color, "%4d", gGlobal._totalRepelCnt); y += size;
	DrawFormatString(x, y, color, "%4d", gGlobal._totalGetEnergy); y += size;
	SetFontSize(80);
	x = 1500;
	y = 100;
	DrawFormatString(x, y, color, "%6d", _timeScore); y += size;
	DrawFormatString(x, y, color, "%6d", _hpScore); y += size;
	DrawFormatString(x, y, color, "%6d", _repelScore); y += size;
	DrawFormatString(x, y, color, "%6d", _energyScore); y += size;
	DrawFormatString(x, y, color, "%6d", _allScore);

#endif

	return true;
}