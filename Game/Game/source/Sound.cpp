/**
 * @file   Sound.cpp
 * @brief  BGM,SE読み込み
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "Sound.h"

 // 実体：BGM,SE呼び出し
Sound gSound; 

Sound::Sound() {
}

Sound::~Sound() {
}

/**
 * BGM,SE読み込み
 */
void Sound::Init() {

	_bgm["titlebgm"] = ResourceServer::LoadSoundMem("res/bgm/title.wav");  // アウトゲーム側(タイトル画面等)のBGM
	_bgm["boss"]     = ResourceServer::LoadSoundMem("res/bgm/boss.wav");   // ボスステージのBGM

	_se["down"]       = ResourceServer::LoadSoundMem("res/se/down.wav");
	_se["explosion1"] = ResourceServer::LoadSoundMem("res/se/explosion_1.wav");
	_se["explosion2"] = ResourceServer::LoadSoundMem("res/se/explosion_2.wav");
	_se["h_attack"]   = ResourceServer::LoadSoundMem("res/se/hattack.wav");
	_se["l_attack"]   = ResourceServer::LoadSoundMem("res/se/lattack.wav");
	_se["hit_boss"]   = ResourceServer::LoadSoundMem("res/se/hit.wav");
	_se["hit_player"] = ResourceServer::LoadSoundMem("res/se/hit2.wav");
	_se["select"]     = ResourceServer::LoadSoundMem("res/se/select.wav");
	_se["shoot"]      = ResourceServer::LoadSoundMem("res/se/shoot.wav");
	_se["decision"]   = ResourceServer::LoadSoundMem("res/se/decision.wav");
	_se["win"]        = ResourceServer::LoadSoundMem("res/se/win.wav");
	_se["lose"]       = ResourceServer::LoadSoundMem("res/se/lose.wav");
}