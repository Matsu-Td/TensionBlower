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
	* ダウン処理
	*/
	void StateDown();

	/**
	* 弾幕パターン処理
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

	// プレイヤークラスで使用
	int _bulletNum;      // ダウン直前に出現していた弾の数カウント
	bool _mlsDownFlag;   // MLSで弾き返された弾でダウンするとtrue

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
	float _a;    // デバッグ確認用
	bool _stateDown;
	int _downTime;

	int _gameClearCnt;
	bool _gameClearFlag;
	static constexpr int MAX_HP = 5000;
	static constexpr int MAX_SHIELD = 1000;
};
