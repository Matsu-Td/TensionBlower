
#include "Reticle.h"
#include "ApplicationMain.h"
#include "Camera.h"
#include "ModeGame.h"

Reticle::Reticle()
{
	_cg = ResourceServer::LoadGraph("res/ui/mls_reticle.png");
	Initialize();
}

Reticle::~Reticle()
{

}

void Reticle::Initialize()
{
	_scrnPos.x = ApplicationMain::GetInstance()->DispSizeW() / 2 - 50;
	_scrnPos.y = ApplicationMain::GetInstance()->DispSizeH() / 2 - 50;
	_mvSpd = 16.0f;
	_hitX = _hitY = 20.0f;
	_hitW = _hitH = 80.0f;
}

void Reticle::Process()
{

	int camState = Camera::GetInstance()->GetCameraState();

	DINPUT_JOYSTATE dinput;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &dinput);
	float lx, ly;
	lx = static_cast<float>(dinput.X);
	ly = static_cast<float>(dinput.Y);
	int dispSizeW = ApplicationMain::GetInstance()->DispSizeW();  // 画面横幅サイズ
	int dispSizeH = ApplicationMain::GetInstance()->DispSizeH();  // 画面縦幅サイズ
	float analogMin = 0.3f;

	if (lx < analogMin) { _scrnPos.x -= _mvSpd; }
	if (lx > -analogMin) { _scrnPos.x += _mvSpd; }
	if (ly < analogMin) { _scrnPos.y -= _mvSpd; }
	if (ly > -analogMin) { _scrnPos.y += _mvSpd; }

	if (_scrnPos.x < 0) { _scrnPos.x = 0; }
	if (_scrnPos.x + 100 > dispSizeW) { _scrnPos.x = dispSizeW - 100; }
	if (_scrnPos.y < 0) { _scrnPos.y = 0; }
	if (_scrnPos.y + 100 > dispSizeH) { _scrnPos.y = dispSizeH - 100; }

	if (camState != Camera::STATE::MLS_LOCK){
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		modeGame->_objServer.Del(this);
	}
}

void Reticle::Render()
{
	DrawGraph(_scrnPos.x, _scrnPos.y, _cg, TRUE); 
	DrawBox(_scrnPos.x + _hitX, _scrnPos.y + _hitY, _scrnPos.x + _hitW, _scrnPos.y + _hitH, GetColor(255, 0, 0), TRUE);
}