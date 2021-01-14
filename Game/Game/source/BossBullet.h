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
/* 
	static BossBullet* GetInstance() { return _pInstance; }
	VECTOR GetPos() const { return _vPos; }
	VECTOR GetScrnPos() const { return _scrnPos; }

	static BossBullet* _pInstance;
*/
private:
	int _cg[2];
	int _shotCnt;
	int _mlsCnt;
	int _pattern;
	float _shotAngle;
	float _setAngle;
	float shotInterval;
	bool _camStateMLS;
	bool _canLockFlag;      // MLSでロック可能距離となる
	bool _repelFlag;    // 弾かれたか(true:弾かれた, false:弾かれてない)
	float _bulletDir;   // -1.0fでMLSによる弾のはじき返し

	static constexpr float NOR_SPD = 1.0f;
};