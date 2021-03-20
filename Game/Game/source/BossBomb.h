/**
 * @file   BossBomb.h
 * @brief  ボスのボム攻撃処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/03
 */

#pragma once

#include "appframe.h"
#include "ObjectBase.h"

class BossBomb : public ObjectBase {
public:
	/**
	 * @brief ボム生成
	 * @param pos ボムの発生位置
	 */
	BossBomb(VECTOR pos);
	~BossBomb();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS_BOMB; }

	/**
	 * @brief 初期化
	 */
	void Initialize();

	/**
	 * @brief フレーム処理：計算
	 */
	void Process();

	/**
	 * @brief フレーム処理：描画
	 */
	void Render();

private:
	int _cg[2];            // 画像
	VECTOR _vTarg;         // 標的の位置(プレイヤーの位置)
	float _shotSpd;        // 弾の移動速度
	float _upSpd;          // 上昇カウント
	int _shotCnt;          // ショットカウント
	int _mlsCnt;           // マルチロックオンシステム中のカウント
	bool _camStateMLS;     // カメラ状態:マルチロックオンシステム発動中か
	bool _canLockFlag;     // MLSでロック可能距離となる
	bool _repelFlag;       // 弾かれたか(true:弾かれた, false:弾かれてない)
	
	enum class STATE {
		UP,       // 上昇
		STOP,     // 停止
		SNIPER,   // 狙撃
		REPEL,
	};
	STATE _state;

	static constexpr int UP_CNT = 24;    // 上昇カウント
	static constexpr int STOP_CNT = 24;  // 停止カウント
	static constexpr float MLS_SPD = 0.01f; // マルチロックオンシステム中の速度計算(通常の1/100に)
};
