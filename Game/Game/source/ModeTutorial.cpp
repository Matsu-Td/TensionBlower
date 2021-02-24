
/**
 * @file  ModeTutorial.cpp
 * @brief �`���[�g���A�����
 *
 * @date 2021-02-08
 */

#include "ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeTutorial.h"

/**
 * ������
 */
bool ModeTutorial::Initialize() {
	if (!base::Initialize()) { return false; }

	_cg = ResourceServer::LoadGraph("res/���f��/tutorial.png");

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
		_menuPos++;
	}
	if (trg & PAD_INPUT_UP) {
		_menuPos--;
	}

	// �Q�[���p�b�h�uA�v�{�^���Ń`���[�g���A�����[�h���폜���A
	// �^�C�g�����[�h�ǉ�
	if (trg & PAD_INPUT_1) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
	}

	return true;
}

/**
 * �t���[�������F�`��
 */
bool ModeTutorial::Render() {
	base::Render();

	DrawGraph(0, 0, _cg, FALSE);

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
