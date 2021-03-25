/**
 * @file  ObjectBase.h
 * @brief �I�u�W�F�N�g���N���X
 *
 * @date 2021/01/15
 */

#pragma once

#include "appframe.h"
#include <iostream>

class ObjectBase {
public:
	ObjectBase();
	virtual ~ObjectBase();

	/**
	 * �I�u�W�F�N�g�̎�ނ��`
	 */
	enum class OBJECTTYPE {
		PLAYER,        // �v���C���[
		BOSS,          // �{�X
		BOSS_BULLET,   // �{�X�̒e��
		BOSS_BOMB,     // �{�X�̃{��
		STAGE,         // �X�e�[�W
		RETICLE,       // �Ə�
		LASER,         // ���[�U�[�G�t�F�N�g
		EXPLOSION,     // �����G�t�F�N�g
		DESTRUCTION,   // �{�X�j��A�����G�t�F�N�g
		HIT_EFFECT,    // �ߐڍU���̃q�b�g�G�t�F�N�g
	};

	/**
	 * �I�u�W�F�N�g�̎�ނ�Ԃ�
	 */
	virtual OBJECTTYPE	GetType() = 0;

	/**
	 * ������
	 */
	virtual void Initialize();

	/**
	 * �t���[�������F�v�Z
	 */
	virtual void Process();

	/**
	 * �t���[�������F�`��
	 */
	virtual void Render();

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

	/**
	 * ���ςł̓����蔻��
	 */
	virtual bool IsDot(ObjectBase& obj);

	/**
	 * �~�ʂƋ��̓����蔻��
	 */
	virtual bool IsHitArc_Sphere(ObjectBase& obj);

	/**
	 * @brief ���f���̉e��`��
	 * @param modelScale ���f���̊g�嗦(�f�t�H���g�� 1.0f)
	 */
	void ShadowRender(float modelScale = 1.0f);

	/**
	 * ���W��ݒ肷��
	 */
	void SetPos(VECTOR vPos) { _vPos = vPos; }

	/**
	 * ���W���擾����
	 */
	VECTOR GetPos()const { return _vPos; }

	/**
	 * �������擾����
	 */
	VECTOR GetDir()const { return _vDir; }

	bool _hitFlag;                         // �U�������蔻�蔭���t���O
	MV1_COLL_RESULT_POLY_DIM _hitPolyDim;  // �����蔻�茋��(�\����)

	float _r;           // ���a(�����蔻��p)

protected:
	int _mh;           // ���f���n���h��
	int _shadowModel;  // �e�p���f���n���h��
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
};