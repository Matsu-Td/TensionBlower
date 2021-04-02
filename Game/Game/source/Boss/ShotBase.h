/**
 * @file   ShotBase.h
 * @brief  弾幕系処理クラスの基底クラス
 * 
 * @author matsuo tadahiko
 * @date   2021/03/22
 */

#pragma once

#include "appframe.h"
#include "../Object/ObjectBase.h"
#include "BossDamage.h"

/**
 * 弾幕系処理クラスの基底クラス
 */
class ShotBase : public ObjectBase{
public:
	/**
	 * 初期化
	 */
	virtual void Initialize();

	/**
	 * フレーム処理：計算
	 */
	virtual void Process();

	/**
	 * フレーム処理：描画
	 */
	virtual void Render();

	/**
	 * 弾の移動処理
	 */
	virtual void Move();

	/**
	 * 当たり判定
	 */
	virtual void Collision();


protected:
	int _cg[2];            // 画像
	VECTOR _vTarg;         // 標的の位置
	float _shotAngle;      // 弾幕発生角度
	float _shotSpd;        // 弾の移動速度
	float _upSpd;          // 上昇カウント
	int _shotCnt;          // ショットカウント
	int _mlsCnt;           // マルチロックオンシステム中のカウント
	bool _camStateMLS;     // カメラ状態:マルチロックオンシステム発動中か
	bool _canLockFlag;     // MLSでロック可能距離となる
	bool _repelFlag;       // 弾かれたか(true:弾かれた, false:弾かれてない)

	enum class STATE {
		NORMAL,   // 通常
		UP,       // 上昇
		STOP,     // 停止
		SNIPER,   // 狙撃
		REPEL,    // 弾き返された状態
	};
	STATE _state; // 状態

	const float REPEL_SPD = 3.0f; // 弾き返された後の弾の移動速度
	const float MLS_SPD = 0.01f;  // マルチロックオンシステム中の速度計算(通常の1/100に)

private:
	std::unique_ptr<BossDamage> _bossDamageCall;  	// ボスへのダメージ処理呼び出し
};