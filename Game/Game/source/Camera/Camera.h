/**
 * @file   Camera.h
 * @brief  �J�����N���X
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#pragma once

#include "appframe.h"

/**
 * @brief �J�����N���X
 */
class Camera{
public:
	Camera();
	~Camera();

	/**
	 * @brief ������
	 */
	void Initialize();

	/**
	 * @brief �t���[�������F�v�Z
	 */
	void Process();

	/**
	 * @brief �t���[�������F�`��
	 */
	void Render();

	/**
	 * �C���X�^���X���擾
	 * @return Camera�̃C���X�^���X
	 */
	static Camera* GetInstance() { return _pInstance; }

	/**
	 * @brief ���W�擾
	 * @return ���W
	 */
	VECTOR GetPos() const { return _vPos; }

	/**
	 * @brief  �^�[�Q�b�g���W�擾
	 * @return �^�[�Q�b�g���W
	 */
	VECTOR GetTarg() const { return _vTarg; }

	/**
	 * @brief �J�����̏��
	 */
	enum class STATE { 
		NORMAL,    // �G�^�[�Q�b�g���b�N���(�f�t�H���g)
		MLS_LOCK,  // �}���`���b�N�V�X�e���������(FPS���_)
	};
	STATE _state;  // �J�������

	/**
	 * @brief  �J�����̏�Ԃ��擾
	 * @return �J�����̏��
	 */
	STATE GetCameraState() const { return _state; }

	static Camera* _pInstance;

private:
	VECTOR _vPos;    // �ʒu
	VECTOR _oldvPos; // �����O�̈ʒu
	VECTOR _vTarg;   // �����_
	float _angleH;   // �����p�x
	float _angleV;   // �����p�x

	STATE _oldState; // �����O�̏��

	struct LOCK_ON { // �\���́F���b�N�I�����
		int x, y;  // �X�N���[�����W
		int cg;    // �摜
	};
	LOCK_ON _lockOn;

	const float NearClip = 0.1f;
	const float FarClip  = 5000.0f;
};
