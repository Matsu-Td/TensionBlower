/**
 * @file   ModePause.cpp
 * @brief  �|�[�Y���[�h�N���X
 * 
 * @author matsuo tadahiko
 * @date   2020/12/27
 */

#include "../Application/ApplicationMain.h"
#include "ModePause.h"
#include "ModeTitle.h"
#include "../Sound/Sound.h"

using namespace tensionblower::mode;

/*
 * ������
 */
bool ModePause::Initialize(){
	if (!base::Initialize()) { return false; }

	_cg = ResourceServer::LoadGraph("res/pause.png");

	_ui[0] = ResourceServer::LoadGraph("res/ui/pause/pause_on_01.png");
	_ui[1] = ResourceServer::LoadGraph("res/ui/pause/pause_on_02.png");
	_ui[2] = ResourceServer::LoadGraph("res/ui/pause/pause_off_01.png");
	_ui[3] = ResourceServer::LoadGraph("res/ui/pause/pause_off_02.png");

	_menuPos = 0;

	return true;
}

/*
 * ���
 */
bool ModePause::Terminate(){
	base::Terminate();

	return true;
}

/*
 * �t���[�������F�v�Z
 */
bool ModePause::Process(){
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetKeyTrg();

	ModeServer::GetInstance()->SkipProcessUnderLayer(); 

	// �Q�[���p�b�h�̏㉺�L�[�y�э��A�i���O�X�e�B�b�N�㉺�Ń��j���[�I��
	if (_menuPos == 0) {
		if (trg & PAD_INPUT_DOWN) {
			PlaySoundMem(gSound._se["select"], DX_PLAYTYPE_BACK);

			_menuPos++;
		}

		// �Q�[���p�b�h�uB�v�{�^���Ń|�[�Y���[�h�폜�˃Q�[�����[�h�֖߂�
		if (trg & PAD_INPUT_2) { 
			PlaySoundMem(gSound._se["decision"], DX_PLAYTYPE_BACK);

			ModeServer::GetInstance()->Del(this);
		}
	}
	if (_menuPos == 1) {
		if (trg & PAD_INPUT_UP) {
			PlaySoundMem(gSound._se["select"], DX_PLAYTYPE_BACK);

			_menuPos--;
		}

		// �Q�[���p�b�h�uB�v�{�^���Ń|�[�Y���[�h�ƃQ�[�����[�h���폜���A
		// �^�C�g�����[�h�ǉ�
		if (trg & PAD_INPUT_2) {  
			PlaySoundMem(gSound._se["decision"], DX_PLAYTYPE_BACK);
			StopSoundMem(gSound._bgm["boss"]);

			ModeServer::GetInstance()->Del(this);
			ModeServer::GetInstance()->Del(ModeServer::GetInstance()->Get("game"));

			ModeServer::GetInstance()->Add(NEW ModeTitle(), 1, "title");
		}
	}

	// �Q�[���p�b�h�uSTART�v�{�^���Ń|�[�Y���[�h�폜�˃Q�[�����[�h�֖߂�
	if (trg & PAD_INPUT_8) { 
		ModeServer::GetInstance()->Del(this);
	}

	return true;
}

/*
 * �t���[�������F�`��
 */
bool ModePause::Render(){
	base::Render();

	DrawGraph(0, 0, _cg, TRUE);

	if (_menuPos == 0) {
		DrawGraph(POS_X, POS_Y_UP,    _ui[0], TRUE);
		DrawGraph(POS_X, POS_Y_UNDER, _ui[3], TRUE);
	}
	if (_menuPos == 1) {
		DrawGraph(POS_X, POS_Y_UP,    _ui[2], TRUE);
		DrawGraph(POS_X, POS_Y_UNDER, _ui[1], TRUE);
	}
	return true;
}