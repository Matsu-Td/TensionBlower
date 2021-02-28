/**
 * @file   Reticle.cpp
 * @brief  ���`�N������
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "Reticle.h"
#include "ApplicationMain.h"
#include "Camera.h"
#include "ModeGame.h"

Reticle::Reticle(){

	_cg = ResourceServer::LoadGraph("res/ui/player/mls_reticle.png");
	Initialize();
}

Reticle::~Reticle(){

}

/**
 * ������
 */
void Reticle::Initialize(){

	// ��ʂ̐^�񒆂ɉ摜��z�u
	_scrnPos.x = ApplicationMain::GetInstance()->DispSizeW() / 2 - 50;
	_scrnPos.y = ApplicationMain::GetInstance()->DispSizeH() / 2 - 50;

	_mvSpd = 16.0f;

	_hitX = _hitY = 20.0f;
	_hitW = _hitH = 80.0f;
}

/**
 * �t���[�������F�v�Z
 */
void Reticle::Process(){

	// �J�����̏�Ԏ擾
	int camState = Camera::GetInstance()->GetCameraState();

	// �A�i���O�X�e�B�b�N�Ή�
	DINPUT_JOYSTATE dinput;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &dinput);
	
	// ���A�i���O�X�e�B�b�N���W
	float lx, ly;   
	lx = static_cast<float>(dinput.X);
	ly = static_cast<float>(dinput.Y);

	// ���A�i���O�X�e�B�b�N��|�����Ƃ��̍ŏ��l
	float analogMin = 0.3f;

	// ��ʃT�C�Y�擾
	int dispSizeW = ApplicationMain::GetInstance()->DispSizeW();
	int dispSizeH = ApplicationMain::GetInstance()->DispSizeH();
	
	// ���`�N������
	if (lx < analogMin)  { _scrnPos.x -= _mvSpd; }
	if (lx > -analogMin) { _scrnPos.x += _mvSpd; }
	if (ly < analogMin)  { _scrnPos.y -= _mvSpd; }
	if (ly > -analogMin) { _scrnPos.y += _mvSpd; }

	// ��ʊO�ɉ摜���o��̂�h�~
	if (_scrnPos.x < 0) { _scrnPos.x = 0; }
	if (_scrnPos.x + 100 > dispSizeW) { _scrnPos.x = dispSizeW - 100; }
	if (_scrnPos.y < 0) { _scrnPos.y = 0; }
	if (_scrnPos.y + 100 > dispSizeH) { _scrnPos.y = dispSizeH - 100; }

	// �J�����̏�Ԃ��}���`���b�N�I���V�X�e���ł͂Ȃ��Ȃ�
	if (camState != Camera::STATE::MLS_LOCK){
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		modeGame->_objServer.Del(this);
	}
}

/**
 * �t���[�������F�`��
 */
void Reticle::Render(){

	DrawGraph(static_cast<int>(_scrnPos.x), static_cast<int>(_scrnPos.y), _cg, TRUE);
	//DrawBox(_scrnPos.x + _hitX, _scrnPos.y + _hitY, _scrnPos.x + _hitW, _scrnPos.y + _hitH, GetColor(255, 0, 0), TRUE);
}