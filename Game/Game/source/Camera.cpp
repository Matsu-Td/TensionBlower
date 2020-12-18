#include "Camera.h"
#include "ApplicationMain.h"
#include "Player.h"
#include "Boss.h"

Camera* Camera::_pInstance = NULL;
#define TEST 0

Camera::Camera()
{
	_pInstance = this;
	Initialize();
}

Camera::~Camera()
{

}

void Camera::Initialize()
{
	_vPos = VGet(0.f, 10.f, -140.f);
	_state = STATE::NORMAL;
}

void Camera::Process()
{
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	VECTOR plPos = Player::GetInstance()->GetPos();   // プレイヤー位置情報取得
	VECTOR bsPos = Boss::GetInstance()->GetPos();   // ボス位置情報取得

	// アナログスティック対応
	DINPUT_JOYSTATE dinput;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &dinput);
	float lx, ly, rx, ry;           // 左右アナログスティックの座標
	float analogMin = 0.3f; 
	lx = static_cast<float>(dinput.X);
	ly = static_cast<float>(dinput.Y);
	rx = static_cast<float>(dinput.Rx);
	ry = static_cast<float>(dinput.Ry);




	// カメラ移動制限
#if TEST
	if (_vPos.y >= 20.f) {
		_vPos.y = 20.f;
	}
	if (_vPos.y < 2.5f) {
		_vPos.y = 2.5f;
	}
#endif

/*	if (trg & PAD_INPUT_3) {   // カメラの位置を初期位置に戻す
		Initialize();
	}
*/
	if (key & PAD_INPUT_8) {	// W
		// カメラ位置（注目位置もXZスライド）
			float sx = _vPos.x - _vTarg.x;
			float sz = _vPos.z - _vTarg.z;
			float camrad = atan2(sz, sx);

			// 移動方向を決める(左スティック)
			{
				VECTOR vec = { 0,0,0 };
				float mvSpd = 1.f;
				float length = sqrt(lx * lx + ly * ly);
				float rad = atan2(lx, ly);
				if (length < analogMin) {
					// 入力が小さかったら動かなかったことにする
					length = 0.f;
				}
				else {
					length = mvSpd;
				}
				// vをrad分回転させる
				vec.x = cos(rad + camrad) * length;
				vec.z = sin(rad + camrad) * length;

				// vecの分移動
				_vPos = VAdd(_vPos, vec);
				_vTarg = VAdd(_vTarg, vec);
			}

			// 距離、ターゲットの高さ変更（右スティック）
			{
				float sx = _vPos.x - _vTarg.x;
				float sz = _vPos.z - _vTarg.z;
				float rad = atan2(sz, sx);
				float length = sqrt(sz * sz + sx * sx);
				if (rx < -analogMin) { length -= 0.5f; }
				if (rx > analogMin) { length += 0.5f; }
				_vPos.x = _vTarg.x + cos(rad) * length;
				_vPos.z = _vTarg.z + sin(rad) * length;

				// Y位置
				if (ry > analogMin) { _vTarg.y -= 0.5f; }
				if (ry < -analogMin) { _vTarg.y += 0.5f; }
			}
		}
	else {

		switch(_state){
		case STATE::NORMAL:
		{
			_vTarg = VGet(plPos.x, plPos.y + 3.5f, plPos.z);
			float sx = _vPos.x - _vTarg.x;
			float sz = _vPos.z - _vTarg.z;
			float camrad = atan2(sz, sx);

			/*
			float sx = _vPos.x - _vTarg.x;
			float sz = _vPos.z - _vTarg.z;
			float camrad = atan2(sz, sx);
			*/
			// 移動方向を決める
			VECTOR vec = { 0,0,0 };
			float mvSpd = 0.3f;
			// アナログ左スティック用
			float length = sqrt(lx * lx + ly * ly);
			float rad = atan2(lx, ly);
			if (length < analogMin) {
				// 入力が小さかったら動かなかったことにする
				length = 0.f;
			}
			else {
				length = mvSpd;
			}

			// vをrad分回転させる
			vec.x = cos(rad + camrad) * length;
			vec.z = sin(rad + camrad) * length;

			_vPos = VAdd(_vPos, vec);
			_vTarg = VAdd(_vTarg, vec);

			// カメラ操作を行う（右スティック）
			{
				// Y軸回転
				float sx = _vPos.x - _vTarg.x;
				float sz = _vPos.z - _vTarg.z;
				float rad = atan2(sz, sx);
				float length = sqrt(sz * sz + sx * sx);
				if (rx > analogMin) { rad -= 0.05f; }
				if (rx < -analogMin) { rad += 0.05f; }
				_vPos.x = _vTarg.x + cos(rad) * length;
				_vPos.z = _vTarg.z + sin(rad) * length;

				// Y位置
				if (ry > analogMin) { _vPos.y -= 0.5f; }
				if (ry < -analogMin) { _vPos.y += 0.5f; }
			}
			break;
		}
		case STATE::LOCK:
			break;
		default:
			break;

		}
	}


	// 敵へのカメラロックオンオフ切替
	if (trg & PAD_INPUT_10) {           // 右アナログスティック押し込み
		if (_state == STATE::NORMAL) {
			_state = STATE::LOCK;
		}
		else {
			_state = STATE::NORMAL;
		}
	}

}


void Camera::Render()
{
	SetCameraPositionAndTarget_UpVecY(_vPos, _vTarg);
	SetCameraNearFar(0.1f, 5000.f);

#ifdef _DEBUG
	// カメラターゲットを中心に短い線を引く
	{
		float linelength = 2.f;
		VECTOR vec = _vTarg;
		DrawLine3D(VAdd(vec, VGet(-linelength, 0, 0)), VAdd(vec, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
		DrawLine3D(VAdd(vec, VGet(0, -linelength, 0)), VAdd(vec, VGet(0, linelength, 0)), GetColor(0, 255, 0));
		DrawLine3D(VAdd(vec, VGet(0, 0, -linelength)), VAdd(vec, VGet(0, 0, linelength)), GetColor(0, 0, 255));
	}
	{
		int x = 0, y = 0, size = 16;
		SetFontSize(size);
		DrawFormatString(x, y, GetColor(255, 0, 0), "Camera:"); y += size;
		DrawFormatString(x, y, GetColor(255, 0, 0), "  target = (%5.2f, %5.2f, %5.2f)", _vTarg.x, _vTarg.y, _vTarg.z); y += size;
		DrawFormatString(x, y, GetColor(255, 0, 0), "  pos    = (%5.2f, %5.2f, %5.2f)", _vPos.x, _vPos.y, _vPos.z); y += size;
		float disX = _vPos.x - _vTarg.x;
		float disZ = _vPos.z - _vTarg.z;
		float rLength = sqrt(disZ * disZ + disX * disX);
		float rad = atan2(disZ, disX);
		float deg = RAD2DEG(rad);
		DrawFormatString(x, y, GetColor(255, 0, 0), "  len = %5.2f, rad = %5.2f, deg = %5.2f", rLength, rad, deg); y += size;
	}
#endif
}
