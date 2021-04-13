/**
 * @file   Reticle.h
 * @brief  プレイヤー照準処理
 * 
 * @author matsuo tadahiko
 * @date   2021/01/14
 */

#pragma once

#include "appframe.h"
#include "../Object/ObjectBase.h"

/**
 * @brief プレイヤー照準処理
 */
class Reticle : public ObjectBase{
public:
	Reticle();
	~Reticle();

	OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::RETICLE; }

	/**
	 * @brief 初期化
	 */
	void Initialize() override;

	/**
	 * @brief フレーム処理：計算
	 */
	void Process() override;

	/**
	 * @brief フレーム処理：描画
	 */
	void Render() override;

private:
	/**
	 * @brief 移動処理
	 */
	void Move();

	/**
	 * @brief 画像が画面外に出るのを防ぐ
	 */
	void PreventOffScreen();

	/**
	 * @brief 削除処理
	 */
	void Deletion();
};
