/**
 * @file   ModeGameOver.cpp
 * @brief  �Q�[���I�[�o�[���[�h�N���X
 * 
 * @author matsuo tadahiko
 * @date   2021/01/14
 */

#include "../Application/ApplicationMain.h"
#include "../Application/ApplicationGlobal.h"
#include "ModeGame.h"
#include "ModeGameOver.h"
#include "ModeTitle.h"
#include "../Sound/Sound.h"
#include "../Player/LoadPlayerVoice.h"

using namespace tensionblower::mode;

/*
 * ������
 */
bool ModeGameOver::Initialize() {
	if (!base::Initialize()) { return false; }

	// �{�X�X�e�[�W��BGM�Đ���~
	StopSoundMem(gSound._bgm["boss"]);
	// �Q�[���I�[�o�[���Đ�
	PlaySoundMem(gSound._se["lose"], DX_PLAYTYPE_BACK);
	// �Q�[���I�[�o�[���̐��f�[�^�Đ�
	PlaySoundMem(gPlayerVoice._vc["gameover"], DX_PLAYTYPE_BACK);

	_cg[0] = resource::ResourceServer::LoadGraph("res/band.png");
	_cg[1] = resource::ResourceServer::LoadGraph("res/gameover.png");

	return true;
}

/*
 * ���
 */
bool ModeGameOver::Terminate(){
	base::Terminate();

	return true;
}

/*
 * �t���[�������F�v�Z
 */
bool ModeGameOver::Process(){
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetKeyTrg();

	::mode::ModeServer::GetInstance()->SkipProcessUnderLayer();

	// �Q�[���p�b�h�uB�v�{�^���ŃQ�[���I�[�o�[���[�h�ƃQ�[�����[�h���폜���A
	// �^�C�g�����[�h��ǉ�
	if (trg & PAD_INPUT_2) {
		StopSoundMem(gSound._se["lose"]);

		::mode::ModeServer::GetInstance()->Del(this);
		::mode::ModeServer::GetInstance()->Del(::mode::ModeServer::GetInstance()->Get("game"));

		::mode::ModeServer::GetInstance()->Add(NEW ModeTitle, 1, "title");
	}

	return true;
}

/*
 * �t���[�������F�`��
 */
bool ModeGameOver::Render(){
	base::Render();

	DrawGraph(0, POS_Y, _cg[0], FALSE);
	DrawGraph(0, POS_Y, _cg[1], TRUE);

	return true;
}