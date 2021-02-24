
/**
 * @file  ModeTitle.cpp
 * @brief �^�C�g�����
 *
 * @date 2021-02-09
 */

#include "ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGameStart.h"
#include "ModeCredit.h"
#include "ModeTutorial.h"
#include "ModeRanking.h"
#include "ModeGame.h"
#include "TitleBGM.h"
#include "Sound.h"

/**
 * ������
 */
bool ModeTitle::Initialize() {
	if (!base::Initialize()) { return false; }

	// BGM�Đ�(�Đ����Ă��Ȃ���)
	if (!CheckSoundMem(gSound._bgm["titlebgm"])) {
		ModeServer::GetInstance()->Add(NEW TitleBGM(), 0, "titlebgm");
	}

	_bg      = ResourceServer::LoadGraph("res/title_back.png");
	_cgtitle = ResourceServer::LoadGraph("res/logo_title.png");

	// ���j���[UI�摜�ǂݍ���(�I����:ON)
	for (int i = 0; i < MENU_NUM; i++) {
		_uiOn[i] = ResourceServer::LoadGraph(_fileNameOn[i]);
	}

	// ���j���[UI�摜�ǂݍ���(���I�����:OFF)
	for (int i = 0; i < MENU_NUM; i++) {
		_uiOff[i] = ResourceServer::LoadGraph(_fileNameOff[i]);
	}
	
	_menuPos = MENU::START;  // �����ʒu

	return true;
}

/**
 * ���
 */
bool ModeTitle::Terminate() {
	base::Terminate();

	return true;
}

/**
 * �^�C�g�����j���[�I��
 */
void ModeTitle::MenuSelect() {

	int trg = ApplicationMain::GetInstance()->GetTrg();

	// �Q�[���p�b�h�̏㉺�L�[�y�э��A�i���O�X�e�B�b�N�㉺�Ń��j���[�I��
	if (trg & PAD_INPUT_DOWN) {
		_menuPos++;
	}
	if (trg & PAD_INPUT_UP) {
		_menuPos--;
	}

	if (trg & PAD_INPUT_2) {
		switch (_menuPos) {
		case MENU::START:
			ModeServer::GetInstance()->Del(ModeServer::GetInstance()->Get("titlebgm"));
			ModeChange(NEW ModeGame(),   1, "game");   
			break;
		case MENU::TUTORIAL:
			ModeChange(NEW ModeTutorial(), 1, "tutorial"); break;

		case MENU::RANKING:
			ModeChange(NEW ModeRanking(),  1, "ranking");  break;

		case MENU::CREDIT:
			ModeChange(NEW ModeCredit(),   1, "credit");   break;

		case MENU::GAME_END:  // ������
//			ModeServer::GetInstance()->Del(this);
//			ApplicationBase::GetInstance()->GameEnd();
			break;
		}
	}
}

/**
 * �^�C�g���폜�A���̃��[�h�o�^
 */
void ModeTitle::ModeChange(ModeBase* nextMode, int layer, const char* modeName) {
	// �^�C�g�����[�h���폜
	ModeServer::GetInstance()->Del(this);
	// ���̃��[�h��o�^
	ModeServer::GetInstance()->Add(nextMode, layer, modeName);
}

/**
 * �t���[�������F�v�Z
 */
bool ModeTitle::Process() {
	base::Process();

	int menuNum = ALL_MENU_NUM / 2;
	_menuPos = (_menuPos + menuNum) % menuNum;

	MenuSelect();

	return true;
}

/**
 * �t���[�������F�`��
 */
bool ModeTitle::Render() {
	base::Render();

	DrawGraph(0, 0, _bg, TRUE);
	DrawGraph(0, 0, _cgtitle, TRUE);

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
