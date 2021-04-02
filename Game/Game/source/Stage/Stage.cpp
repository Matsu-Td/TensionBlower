/**
 * @file   Stage.cpp
 * @brief  ステージクラス
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "Stage.h"
#include "../Application/ApplicationMain.h"

Stage::Stage(){
	_mh = ResourceServer:: MV1LoadModel("res/model/stage/stage_collision.mv1");
	_mhMap = ResourceServer::MV1LoadModel("res/model/stage/stage.mv1");
	MV1SetupCollInfo(_mh, -1, 8, 8, 8);
}

Stage::~Stage(){
	// 何もしない
}

/**
 * フレーム処理：描画
 */
void Stage::Render(){

	MV1DrawModel(_mhMap);
}