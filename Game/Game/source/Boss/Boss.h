/**
 * @file   Boss.h
 * @brief  ボスクラス
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#pragma once

#include "appframe.h"
#include "../Object/ObjectBase.h"

namespace tensionblower {

	namespace boss {

		/**
		 * @brief ボスクラス
		 */
		class Boss : public ObjectBase {
		public:
			Boss();
			~Boss();

			OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS; }

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

			/**
			 * @brief  ヒットポイント値取得
			 * @return ヒットポイント
			 */
			int GetHitPoint() const { return _hitpoint; }

			/**
			 * @brief  シールド値取得
			 * @return シールド値
			 */
			int GetShield() const { return _shield; }

			/**
			 * @brief  フェーズ数取得
			 * @return 現在のフェーズ
			 */
			int GetPhaseNo() const { return _phaseNo; }

			/**
		　　 * @brief プレイヤーに弾き返された弾によるダメージ処理
			 */
			void RepelDamage();

			/**
			 * @brief プレイヤーから受けたダメージ量計算
			 */
			void AttackDamage();

			/**
			 * @brief ヒットポイントへの爆発ダメージ
			 */
			void ExplosionDamageHP();

			/**
			 * @brief シールドへの爆発ダメージ
			 */
			void ExplosionDamageShield();

			/**
			 * @brief Bossインスタンスを取得する
			 */
			static Boss* GetInstance() { return _pInstance; }

			static Boss* _pInstance;

			// プレイヤークラスで使用
			int  _bulletNum;     // ダウン直前に出現していた弾の数カウント
			bool _mlsDownFlag;   // MLSで弾き返された弾でダウンすると「true」

			/**
			 * @brief 状態
			 */
			enum class STATE {
				NORMAL,  // 通常
				DOWN,    // ダウン
				RETURN,  // 復帰
				DEATH,   // 死亡
			};
			STATE GetState() const { return _state; };

		private:
			/**
			 * @brief 通常状態処理
			 */
			void StateNormal();

			/**
			 * @brief ダウン状態処理
			 */
			void StateDown();

			/**
			 * @brief 復帰状態処理
			 */
			void StateReturn();

			/**
			 * モーション切替
			 * @param  oldState 処理前の状態
			 */
			void MotionSwitch();

			/**
			 * @brief 死亡処理
			 */
			void Death();

			/**
			 * @brief 弾幕の弾を生成する
			 * @param posY 弾の生成するY座標(高さ)
			 * @param shotSpd 弾の移動速度
			 * @param ShotAngle 弾を生成する角度、位置
			 */
			void ShotGeneration(float posY, float shotSpd, float shotAngle);

			/**
			 * @brief レーザーを生成する
			 * @param laserAngle レーザーの発射角度、位置
			 * @param roteSpd レーザーの発射位置が回転する速度(デフォルト:1.0f)
			 */
			void LaserGeneration(float laserAngle, float roteSpd = 1.0f);

			/**
			 * @brief 弾幕パターン切替処理
			 */
			void BarragePatternSwitch();
			/**
			 * @brief 弾幕パターン1&2
			 * @brief ボスを中心として発射位置を回転させながら8つの弾を同時に発射する
			 */
			void BarragePattern1and2();

			/**
			 * @brief 弾幕パターン3
			 * @brief ボスを中心として発射位置を回転させながら8つの弾を同時に発射する
			 * @brief 短い周期で回転方向を変化させ、弾が横に波打つような弾幕を発生させる
			 */
			void BarragePattern3();

			/**
			 * @brief 弾幕パターン4-1
			 * @brief ボスを中心として発射位置を左回りに回転させながら8つの弾を同時に発射する
			 */
			void BarragePattern4_1();

			/**
			 * @brief 弾幕パターン4-2
			 * @brief ボスを中心として発射位置を右回りに回転させながら8つの弾を同時に発射する
			 */
			void BarragePattern4_2();

			/**
			 * @brief 弾幕パターン5
			 * @brief 同時に7発の弾を発射
			 * @brief 隣り合う弾の高低差を一定にしたまま発射位置を徐々に変化させ、
			 * @brief 直線に波打つ弾幕を発生させる
			 */
			void BarragePattern5();

			/**
			 * @brief 弾幕パターン6
			 * @brief 同時に3発発射、プレイヤーを狙い撃つ攻撃
			 */
			void BarragePattern6();

			/**
			 * @brief 弾幕パターン7
			 * @brief ボムによる攻撃
			 */
			void BarragePattern7();

			/**
			 * @brief レーザー攻撃1-1
			 * @brief レーザー1本生成し、発射位置をボスを中心に左回りに回転させる
			 */
			void LaserAttack1_1();

			/**
			 * @brief レーザー攻撃1-2
			 * @brief レーザー1本生成し、発射位置をボスを中心に右回りに回転させる
			 */
			void LaserAttack1_2();

			/**
			 * @brief レーザー攻撃2
			 * @brief 発射位置をボスを中心に、同時に4本のレーザーを発射する
			 */
			void LaserAttack2();

			/**
			 * @brief フェーズ変更処理
			 */
			void FhaseChange();

			/**
			 * @brief 6種類の声データをランダムで再生
			 */
			void PlayAttackVoiceChange();

			/**
			 * @brief 声データ再生
			 * @param voiceName 声データの名前
			 */
			void PlayVoice(std::string voiceName);

			/**
			 * @brief ボス正面方向回転処理
			 * @param rotSpdChenge 回転速度切替用
			 */
			void DirectionalRotation(float rotSpdChange);

		private:
			int   _hitpoint;      // ヒットポイント値
			int   _shield;        // シールド値
			int   _downTime;      // ダウン時間
			int   _deathCnt;      // 死亡カウント
			bool  _stateDown;     // ダウン状態か(true:ダウン状態)
			float _sinCnt;        // 上下運動用サイン波カウント

			int   _shotCnt;       // 弾幕発射タイミングカウント
			int   _mlsCnt;        // マルチロックオンシステム発動時のカウント
			int   _reverseCnt;    // 弾幕回転方向が反転するカウント
			int   _patternRandom; // 弾幕パターン3種ランダムで切替
			int   _phaseNo;       // フェーズ：HP残量で変化
			float _shotAngle;     // 弾幕の発射角度
			float _shotAngleUp;   // 通常の弾幕の上側に発生する弾幕の発射角度(弾幕パターン4用)
			float _setRotAngle;   // 発射一定角度セット
			float _shotHeight;    // 弾幕を発射する高さ
			float _laserAngle;    // レーザーの発射角度

			static const int ATTACK_VOICE_NUM = 6;        // 攻撃時の声データ総数
			std::string _attackNameNo[ATTACK_VOICE_NUM] = // 攻撃時の声データの名前を格納
			{ "attack1","attack1" ,"attack2" ,"attack4" ,"attack5" ,"attack6" };

			STATE  _state;    // 状態
			STATE  _oldState; // 処理前の状態
			VECTOR _cross;    // 外積(ボスの向き回転計算用)

			const int PHASE_ONE_HP       = 4000; // フェーズ1へ移行する残りHP量
			const int PHASE_TWO_HP       = 3000; // フェーズ2へ移行する残りHP量
			const int PHASE_THREE_HP     = 2000; // フェーズ3へ移行する残りHP量
			const int PHASE_FOUR_HP      = 1000; // フェーズ4へ移行する残りHP量
			const int MIN_DOWN_TIME      = 180;  // ダウン時間最小値(ダウン時間計算用)
			const int PATTERN_CHANGE_CNT = 240;  // 弾幕パターンを変化させるカウント最大値
			const int SHOT_REVERSE_CNT   = 90;   // 弾幕回転方向を変化させるカウント最大値
			const int EXPLOSION_DMG_NORM = 2;    // 爆発HPダメージ量：通常時(シールド無)
			const int EXPLOSION_DMG_HP   = 1;    // 爆発HPダメージ量(シールド有)
			const int EXPLOSION_DMG_SLD  = 2;    // 爆発シールドダメージ量(シールド有)
		
			const float ADD_POS_Y     = 9.0f;    // 当たり判定用Y座標加算値
			const float ROT_SPD       = 0.01f;   // ボスの向き回転用角速度
			const float SHOT_DISTANCE = 10.0f;   // 弾幕を発生させる位置(ボス中心からの距離)
			const float LESER_POS_Y   = 4.5f;    // レーザーを発射する位置Y座標(高さ)
			const float SHOT_Y_MAX    = 12.0f;   // 弾幕の高さ上限
		};
	}
}