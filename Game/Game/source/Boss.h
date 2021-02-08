#pragma once

/**
 * @file  Boss.h
 * @brief ボス関連処理
 *
 * @date 2021-02-08
 */

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
	float _height;
	float _upDown;

	int _hitpoint;
	int _shield;
	float _a;    // デバッグ確認用
	bool _stateDown;     // ダウン状態
	int _downTime;       // ダウン時間

	int _gameClearCnt;      // クリアカウント
	bool _gameClearFlag;    // クリアフラグ
};
