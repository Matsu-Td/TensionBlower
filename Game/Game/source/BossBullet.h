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
	void ShotStart();

	void SetAngle(float shotAngle) { _shotAngle = shotAngle; }
/* 
	static BossBullet* GetInstance() { return _pInstance; }
	VECTOR GetPos() const { return _vPos; }
	VECTOR GetScrnPos() const { return _scrnPos; }

	static BossBullet* _pInstance;
*/
private:
	int _mhMap;
	int _mhPl;
	int _shotCnt;
	int _mlsCnt;
	int _pattern;
	float _shotAngle;
	float _setAngle;
	float shotInterval;
	bool _camModeMLS;
//	MV1_COLL_RESULT_POLY_DIM _hitPolyDimStg;
//	MV1_COLL_RESULT_POLY_DIM _hitPolyDimPl;

	static constexpr float NOR_SPD = 1.f;
};