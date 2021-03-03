/**
 * @file   BossBomb.h
 * @brief  ボスのボム攻撃処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/03
 */

#pragma once

#include "appframe.h"

class BossBomb : public ObjectBase {
	BossBomb(VECTOR pos);
	~BossBomb();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS_BULLET; }

	void Initialize();
	void Process();
	void Render();

	VECTOR _vTarg;
	float _shotSpd;         // 弾の移動速度
	float _upSpd;
	int _shotCnt;           // 
	int _mlsCnt;
	float _shotAngle;       // 弾幕発生角度
	float _setAngle;        // 弾幕発生角度設定
	float shotInterval;     // 弾幕発生インターバル
	bool _camStateMLS;      // カメラ状態:マルチロックオンシステム発動中か
	bool _canLockFlag;      // MLSでロック可能距離となる
	bool _repelFlag;        // 弾かれたか(true:弾かれた, false:弾かれてない)
	float _bulletDir;       // -1.0fでMLSによる弾のはじき返し

	enum STATE {
		UP,
		STOP,
		ATTACK,
	};
	STATE _state;
};
