///**
// * @file   PlayerBullet.h
// * @brief  �v���C���[�ˌ��p�̒e�ړ�����
// * 
// * @author matsuo tadahiko
// * @date   2021/03/01
// */
//
//#pragma once
//
//#include "appframe.h"
//
//class PlayerBullet : public ObjectBase {
//public:
//	PlayerBullet(VECTOR pos, float angle);
//	~PlayerBullet();
//
//	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::PLAYER_BULLET; }
//	/**
//	 * @brief ������
//	 */
//	void Initialize();
//
//	/**
//	 * @brief �t���[�������F�v�Z
//	 */
//	void Process();
//
//	/**
//	 * @brief �t���[�������F�`�� 
//	 */
//	void Render();
//
//	int	_effectHandle;  // �G�t�F�N�g�t�@�C�������[�h����n���h��
//	int	_playingHandle;	// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������
//private:
//	float _shotAngle;    // �e�𔭎˂���p�x
//	bool  _shotFlag;     // ���˃t���O
//
//	static constexpr float ADJ_DEG = 90.0f;  // �p�x(�e�̌���)���ꕪ����
//};