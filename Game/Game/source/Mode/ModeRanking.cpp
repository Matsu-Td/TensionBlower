/**
 * @file   ModeRanking.cpp
 * @brief  �����L���O���
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "../Application/ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeRanking.h"
#include "../Sound/Sound.h"

/**
 * ������
 */
bool ModeRanking::Initialize() {
	if (!base::Initialize()) { return false; }

	_cg = ResourceServer::LoadGraph("res/ranking.png");

	return true;
}

/**
 * ���
 */
bool ModeRanking::Terminate() {
	base::Terminate();

	return true;
}

/**
 * �t���[�������F�v�Z
 */
bool ModeRanking::Process() {
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	// �Q�[���p�b�h�uA�v�{�^���Ń����L���O���[�h���폜���A�^�C�g�����[�h�ǉ�
	if (trg & PAD_INPUT_1) {
		PlaySoundMem(gSound._se["decision"], DX_PLAYTYPE_BACK);
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(NEW ModeTitle(), 1, "title");
	}

	return true;
}

/**
 * �t���[�������F�`��
 */
bool ModeRanking::Render() {
	base::Render();

	DrawGraph(0, 0, _cg, FALSE);

	return true;
}
