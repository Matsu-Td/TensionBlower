
/**
 * @file TitleBGM.cpp
 * @brief �A�E�g�Q�[���pBGM�Đ�
 *
 * @date 2021-02-13
 */

#include "TitleBGM.h"
#include "Sound.h"

TitleBGM::TitleBGM() {
	// BGM�Đ��J�n
	PlaySoundMem(gSound._bgm["titlebgm"], DX_PLAYTYPE_BACK);
}

TitleBGM::~TitleBGM() {
	// BGM�Đ���~
	StopSoundMem(gSound._bgm["titlebgm"]);
}