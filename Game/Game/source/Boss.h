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

	void FhaseChange();
	void ShotPatternSwitch();

	/**
	* �_�E������
	*/
	void StateDown();

	/**
	* �e���p�^�[������
	*/
	void ShotPattern1and2();
//	void ShotPattern2();
	void ShotPattern3();
	void ShotPattern4_1();
	void ShotPattern4_2();
	void ShotPattern5();
	void ShotPattern6();

	static Boss* GetInstance() { return _pInstance; }
//	VECTOR GetPos() const { return _vPos; }

	static Boss* _pInstance;

	// �v���C���[�N���X�Ŏg�p
	int _bulletNum;      // �_�E�����O�ɏo�����Ă����e�̐��J�E���g
	bool _mlsDownFlag;   // MLS�Œe���Ԃ��ꂽ�e�Ń_�E�������true

private:
	int _shotCnt;
	int _mlsCnt;
	int _reverseCnt;
	float _shotAngle;
	float _shotAngle1;
	float _setRotAngle;
	float shotInterval;
	int _shotPattern;
	int _phase;

	int _hitpoint;
	int _shield;
	float _a;    // �f�o�b�O�m�F�p
	bool _stateDown;
	int _downTime;

	int _gameClearCnt;
	bool _gameClearFlag;
	static constexpr int MAX_HP = 5000;
	static constexpr int MAX_SHIELD = 1000;
};
