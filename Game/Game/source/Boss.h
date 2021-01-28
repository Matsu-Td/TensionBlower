#pragma once
#include "appframe.h"
#include "BossBullet.h"
#define  CHARA_DATA (modeGame->_charaData)

class Boss : public ObjectBase{
public:
	Boss();
	~Boss();
	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS; }
	void Initialize();
	void Process();
	void Render();
	void Damage();
	void AttackDamage();

	/**
	* �_�E������
	*/
	void StateDown();

	/**
	* �e���p�^�[��1����
	*/
	void ShotPattern1();

	static Boss* GetInstance() { return _pInstance; }
//	VECTOR GetPos() const { return _vPos; }

	static Boss* _pInstance;

	// �v���C���[�N���X�Ŏg�p
	int _bulletNum;      // �_�E�����O�ɏo�����Ă����e�̐��J�E���g
	bool _mlsDownFlag;   // MLS�Œe���Ԃ��ꂽ�e�Ń_�E�������true

private:
	int _shotCnt;
	int _mlsCnt;
	float _shotAngle;
	float shotInterval;

	int _hitpoint;
	int _shield;
	
	bool _stateDown;
	int _downTime;

	int _gameClearCnt;
	bool _gameClearFlag;
	static constexpr int MAX_HP = 5000;
	static constexpr int MAX_SHIELD = 1000;
};
