/**
 * @file   Camera.h
 * @brief  �J�����֘A����
 * 
 * @author matsuo tadahiko
 * @date   2021/03/15
 */

#pragma once

#include "appframe.h"

#define	DEG2RAD(x)			( ((x) / 180.0f ) * DX_PI_F )
#define	RAD2DEG(x)			( ((x) * 180.0f ) / DX_PI_F )

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

	static Camera* GetInstance() { return _pInstance; }

	/**
	 * @brief ���W�擾
	 * 
	 * @return ���W
	 */
	VECTOR GetPos() const { return _vPos; }

	/**
	 * @brief �^�[�Q�b�g���W�擾
	 * 
	 * @return �^�[�Q�b�g���W
	 */
	VECTOR GetTarg() const { return _vTarg; }

	enum class STATE {      // �J�����̏��
		TARG_LOCK_ON, // �G�^�[�Q�b�g���b�N���(�f�t�H���g)
		MLS_LOCK,     // �}���`���b�N�V�X�e���������(FPS���_)
	};
	STATE _state;    // �J�������
	STATE GetCameraState() { return _state; }

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
};
