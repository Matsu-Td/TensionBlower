/**
 * @file   Laser.h
 * @brief  ボスのレーザー攻撃
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"
#include "ObjectBase.h"

class Laser : public ObjectBase{
public:
	/**
	 * @brief レーザー生成
	 * @param pos     レーザー発射位置
	 * @param radius  ボスからの半径
	 * @param angle   レーザーの発射角度、位置
	 * @param roteSpd レーザーの回転速度
	 */
	Laser(VECTOR pos,float radius, float angle, float roteSpd);
	~Laser();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::LASER; }

	/**
	 * @brief 初期化
	 */
	void Initialize();

	/**
	 * @brief フレーム処理：計算
	 */
	void Process();

	/**
	 * @brief フレーム計算：描画
	 */
	void Render();

private:
	int	  _effectHandle;  // エフェクトファイルをロードするハンドル
	int	  _playingHandle;	// ロードしたエフェクトファイルから、エフェクトを生成したもの

	float _roteAngle; // 回転角度
	float _roteSpd;   // 回転速度
	float _radius;    // ボスからの半径
	int _effectCnt;   // エフェクト再生カウント
	int _mlsCnt;      // マルチロックオンシステム発動中のカウント

	static constexpr float MLS_SPD = 0.01f; // マルチロックオンシステム中の速度計算(通常の1/100に)
};