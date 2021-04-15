/**
 * @file   Sound.cpp
 * @brief  BGM,SE読み込み処理
 * 
 * @author matsuo tadahiko
 * @date   2021/02/13
 */

#include "Sound.h"

using namespace tensionblower::sound;

// 実体：BGM,SE呼び出し
Sound gSound; 

/*
 * BGM,SE読み込み
 */
void Sound::Initialize() {

	_bgm["titlebgm"] = resource::ResourceServer::LoadSoundMem("res/bgm/title.wav");  // アウトゲーム側(タイトル画面等)のBGM
	_bgm["boss"]     = resource::ResourceServer::LoadSoundMem("res/bgm/boss.wav");   // ボスステージのBGM

	_se["down"]       = resource::ResourceServer::LoadSoundMem("res/se/down.wav");
	_se["explosion1"] = resource::ResourceServer::LoadSoundMem("res/se/explosion_1.wav");
	_se["explosion2"] = resource::ResourceServer::LoadSoundMem("res/se/explosion_2.wav");
	_se["h_attack"]   = resource::ResourceServer::LoadSoundMem("res/se/hattack.wav");
	_se["l_attack"]   = resource::ResourceServer::LoadSoundMem("res/se/lattack.wav");
	_se["hit_boss"]   = resource::ResourceServer::LoadSoundMem("res/se/hit.wav");
	_se["hit_player"] = resource::ResourceServer::LoadSoundMem("res/se/hit2.wav");
	_se["select"]     = resource::ResourceServer::LoadSoundMem("res/se/select.wav");
	_se["shoot"]      = resource::ResourceServer::LoadSoundMem("res/se/shoot.wav");
	_se["decision"]   = resource::ResourceServer::LoadSoundMem("res/se/decision.wav");
	_se["win"]        = resource::ResourceServer::LoadSoundMem("res/se/win.wav");
	_se["lose"]       = resource::ResourceServer::LoadSoundMem("res/se/lose.wav");
}