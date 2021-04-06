/** 
 * @file   BossVoiceChange.cpp
 * @brief  �{�X�̐��f�[�^�ؑցA�Đ�����
 * 
 * @author matsuo tadahiko
 * @date   2021/04/07
 */

#include "Boss.h"
#include "LoadBossVoice.h"

/*
 * ���f�[�^�Đ�
 */
void Boss::PlayVoice(std::string voiceName) {
	PlaySoundMem(gBossVoice._vc[voiceName], DX_PLAYTYPE_BACK);
}

/*
 * 6��ނ̐��f�[�^�������_���ōĐ�
 */
void Boss::PlayAttackVoiceChange() {

	int voiceNo = rand() % ATTACK_VOICE_NUM;
	PlayVoice(_attackNameNo[voiceNo]);
}
