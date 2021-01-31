#pragma once
#include "appframe.h"
#include <list>

class BossBullet : public ObjectBase{
public:
	BossBullet();
	virtual ~BossBullet();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS_BULLET; }
	void Initialize();
	void Process();
	void Render();
	void Shot();

	void SetAngle(float shotAngle) { _shotAngle = shotAngle; }
	void SetShotSpd(float shotSpd) { _shotSpd = shotSpd; }

private:
	int _cg[2];
	float _shotSpd;
	int _shotCnt;
	int _mlsCnt;
	int _pattern;
	float _shotAngle;
	float _setAngle;
	float shotInterval;
	bool _camStateMLS;
	bool _canLockFlag;      // MLSÇ≈ÉçÉbÉNâ¬î\ãóó£Ç∆Ç»ÇÈ
	bool _repelFlag;    // íeÇ©ÇÍÇΩÇ©(true:íeÇ©ÇÍÇΩ, false:íeÇ©ÇÍÇƒÇ»Ç¢)
	float _bulletDir;   // -1.0fÇ≈MLSÇ…ÇÊÇÈíeÇÃÇÕÇ∂Ç´ï‘Çµ

	static constexpr float NOR_SPD = 1.0f;
};