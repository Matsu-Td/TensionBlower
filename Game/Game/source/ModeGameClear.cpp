
/**
 * @file  ModeGameClear.cpp
 * @brief �Q�[���N���A���
 * 
 * @data 2021-02-08
 */

#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeGame.h"
#include "ModeGameClear.h"
#include "ModeResult.h"

/**
 * ������
 */
bool ModeGameClear::Initialize(){
	if (!base::Initialize()) { return false; }

	_cg = ResourceServer::LoadGraph("res/���f��/�Q�[���N���A.png");

	// �N���A����܂ł̌o�ߎ��Ԃ��i�[
	gGlobal._gameTime = GetNowCount() - gGlobal._gameTime;

	return true;
}

/**
 * ���
 */
bool ModeGameClear::Terminate(){
	base::Terminate();

	return true;
}

/**
 * �t���[�������F�v�Z
 */
bool ModeGameClear::Process(){
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	ModeServer::GetInstance()->SkipProcessUnderLayer();

	// �Q�[���p�b�h�uB�v�{�^���ŃQ�[���N���A���[�h�ƃQ�[�����[�h���폜���A
	// ���U���g���[�h�ǉ�
	if (trg & PAD_INPUT_2) {  
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Del(ModeServer::GetInstance()->Get("game"));

		ModeResult* modeResult = new ModeResult();
		ModeServer::GetInstance()->Add(modeResult, 1, "result");
	}

	return true;
}

/**
 * �t���[�������F�`��
 */
bool ModeGameClear::Render(){
	base::Render();

	DrawGraph(0, 0, _cg, FALSE);

	return true;
}