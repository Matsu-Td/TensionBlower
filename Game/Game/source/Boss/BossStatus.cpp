/**
 * @file   BossStatus.cpp
 * @brief  �{�X�X�e�[�^�XUI�`��
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "Boss.h"
#include "BossStatus.h"
#include "../Mode/ModeGame.h"

BossStatus::BossStatus() {

	_cgName    = ResourceServer::LoadGraph("res/ui/boss/enemy_name.png");
	_cgFrame   = ResourceServer::LoadGraph("res/ui/boss/enemy_status.png");
	_cgFrameBg = ResourceServer::LoadGraph("res/ui/boss/enemy_status_2.png");
	_cgShield  = ResourceServer::LoadGraph("res/ui/boss/enemy_shield.png");

	// HP�o�[�Ɩ{���\���p�̃A�C�R���ǂݍ���
	for (int i = 0; i < HP_BAR_NUM; i++) {
		_cgHP[i] = ResourceServer::LoadGraph(_hpBarString[i]);
		_cgIcon[i] = ResourceServer::LoadGraph(_iconString[i]);
	}
}

BossStatus::~BossStatus() {

}

/**
 * �t���[�������F�`��
 */
void BossStatus::Render(){

	// �{�X���擾
	int hitpoint = Boss::GetInstance()->GetHitPoint();
	int shield   = Boss::GetInstance()->GetShield();
	int phase    = Boss::GetInstance()->GetPhase();

	// �X�e�[�^�X�o�[�w�i
	DrawGraph(FRAME_POS_X, FRAME_BG_POS_Y, _cgFrameBg, TRUE);

	// 5�d��HP�o�[���t�F�[�Y���ɐ��䂷��
	int nowBarNum = HP_BAR_NUM - 1 - phase;  // ���݂̎c��HP�o�[�{��-1
	for (int i = 0; i < nowBarNum; i++) {
		DrawExtendGraph(HP_POS_X_L, HP_POS_Y_L, HP_POS_X_R, HP_POS_Y_R, _cgHP[i], TRUE);
	}
	// ��ԏ�ɕ\������HP�o�[
	DrawExtendGraph(HP_POS_X_L + HP_SIZE - (HP_SIZE * (hitpoint - (HP_ONE * nowBarNum)) / HP_ONE),
		            HP_POS_Y_L, HP_POS_X_R, HP_POS_Y_R, _cgHP[nowBarNum], TRUE);

	// HP�o�[�c��{���\��
	if (hitpoint > 0) {
		for (int i = 0; i < HP_BAR_NUM - phase; i++) {
			DrawGraph(ICON_POS_X[i], ICON_POS_Y, _cgIcon[i], TRUE);
		}
	}

	// �V�[���h�o�[
	DrawExtendGraph(SHIELD_POS_X_L + SHIELD_SIZE - (SHIELD_SIZE * shield / SHIELD_ONE), SHIELD_POS_Y_L, SHIELD_POS_X_R, SHIELD_POS_Y_R, _cgShield, TRUE);

	// �X�e�[�^�X�o�[�{��
	DrawGraph(FRAME_POS_X, FRAME_POS_Y, _cgFrame, TRUE);

	// �{�X���\��
	DrawGraph(NAME_POS_X, NAME_POS_Y, _cgName, TRUE);
}