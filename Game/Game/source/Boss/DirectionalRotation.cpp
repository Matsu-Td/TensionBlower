/** 
 * @file   DirectionalRotation.cpp
 * @brief  ボス正面方向回転処理
 * 
 * @author matsuo tadahiko
 * @date   2021/04/07
 */

#include "Boss.h"
#include "../Player/Player.h"

using namespace tensionblower::boss;

/*
 * ボス正面方向回転処理
 */
void Boss::DirectionalRotation(float rotSpdChange) {

	// プレイヤーの位置情報取得
	VECTOR plPos = player::Player::GetInstance()->GetPos();

	// ボスのフォワードベクトル
	VECTOR forward = { cos(_angle),0.0f,sin(_angle) };

	// プレイヤーに向かうベクトル
	VECTOR dis = VSub(plPos, _vPos);
	// 単位ベクトル化
	dis = VNorm(dis);

	// 外積でプレイヤーの位置を左右判定し、ボスの向きを回転させる
	_cross = VCross(forward, dis);

	if (_cross.y > 0.0f) {
		_angle += ROT_SPD * rotSpdChange;
	}
	else if (_cross.y < 0.0f) {
		_angle -= ROT_SPD * rotSpdChange;
	}
	_vDir = { cos(_angle),0.0f,sin(_angle) };
}