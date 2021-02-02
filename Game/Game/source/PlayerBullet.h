#pragma once
#include "appframe.h"
#include <string>
#include <vector>

class PlayerBullet : public ObjectBase {
public:
	PlayerBullet();
	~PlayerBullet();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::PLAYER_BULLET; }

	void Initialize();
	void Process();
	void Render();

	void SetShotAngle(float shotAngle) { _shotAngle = shotAngle; }

	int		_effectResourceHandle;		// �G�t�F�N�g�t�@�C�������[�h����n���h��
	int		_playingEffectHandle;		// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������
private:
	float  _shotAngle;    // �e�𔭎˂���p�x
	bool   _shotFlag;     // ���˃t���O

	static constexpr float ADJ_DEG = 90.0f;  // �p�x(�e�̌���)���ꕪ����
};