/**
 * @file   Reticle.cpp
 * @brief  �v���C���[�Ə�����
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "Reticle.h"
#include "../Application/ApplicationMain.h"
#include "../Camera/Camera.h"
#include "../Mode/ModeGame.h"
#include "../Sound/Sound.h"

Reticle::Reticle(){

	_cg = ResourceServer::LoadGraph("res/ui/player/mls_reticle.png");

	Initialize();
}

Reticle::~Reticle(){
    // BGM�̍Đ����g�����f�t�H���g�ɖ߂�
	SetFrequencySoundMem(-1, gSound._bgm["boss"]);
}

/*
 * ������
 */
void Reticle::Initialize(){

	// ��ʂ̐^�񒆂ɉ摜��z�u
	_scrnPos.x = static_cast<float>(ApplicationMain::GetInstance()->DispSizeW() / 2 - 50);
	_scrnPos.y = static_cast<float>(ApplicationMain::GetInstance()->DispSizeH() / 2 - 50);

	_mvSpd = 16.0f;

	_hitX = _hitY = 20.0f;
	_hitW = _hitH = 80.0f;

	// �Ə�������MLS��������BGM�̍Đ����g��������������(�X���[�Đ��ɂ���)
	SetFrequencySoundMem(23000, gSound._bgm["boss"]);
}

/*
 * �t���[�������F�v�Z
 */
void Reticle::Process(){

	// �J�����̏�Ԏ擾
	Camera::STATE camState = Camera::GetInstance()->GetCameraState();

	// ��ʃT�C�Y�擾
	int dispSizeW = ApplicationMain::GetInstance()->DispSizeW();
	int dispSizeH = ApplicationMain::GetInstance()->DispSizeH();

	// �A�i���O�X�e�B�b�N�Ή�
	DINPUT_JOYSTATE dinput;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &dinput);
	
	// ���A�i���O�X�e�B�b�N���W
	float lx, ly;   
	lx = static_cast<float>(dinput.X);
	ly = static_cast<float>(dinput.Y);

	// ���A�i���O�X�e�B�b�N��|�����Ƃ��̍ŏ��l
	float analogMin = 0.3f;

	// �ړ����������߂�
	float length = sqrt(lx * lx + ly * ly);;
	float rad = atan2(ly, lx);
	VECTOR vec = { 0.0f,0.0f,0.0f };

	// �ړ�����
	if (length < ANALOG_MIN) {
		length = 0.0f;
	}
	else {
		length = _mvSpd;;
	}

	// vec��rad����]������
	vec.x = cos(rad) * length;
	vec.y = sin(rad) * length;

	// vec�̕��ړ�
	_scrnPos = VAdd(_scrnPos, vec);

	// ��ʊO�ɉ摜���o��̂�h�~
	if (_scrnPos.x < 0) { _scrnPos.x = 0; }
	if (_scrnPos.x + 100.0f > dispSizeW) { _scrnPos.x = static_cast<float>(dispSizeW - 100); }
	if (_scrnPos.y < 0.0f) { _scrnPos.y = 0.0f; }
	if (_scrnPos.y + 100.0f > dispSizeH) { _scrnPos.y = static_cast<float>(dispSizeH - 100); }

	// �J�����̏�Ԃ��}���`���b�N�I���V�X�e���ł͂Ȃ��Ȃ�
	if (camState != Camera::STATE::MLS_LOCK){
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		modeGame->_objServer.Del(this);
	}
}

/*
 * �t���[�������F�`��
 */
void Reticle::Render(){

	DrawGraph(static_cast<int>(_scrnPos.x), static_cast<int>(_scrnPos.y), _cg, TRUE);
}