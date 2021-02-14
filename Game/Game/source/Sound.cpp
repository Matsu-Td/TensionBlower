
/**
 * @file Sound.h
 * @brief BGM,SE読み込み
 *
 * @date 2021-02-13
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
}