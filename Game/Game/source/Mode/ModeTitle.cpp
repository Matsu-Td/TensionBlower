/**
 * @file   ModeTitle.cpp
 * @brief  �^�C�g�����[�h�N���X
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#include "../Application/ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGameStart.h"
#include "ModeCredit.h"
#include "ModeTutorial.h"
#include "ModeGame.h"
#include "TitleBGM.h"
#include "../Sound/Sound.h"
#include "../Player/LoadPlayerVoice.h"
#include "../Boss/LoadBossVoice.h"

/*
 * ������
 */
bool ModeTitle::Initialize() {
	if (!base::Initialize()) { return false; }

	// BGM�Đ�(�Đ����Ă��Ȃ���)
	if (!CheckSoundMem(gSound._bgm["titlebgm"])) {
		ModeServer::GetInstance()->Add(NEW TitleBGM(), 0, "titlebgm");
	}

	// �v���C���[or�{�X�̐��Ń^�C�g���R�[������(�����_��)
	int voice = rand() % 2;
	if (voice == 0) {
		// �v���C���[
		PlaySoundMem(gPlayerVoice._vc["title"], DX_PLAYTYPE_BACK);
	}
	else {
		// �{�X
		PlaySoundMem(gBossVoice._vc["title"], DX_PLAYTYPE_BACK);
	}

	// �w�i�p����ǂݍ���
	_movieHandle = ResourceServer::LoadGraph("res/movie/title_bg.mp4");

	// �^�C�g�����S�ǂݍ���
	_cgtitle = ResourceServer::LoadGraph("res/logo_title.png");

	// ����Đ��J�n
	PlayMovieToGraph(_movieHandle);

	// ���j���[UI�摜�ǂݍ���(�I����:ON)
	for (int i = 0; i < MENU_NUM; i++) {
		_uiOn[i] = ResourceServer::LoadGraph(_fileNameOn[i]);
	}

	// ���j���[UI�摜�ǂݍ���(���I�����:OFF)
	for (int i = 0; i < MENU_NUM; i++) {
		_uiOff[i] = ResourceServer::LoadGraph(_fileNameOff[i]);
	}

	// �����ʒu
	_menuPos = MENU::START;

	return true;
}

/*
 * ���
 */
bool ModeTitle::Terminate() {
	base::Terminate();

	return true;
}

/*
 * �^�C�g�����j���[�I��
 */
void ModeTitle::MenuSelect() {

	int trg = ApplicationMain::GetInstance()->GetTrg();

	// �Q�[���p�b�h�̍��E�L�[�y�э��A�i���O�X�e�B�b�N���E�Ń��j���[�I��
	if (trg & PAD_INPUT_RIGHT) {
		PlaySoundMem(gSound._se["select"], DX_PLAYTYPE_BACK);
		_menuPos++;
	}
	if (trg & PAD_INPUT_LEFT) {
		PlaySoundMem(gSound._se["select"], DX_PLAYTYPE_BACK);
		_menuPos--;
	}

	if (trg & PAD_INPUT_2) {
		PlaySoundMem(gSound._se["decision"], DX_PLAYTYPE_BACK);
		switch (_menuPos) {
		case MENU::START:
			// BGM�Đ���~
			StopSoundMem(gSound._bgm["titlebgm"]);
			ModeServer::GetInstance()->Del(ModeServer::GetInstance()->Get("titlebgm"));
			ModeChange(NEW ModeGame(),   1, "game");   
			break;
		case MENU::TUTORIAL:
			ModeChange(NEW ModeTutorial(), 1, "tutorial"); break;

		case MENU::CREDIT:
			ModeChange(NEW ModeCredit(),   1, "credit");   break;

		case MENU::GAME_END: 
			ModeServer::GetInstance()->Del(this);
			ApplicationBase::GetInstance()->GameEnd();
			break;
		}
	}

	// �w�i�̓�������[�v�Đ�������
	if (GetMovieStateToGraph(_movieHandle) == 0) {
		SeekMovieToGraph(_movieHandle, 0);  // ����̐擪�ɍĐ��ʒu���ړ�
		PlayMovieToGraph(_movieHandle);     // ����Đ��J�n
	}
}

/*
 * �^�C�g���폜�A���̃��[�h�o�^
 */
void ModeTitle::ModeChange(ModeBase* nextMode, int layer, const char* modeName) {
	// �^�C�g�����[�h���폜
	ModeServer::GetInstance()->Del(this);
	// ���̃��[�h��o�^
	ModeServer::GetInstance()->Add(nextMode, layer, modeName);
}

/*
 * �t���[�������F�v�Z
 */
bool ModeTitle::Process() {
	base::Process();

	int menuNum = ALL_MENU_NUM / 2;
	_menuPos = (_menuPos + menuNum) % menuNum;

	// ���j���[�I��
	MenuSelect();

	return true;
}

/*
 * �t���[�������F�`��
 */
bool ModeTitle::Render() {
	base::Render();

	DrawGraph(0, 0, _movieHandle, TRUE);
	DrawGraph(0, 0, _cgtitle, TRUE);

	// ���j���[UI�摜(���I�����:OFF)�͑I�𒆂͕\�����Ȃ�
	for (int menuNum = 0; menuNum < MENU_NUM; menuNum++) {
		if (_menuPos != menuNum) { DrawGraph(MENU_POS_X[menuNum], MENU_POS_Y, _uiOff[menuNum], TRUE); }
	}

	// ���j���[UI�摜(�I�����:ON)�͑I�𒆂̂ݕ\������
	for (int menuNum = 0; menuNum < MENU_NUM; menuNum++) {
		if (_menuPos == menuNum) { DrawGraph(MENU_POS_X[menuNum], MENU_POS_Y, _uiOn[menuNum], TRUE); }
	}

	return true;
}
