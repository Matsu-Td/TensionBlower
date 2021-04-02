/**
 * @file   Stage.cpp
 * @brief  �X�e�[�W�`��
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

}

/**
 * �t���[�������F�`��
 */
void Stage::Render(){

	MV1DrawModel(_mhMap);
}