#pragma once
#include "DxLib.h"
#include <iostream>


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
		RETICLE,
		LASER,
	};
	virtual OBJECTTYPE	GetType() = 0;

	virtual void Init();
	virtual void Process();
	virtual void Render();
	virtual void Damage() {}
	virtual void AttackDamage(){}

	/**
     * ���f���ƃX�e�[�W�̓����蔻��
     * @param r �J�v�Z���̔��a
     */
	virtual bool IsHitStage(ObjectBase& obj, float r);

	/**
	* �J�v�Z�����m�̓����蔻��
	* @param r �J�v�Z���̔��a
	*/
	virtual bool IsHitLineSegment(ObjectBase& obj, float r);

	/**
    * �X�N���[�����W��̓����蔻��
    */
	virtual bool IsHitScrnPos(ObjectBase& obj);

	virtual bool IsDot(ObjectBase& obj);

	virtual bool IsHitArc_Sphere(ObjectBase& obj);
	/**
	* �ۑ�@���H2///////////////////////////////////////////////////
	*/
	//ObjectBase(ObjectBase&& obj) noexcept;
	//ObjectBase& operator=(ObjectBase&& obj) noexcept;
	/*
	template<typename T>
	void moveSwap(T& a, T& b) {
		T tmp = std::move(a);
		a = std::move(b);
		b = std::move(tmp);
		
	}*/

	void SetPos(VECTOR vPos) { _vPos = vPos; }
	///////////////////////////////////////////////////////////////


	VECTOR GetPos()const { return _vPos; }
	VECTOR GetDir()const { return _vDir; }
	bool _hitFlag;       // �U�������蔻�蔭���t���O
	MV1_COLL_RESULT_POLY_DIM _hitPolyDim;
protected:
	int _mh;           // ���f���n���h��
	int	_cg;		   // �摜
	int	_cut;		   // ����J�E���^
	int _attachIndex;  // �A�j���[�V�������A�^�b�`
	float _totalTime;  // �A�j���[�V�������Đ�����
	float _playTime;   // �A�j���[�V�����Đ�����

	VECTOR _vPos;      // �ʒu
	VECTOR _oldPos;    // �ړ������O�̈ʒu�ۑ�
	VECTOR _vDir;      // ����
	VECTOR _scrnPos;   // �X�N���[�����W
	VECTOR _capsulePos1, _capsulePos2; // �����蔻��p�J�v�Z�����`������2�_�̍��W

	float _hitX, _hitY;  // 2D�����蔻��p(�摜����̍��W)
	float _hitW, _hitH;  // 2D�����蔻��p(�摜�E��̍��W)

	float _angle;        // �p�x(��]�A����)
	float _mvSpd;        // �ړ����x
	float _r;            // ���a(�����蔻��p)

	

};

