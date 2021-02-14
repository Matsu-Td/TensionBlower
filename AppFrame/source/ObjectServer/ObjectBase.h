#pragma once
#include "DxLib.h"
#include <iostream>


class ObjectBase {
public:
	ObjectBase();
	~ObjectBase();

	enum class OBJECTTYPE {
		PLAYER,
		PLAYER_BULLET,
		BOSS,
		BOSS_BULLET,
		CAMERA,
		STAGE,
		RETICLE,
		LASER,
	};
	virtual OBJECTTYPE	GetType() = 0;

	virtual void Init();
	virtual void Process();
	virtual void Render();
	virtual void Damage() {}
	virtual void AttackDamage(){}

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

	virtual bool IsDot(ObjectBase& obj);

	virtual bool IsHitArc_Sphere(ObjectBase& obj);
	/**
	* 課題　実践2///////////////////////////////////////////////////
	*/
	//ObjectBase(ObjectBase&& obj) noexcept;
	//ObjectBase& operator=(ObjectBase&& obj) noexcept;
	/*
	template<typename T>
	void moveSwap(T& a, T& b) {
		T tmp = std::move(a);
		a = std::move(b);
		b = std::move(tmp);
		
	}*/

	void SetPos(VECTOR vPos) { _vPos = vPos; }
	///////////////////////////////////////////////////////////////


	VECTOR GetPos()const { return _vPos; }
	VECTOR GetDir()const { return _vDir; }
	bool _hitFlag;       // 攻撃当たり判定発生フラグ
	MV1_COLL_RESULT_POLY_DIM _hitPolyDim;
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
	float _r;            // 半径(当たり判定用)

	

};

