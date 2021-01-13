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

	/**
     * ���f���ƃX�e�[�W�̓����蔻��
     * @param obj �I�u�W�F�N�g�T�[�o�[�ɓo�^���Ă���I�u�W�F�N�g�N���X
     * @param r �J�v�Z���̔��a
     */
	virtual bool IsHitStage(ObjectBase& obj, float r);

	/**
	* �J�v�Z�����m�̓����蔻��
	* @param obj �I�u�W�F�N�g�T�[�o�[�ɓo�^���Ă���I�u�W�F�N�g�N���X
	* @param r �J�v�Z���̔��a
	*/
	virtual bool IsHitLineSegment(ObjectBase& obj, float r);
	virtual void Damage() {}

	void SetPos(VECTOR vPos) { _vPos = vPos; }
	VECTOR GetPos()const { return _vPos; }
	VECTOR GetDir()const { return _vDir; }

	int _mh;           // ���f���n���h��
	MV1_COLL_RESULT_POLY_DIM _hitPolyDim;
protected:
	int	_cut;		   // ����J�E���^
	int	_cg;		   // �摜

	int _attachIndex;  // �A�j���[�V�������A�^�b�`
	float _totalTime;  // �A�j���[�V�������Đ�����
	float _playTime;   // �A�j���[�V�����Đ�����

	VECTOR _vPos;      // �ʒu
	VECTOR _vDir;      // ����
	VECTOR _scrnPos;
	VECTOR _capsulePos1, _capsulePos2;
	VECTOR _hitPos1,_hitPos2;

	float _vx, _vz;
	float _angle;
	float _mvSpd;        // �ړ����x
	float _r;            // ���a(�����蔻��p)
};

