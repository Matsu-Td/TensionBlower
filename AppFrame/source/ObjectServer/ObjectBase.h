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
		STAGE,
	};
	virtual OBJECTTYPE	GetType() = 0;

	virtual void Init();
	virtual void Process();
	virtual void Render();

	virtual bool IsHitStage(ObjectBase& obj);
	virtual void Damage() {}

	void SetPos(VECTOR vPos) { _vPos = vPos; }
	VECTOR GetPos()const { return _vPos; }
	VECTOR GetDir()const { return _vDir; }

	int _mh;           // モデルハンドル

protected:
	int	_cut;		   // 動作カウンタ
	int	_cg;		   // 画像

	int _attachIndex;  // アニメーションをアタッチ
	float _totalTime;  // アニメーション総再生時間
	float _playTime;   // アニメーション再生時間

	VECTOR _vPos;      // 位置
	VECTOR _vDir;      // 向き
	VECTOR _scrnPos;
	VECTOR _capsulePos1, _capsulePos2;
	VECTOR _hitPos1,_hitPos2;

	float _vx, _vz;
	float _angle;
	float _mvSpd;        // 移動速度
	float _r;            // 半径(当たり判定用)
};

