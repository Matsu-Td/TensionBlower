
/**
 * @file  ModeOption.cpp
 * @brief �|�[�Y���
 *
 * @date 2021-02-08
 */

#include "ApplicationMain.h"
#include "ModeOption.h"
#include "ModeTitle.h"

/**
 * ������
 */
bool ModeOption::Initialize(){
	if (!base::Initialize()) { return false; }

	_cg = ResourceServer::LoadGraph("res/���f��/�|�[�Y.png");

	_ui[0] = ResourceServer::LoadGraph("res/ui/on/title_on_1.png");
	_ui[1] = ResourceServer::LoadGraph("res/ui/on/title_on_6.png");
	_ui[2] = ResourceServer::LoadGraph("res/ui/off/title_off_1.png");
	_ui[3] = ResourceServer::LoadGraph("res/ui/off/title_off_6.png");

	_menuPos = 0;

	return true;
}

/**
 * ���
 */
bool ModeOption::Terminate(){
	base::Terminate();

	return true;
}

/**
 * �t���[�������F�v�Z
 */
bool ModeOption::Process(){
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	ModeServer::GetInstance()->SkipProcessUnderLayer(); 

	// �Q�[���p�b�h�̏㉺�L�[�y�э��A�i���O�X�e�B�b�N�㉺�Ń��j���[�I��
	if (_menuPos == 0) {
		if (trg & PAD_INPUT_DOWN) {
			_menuPos++;
		}

		// �Q�[���p�b�h�uB�v�{�^���Ń|�[�Y���[�h�폜�˃Q�[�����[�h�֖߂�
		if (trg & PAD_INPUT_2) {  
			ModeServer::GetInstance()->Del(this);
		}
	}
	if (_menuPos == 1) {
		if (trg & PAD_INPUT_UP) {
			_menuPos--;
		}

		// �Q�[���p�b�h�uB�v�{�^���Ń|�[�Y���[�h�ƃQ�[�����[�h���폜���A
		// �^�C�g�����[�h�ǉ�
		if (trg & PAD_INPUT_2) {  
			ModeServer::GetInstance()->Del(this);
			ModeServer::GetInstance()->Del(ModeServer::GetInstance()->Get("game"));

			ModeTitle* modeTitle = NEW ModeTitle();
			ModeServer::GetInstance()->Add(modeTitle, 1, "title");
		}
	}

	// �Q�[���p�b�h�uSTART�v�{�^���Ń|�[�Y���[�h�폜�˃Q�[�����[�h�֖߂�
	if (trg & PAD_INPUT_8) { 
		ModeServer::GetInstance()->Del(this);
	}

	return true;
}

/**
 * �t���[�������F�`��
 */
bool ModeOption::Render(){
	base::Render();

	DrawGraph(0, 0, _cg, TRUE);

	// ������
	if (_menuPos == 0) {
		DrawGraph(786, 380, _ui[0], TRUE);
		DrawGraph(786, 580, _ui[3], TRUE);
	}
	if (_menuPos == 1) {
		DrawGraph(786, 380, _ui[2], TRUE);
		DrawGraph(786, 580, _ui[1], TRUE);
	}
	return true;
}