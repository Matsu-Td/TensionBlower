
/**
 * @file  ModeRanking.cpp
 * @brief �����L���O���
 *
 * @date 2021-02-08
 */

#include "ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeRanking.h"

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
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
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
