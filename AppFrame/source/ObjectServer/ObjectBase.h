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
	int	_cut;		   // ����J�E���^
	int	_cg;		   // �摜
	int _mh;           // ���f���n���h��
	int _attachIndex;  // �A�j���[�V�������A�^�b�`
	float _totalTime;  // �A�j���[�V�������Đ�����
	float _playTime;   // �A�j���[�V�����Đ�����

	VECTOR _vPos;      // �ʒu
	VECTOR _vDir;      // ����

	float _vx, _vz;
	float _angle;
	float _mvSpd;        // �ړ����x
	float _r;            // ���a(�����蔻��p)
};

