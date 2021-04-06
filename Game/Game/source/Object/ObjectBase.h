/**
 * @file  ObjectBase.h
 * @brief オブジェクト基底クラス
 *
 * @date 2021/03/20
 */

#pragma once

#include "appframe.h"
#include <iostream>

/**
 * @brief オブジェクト基底クラス
 */
class ObjectBase {
public:
	ObjectBase();
	virtual ~ObjectBase();

	/**
	 * @brief オブジェクトの種類を定義
	 */
	enum class OBJECTTYPE {
		PLAYER,        // プレイヤー
		BOSS,          // ボス
		BOSS_BULLET,   // ボスの弾幕
		BOSS_BOMB,     // ボスのボム
		STAGE,         // ステージ
		RETICLE,       // 照準
		LASER,         // レーザーエフェクト
		EXPLOSION,     // 爆発エフェクト
		DESTRUCTION,   // ボス破壊、爆発エフェクト
		HIT_EFFECT,    // 近接攻撃のヒットエフェクト
	};

	/**
	 * @brief オブジェクトの種類を返す
	 */
	virtual OBJECTTYPE	GetType() = 0;

	/**
	 * @brief 初期化
	 */
	virtual void Initialize();

	/**
	 * @brief フレーム処理：計算
	 */
	virtual void Process();

	/**
	 * @brief フレーム処理：描画
	 */
	virtual void Render();

	/**
	 * @brief モデルとステージの当たり判定
	 * @param r カプセルの半径
	 */
	virtual bool IsHitStage(ObjectBase& obj, float r);

	/**
	 * @brief カプセル同士の当たり判定
	 * @param r カプセルの半径
	 */
	virtual bool IsHitLineSegment(ObjectBase& obj, float r);

	/**
	 * @brief スクリーン座標上の当たり判定
	 */
	virtual bool IsHitScrnPos(ObjectBase& obj);

	/**
	 * @brief 内積での当たり判定
	 */
	virtual bool IsDot(ObjectBase& obj);

	/**
	 * @brief 円弧と球の当たり判定
	 */
	virtual bool IsHitArc_Sphere(ObjectBase& obj);

	/**
	 * @brief モデルの影を描画
	 * @param modelScale モデルの拡大率(デフォルトは 1.0f)
	 */
	void ShadowRender(float modelScale = 1.0f);

	/**
	 * @brief 座標を設定する
	 */
	void SetPos(VECTOR vPos) { _vPos = vPos; }

	/**
	 * @brief 座標を取得する
	 */
	VECTOR GetPos()const { return _vPos; }

	/**
	 * @brief 向きを取得する
	 */
	VECTOR GetDir()const { return _vDir; }

	bool _hitFlag;                         // 攻撃当たり判定発生フラグ
	MV1_COLL_RESULT_POLY_DIM _hitPolyDim;  // 当たり判定結果(構造体)

	float _r;           // 半径(当たり判定用)

protected:
	int _mh;           // モデルハンドル
	int _shadowModel;  // 影用モデルハンドル
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