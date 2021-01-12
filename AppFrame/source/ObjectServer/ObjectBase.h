#pragma once
#include "DxLib.h"

class ObjectBase {
public:
	ObjectBase();
	~ObjectBase();

	enum class OBJECTTYPE {
		PLAYER,
		PLAYER_BULLET,
		BOSS,
		BOSS_BULLET,
		CAMERA,
	};
	virtual OBJECTTYPE	GetType() = 0;

	virtual void Init();
	virtual void Process();
	virtual void Render();

//	virtual bool IsHit(ObjectBase& obj);
	virtual void Damage() {}

	void SetPos(VECTOR vPos) { _vPos = vPos; }
	VECTOR GetPos()const { return _vPos; }
	VECTOR GetDir()const { return _vDir; }

protected:
	int	_cut;		   // 動作カウンタ
	int	_cg;		   // 画像
	int _mh;           // モデルハンドル
	int _attachIndex;  // アニメーションをアタッチ
	float _totalTime;  // アニメーション総再生時間
	float _playTime;   // アニメーション再生時間

	VECTOR _vPos;      // 位置
	VECTOR _vDir;      // 向き

	float _vx, _vz;
	float _angle;
	float _mvSpd;        // 移動速度
	float _r;            // 半径(当たり判定用)
};

