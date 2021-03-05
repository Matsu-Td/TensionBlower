/**
 * @file   ModeTutorial.cpp
 * @brief  �`���[�g���A�����
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeTutorial.h"
#include "Sound.h"

/**
 * ������
 */
bool ModeTutorial::Initialize() {
	if (!base::Initialize()) { return false; }

	_bg    = ResourceServer::LoadGraph("res/title_back.png");
	_cg[0] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei1.png");
	_cg[1] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei2.png");
	_cg[2] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei3.png");
	_cg[3] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei4.png");
	_cg[4] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei5.png");
	_cg[5] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei6.png");
	_cg[6] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei7.png");
	_cg[7] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei8.png");
	_cg[8] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei9.png");

	// ���j���[UI�摜�ǂݍ���(�I����:ON)
	for (int i = 0; i < MENU_NUM; i++) {
		_uiOn[i] = ResourceServer::LoadGraph(_fileNameOn[i]);
	}

	// ���j���[UI�摜�ǂݍ���(���I�����:OFF)
	for (int i = 0; i < MENU_NUM; i++) {
		_uiOff[i] = ResourceServer::LoadGraph(_fileNameOff[i]);
	}

	_menuPos = 0;

	return true;
}

/**
 * ���
 */
bool ModeTutorial::Terminate() {
	base::Terminate();

	return true;
}

/**
 * �t���[�������F�v�Z
 */
bool ModeTutorial::Process() {
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	int menuNum = ALL_MENU_NUM / 2;
	_menuPos = (_menuPos + menuNum) % menuNum;


	// �Q�[���p�b�h�̏㉺�L�[�y�э��A�i���O�X�e�B�b�N�㉺�Ń��j���[�I��
	if (trg & PAD_INPUT_DOWN) {
		PlaySoundMem(gSound._se["select"], DX_PLAYTYPE_BACK);
		_menuPos++;
	}
	if (trg & PAD_INPUT_UP) {
		PlaySoundMem(gSound._se["select"], DX_PLAYTYPE_BACK);
		_menuPos--;
	}

	// �Q�[���p�b�h�uA�v�{�^���Łu�߂�v��I������ƃ`���[�g���A�����[�h���폜���A�^�C�g�����[�h�ǉ�
	if (_menuPos == 9) { 
		if (trg & PAD_INPUT_2) {
			ModeServer::GetInstance()->Del(this);
			ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
		}
	}

	return true;
}

/**
 * �t���[�������F�`��
 */
bool ModeTutorial::Render() {
	base::Render();

	DrawGraph(0, 0, _bg, TRUE);
	DrawGraph(50, 50, _cg[_menuPos], TRUE);

	// ���j���[UI�摜(���I�����:OFF)�͑I�𒆂͕\�����Ȃ�
	for (int menuNum = 0; menuNum < MENU_NUM; menuNum++) {
		if (_menuPos != menuNum) { DrawGraph(MENU_POS_X[menuNum], MENU_POS_Y[menuNum], _uiOff[menuNum], TRUE); }
	}

	// ���j���[UI�摜(�I�����:ON)�͑I�𒆂̂ݕ\������
	for (int menuNum = 0; menuNum < MENU_NUM; menuNum++) {
		if (_menuPos == menuNum) { DrawGraph(MENU_POS_X[menuNum], MENU_POS_Y[menuNum], _uiOn[menuNum], TRUE); }
	}

	return true;
}
