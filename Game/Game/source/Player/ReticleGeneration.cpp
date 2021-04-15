/** 
 * @file   ReticleGeneration.cpp
 * @brief  照準生成処理
 * 
 * @author matsuo tadahiko
 * @date   2021/04/06
 */

#include "Player.h"
#include "../Application/ApplicationMain.h"
#include "../Mode/ModeGame.h"
#include "Reticle.h"

using namespace tensionblower::player;

/*
 * マルチロックオンシステム用照準追加
 */
void Player::ReticleGeneration() {

	// キーのトリガ情報取得	
	int trg = ApplicationMain::GetInstance()->GetKeyTrg();

	// ゲームパッド「LBボタン」でマルチロックオンシステム用照準追加
	if (trg & PAD_INPUT_5) {
		mode::ModeGame* modeGame = static_cast<mode::ModeGame*>(::mode::ModeServer::GetInstance()->Get("game"));
		Reticle* reticle = NEW Reticle();
		modeGame->_objServer.Add(reticle);
	}
}