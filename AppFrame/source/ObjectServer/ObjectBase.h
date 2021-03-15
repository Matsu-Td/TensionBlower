#pragma once

/**
 * @file ObjectBase.h
 * @brief オブジェクトベース
 *
 * @date 2021-01-15
 */

#include "DxLib.h"
#include <iostream>

class ObjectBase {
public:
	ObjectBase();
	virtual ~ObjectBase();

	enum class OBJECTTYPE {
		PLAYER,        // プレイヤー
		BOSS,          // ボス
		BOSS_BULLET,   // ボスの弾幕
		BOSS_BOMB,     // ボスのボム
		CAMERA,        // カメラ
		STAGE,         // ステージ
		RETICLE,       // 照準
		LASER,         // レーザーエフェクト
		EXPLOSION,     // 爆発エフェクト
		DESTRUCTION,   // ボス破壊、爆発エフェクト
	};
	virtual OBJECTTYPE	GetType() = 0;

	virtual void Init();
	virtual void Process();
	virtual void Render();

	/**
     * モデルとステージの当たり判定
     * @param r カプセルの半径
     */
	virtual bool IsHitStage(ObjectBase& obj, float r);

	/**
	 * カプセル同士の当たり判定
	 * @param r カプセルの半径
	 */
	virtual bool IsHitLineSegment(ObjectBase& obj, float r);

	/**
     * スクリーン座標上の当たり判定
     */
	virtual bool IsHitScrnPos(ObjectBase& obj);

	/**
	 * 内積での当たり判定
	 */
	virtual bool IsDot(ObjectBase& obj);

	/**
	 * 円弧と球の当たり判定
	 */
	virtual bool IsHitArc_Sphere(ObjectBase& obj);

	/**
	 * 座標をセットする
	 */
	void SetPos(VECTOR vPos) { _vPos = vPos; }

	/**
	 * 座標を取得する
	 */
	VECTOR GetPos()const { return _vPos; }

	/**
	 * 向きを取得する
	 */
	VECTOR GetDir()const { return _vDir; }

	bool _hitFlag;       // 攻撃当たり判定発生フラグ
	MV1_COLL_RESULT_POLY_DIM _hitPolyDim;

	float _r;            // 半径(当たり判定用)

protected:
	int _mh;           // モデルハンドル
	int	_cg;		   // 画像
	int	_cut;		   // 動作カウンタ
	int _attachIndex;  // アニメーションをアタッチ
	float _totalTime;  // アニメーション総再生時間
	float _playTime;   // アニメーション再生時間

	VECTOR _vPos;      // 位置
	VECTOR _oldPos;    // 移動処理前の位置保存
	VECTOR _vDir;      // 向き
	VECTOR _scrnPos;   // スクリーン座標
	VECTOR _capsulePos1, _capsulePos2; // 当たり判定用カプセルを形成する2点の座標

	float _hitX, _hitY;  // 2D当たり判定用(画像左上の座標)
	float _hitW, _hitH;  // 2D当たり判定用(画像右上の座標)

	float _angle;        // 角度(回転、向き)
	float _mvSpd;        // 移動速度
};

