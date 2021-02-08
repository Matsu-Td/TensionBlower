
/**
 * @file  Stage.cpp
 * @brief ステージ
 *
 * @date 2021-02-08
 */

#include "Stage.h"
#include "ApplicationMain.h"


Stage::Stage(){
	_mh = ResourceServer:: MV1LoadModel("res/model/仮データ/stage_dummy02.mv1");
	MV1SetupCollInfo(_mh, -1, 8, 8, 8);
}

Stage::~Stage(){

}

void Stage::Initialize(){

}

void Stage::Process(){

}

void Stage::Render(){
#ifdef _DEBUG
	{
		float linelength = 1000.f;
		VECTOR v = { 0, 0, 0 };
		DrawLine3D(VAdd(v, VGet(-linelength, 0, 0)), VAdd(v, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
		DrawLine3D(VAdd(v, VGet(0, -linelength, 0)), VAdd(v, VGet(0, linelength, 0)), GetColor(0, 255, 0));
		DrawLine3D(VAdd(v, VGet(0, 0, -linelength)), VAdd(v, VGet(0, 0, linelength)), GetColor(0, 0, 255));
	}
#endif

	MV1DrawModel(_mh);
}