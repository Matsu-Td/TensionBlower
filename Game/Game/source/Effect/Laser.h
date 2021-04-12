/**
 * @file   Laser.h
 * @brief  ボスのレーザー攻撃クラス
 * 
 * @author matsuo tadahiko
 * @date   2021/02/14
 */

#pragma once

#include "appframe.h"
#include "../Object/ObjectBase.h"

/**
 * @brief ボスのレーザー攻撃クラス
 */
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

	OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::LASER; }

	/**
	 * @brief 初期化
	 */
	void Initialize() override;

	/**
	 * @brief フレーム処理：計算
	 */
	void Process() override;

	/**
	 * @brief フレーム計算：描画
	 */
	void Render() override;

private:
	/**
	 * @brief レーザーを削除する
	 */
	void Deletion();

	int	  _effectHandle;  // エフェクトファイルをロードするハンドル
	int	  _playingHandle; // ロードしたエフェクトファイルから、エフェクトを生成したもの

	int   _effectCnt; // エフェクト再生カウント
	int   _mlsCnt;    // マルチロックオンシステム発動中のカウント
	float _roteAngle; // 回転角度
	float _roteSpd;   // 回転速度
	float _radius;    // ボスからの半径

	const float MLS_SPD      = 0.01f;  // マルチロックオンシステム中の速度計算(通常の1/100に)
	const float LASER_LENGTH = 125.0f; // レーザーの全長
};