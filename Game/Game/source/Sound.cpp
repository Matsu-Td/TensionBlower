/**
 * @file   Sound.cpp
 * @brief  BGM,SE�ǂݍ���
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
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

	_se["down"]       = ResourceServer::LoadSoundMem("res/se/down.wav");
	_se["explosion1"] = ResourceServer::LoadSoundMem("res/se/explosion_1.wav");
	_se["explosion2"] = ResourceServer::LoadSoundMem("res/se/explosion_2.wav");
	_se["h_attack"]   = ResourceServer::LoadSoundMem("res/se/hattack.wav");
	_se["l_attack"]   = ResourceServer::LoadSoundMem("res/se/lattack.wav");
	_se["hit"]        = ResourceServer::LoadSoundMem("res/se/hit.wav");
	_se["select"]     = ResourceServer::LoadSoundMem("res/se/select.wav");
	_se["shoot"]      = ResourceServer::LoadSoundMem("res/se/shoot.wav");
}