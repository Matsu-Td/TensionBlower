/** 
 * @file   ReticleGeneration.cpp
 * @brief  照準生成処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/26
 */

#include "Player.h"
#include "../Application/ApplicationMain.h"
#include "../Mode/ModeGame.h"
#include "Reticle.h"

 /*
  * マルチロックオンシステム用照準追加
  */
void Player::ReticleGeneration() {

	// キーのトリガ情報取得	
	int trg = ApplicationMain::GetInstance()->GetTrg();

	// ゲームパッド「LBボタン」でマルチロックオンシステム用照準追加
	if (trg & PAD_INPUT_5) {
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		Reticle* reticle = NEW Reticle();
		modeGame->_objServer.Add(reticle);
	}
}