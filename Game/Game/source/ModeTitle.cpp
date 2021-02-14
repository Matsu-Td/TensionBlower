
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

	if (!CheckSoundMem(gSound._bgm["titlebgm"])) {
		ModeServer::GetInstance()->Add(NEW TitleBGM(), 0, "titlebgm");
	}

	_cgtitle            = ResourceServer::LoadGraph("res/logo_title.png");

	_ui["on_start"]     = ResourceServer::LoadGraph("res/ui/on/title_on_1.png");
	_ui["on_tutorial"]  = ResourceServer::LoadGraph("res/ui/on/title_on_2.png");
	_ui["on_ranking"]   = ResourceServer::LoadGraph("res/ui/on/title_on_3.png");
	_ui["on_credit"]    = ResourceServer::LoadGraph("res/ui/on/title_on_5.png");
	_ui["on_end"]       = ResourceServer::LoadGraph("res/ui/on/title_on_6.png");
	_ui["off_start"]    = ResourceServer::LoadGraph("res/ui/off/title_off_1.png");
	_ui["off_tutorial"] = ResourceServer::LoadGraph("res/ui/off/title_off_2.png");
	_ui["off_ranking"]  = ResourceServer::LoadGraph("res/ui/off/title_off_3.png");
	_ui["off_credit"]   = ResourceServer::LoadGraph("res/ui/off/title_off_5.png");
	_ui["off_end"]      = ResourceServer::LoadGraph("res/ui/off/title_off_6.png");

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

	if (trg & PAD_INPUT_B) {
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

		case MENU::GAME_END:
			ModeServer::GetInstance()->Del(this);
			ApplicationBase::GetInstance()->GameEnd();
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

	int menuNum = static_cast<int>(_ui.size()) / 2;
	_menuPos = (_menuPos + menuNum) % menuNum;

	MenuSelect();

	return true;
}

/**
 * �t���[�������F�`��
 */
bool ModeTitle::Render() {
	base::Render();

	DrawGraph(0, 0, _cgtitle, TRUE);

	DrawGraph(120, 480, _ui["off_start"],    TRUE);
	DrawGraph(435, 575, _ui["off_tutorial"], TRUE);
	DrawGraph(120, 670, _ui["off_ranking"],  TRUE);
	DrawGraph(435, 765, _ui["off_credit"],   TRUE);
	DrawGraph(120, 860, _ui["off_end"],      TRUE);

	if (_menuPos == MENU::START)	{ DrawGraph(120, 480, _ui["on_start"],    TRUE); }
	if (_menuPos == MENU::TUTORIAL) { DrawGraph(435, 575, _ui["on_tutorial"], TRUE); }
	if (_menuPos == MENU::RANKING)	{ DrawGraph(120, 670, _ui["on_ranking"],  TRUE); }
	if (_menuPos == MENU::CREDIT)   { DrawGraph(435, 765, _ui["on_credit"],   TRUE); }
	if (_menuPos == MENU::GAME_END) { DrawGraph(120, 860, _ui["on_end"],      TRUE); }

	// ������
	DrawFormatString(1500, 16, GetColor(255, 255, 255),"menuPos = %d",_menuPos);

	return true;
}
