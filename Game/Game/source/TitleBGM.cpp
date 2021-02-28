/**
 * @file   TitleBGM.cpp
 * @brief  �A�E�g�Q�[���pBGM�Đ�
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "TitleBGM.h"
#include "Sound.h"

TitleBGM::TitleBGM() {
	// BGM�Đ��J�n
	PlaySoundMem(gSound._bgm["titlebgm"], DX_PLAYTYPE_BACK);
}

TitleBGM::~TitleBGM() {

}