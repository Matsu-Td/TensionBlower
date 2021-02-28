/**
 * @file   Stage.cpp
 * @brief  ステージ描画
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "Stage.h"
#include "ApplicationMain.h"

Stage::Stage(){
	_mh = ResourceServer:: MV1LoadModel("res/model/仮データ/stage_dummy02.mv1");
	_mhMap = ResourceServer::MV1LoadModel("res/model/stage/stage.mv1");
	MV1SetupCollInfo(_mh, -1, 8, 8, 8);
}

Stage::~Stage(){

}

/**
 * フレーム処理：描画
 */
void Stage::Render(){
#if 0
	{
		float linelength = 1000.0f;
		VECTOR v = { 0.0f, 0.0f, 0.0f };
		DrawLine3D(VAdd(v, VGet(-linelength, 0, 0)), VAdd(v, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
		DrawLine3D(VAdd(v, VGet(0, -linelength, 0)), VAdd(v, VGet(0, linelength, 0)), GetColor(0, 255, 0));
		DrawLine3D(VAdd(v, VGet(0, 0, -linelength)), VAdd(v, VGet(0, 0, linelength)), GetColor(0, 0, 255));
	}
#endif

	MV1DrawModel(_mhMap);
}