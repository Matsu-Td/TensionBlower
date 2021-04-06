/** 
 * @file   BossVoiceChange.cpp
 * @brief  ボスの声データ切替、再生処理
 * 
 * @author matsuo tadahiko
 * @date   2021/04/07
 */

#include "Boss.h"
#include "LoadBossVoice.h"

/*
 * 声データ再生
 */
void Boss::PlayVoice(std::string voiceName) {
	PlaySoundMem(gBossVoice._vc[voiceName], DX_PLAYTYPE_BACK);
}

/*
 * 6種類の声データをランダムで再生
 */
void Boss::PlayAttackVoiceChange() {

	int voiceNo = rand() % ATTACK_VOICE_NUM;
	PlayVoice(_attackNameNo[voiceNo]);
}
