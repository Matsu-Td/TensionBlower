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
	void ShotPattern1();

	static Boss* GetInstance() { return _pInstance; }
//	VECTOR GetPos() const { return _vPos; }

	static Boss* _pInstance;

private:
	int _shotCnt;
	int _mlsCnt;
	float _shotAngle;
	float shotInterval;

	int _hitpoint;
	int _shield;

	static constexpr int MAX_HP = 5000;
	static constexpr int MAX_SHIELD = 1000;
};
