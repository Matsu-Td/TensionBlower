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
	* ダウン処理
	*/
	void StateDown();

	/**
	* 弾幕パターン1処理
	*/
	void ShotPattern1();

	static Boss* GetInstance() { return _pInstance; }
//	VECTOR GetPos() const { return _vPos; }

	static Boss* _pInstance;

	// プレイヤークラスで使用
	int _bulletNum;      // ダウン直前に出現していた弾の数カウント
	bool _mlsDownFlag;   // MLSで弾き返された弾でダウンするとtrue

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
