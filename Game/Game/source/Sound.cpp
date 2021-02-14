
/**
 * @file Sound.h
 * @brief BGM,SE�ǂݍ���
 *
 * @date 2021-02-13
 */

#include "Sound.h"

 // ���́FBGM,SE�Ăяo��
Sound gSound; 

Sound::Sound() {
}

Sound::~Sound() {
}

/**
 * BGM,SE�ǂݍ���
 */
void Sound::Init() {

	_bgm["titlebgm"] = ResourceServer::LoadSoundMem("res/bgm/title.wav");  // �A�E�g�Q�[����(�^�C�g����ʓ�)��BGM
	_bgm["boss"]     = ResourceServer::LoadSoundMem("res/bgm/boss.wav");   // �{�X�X�e�[�W��BGM
}