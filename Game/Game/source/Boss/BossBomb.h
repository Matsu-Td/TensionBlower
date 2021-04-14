/**
 * @file   BossBomb.h
 * @brief  ボスのボム攻撃処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/03
 */

#pragma once

#include "ShotBase.h"

namespace tensionblower {

	namespace boss {

		/**
		 * @brief ボスのボム攻撃処理
		 */
		class BossBomb : public ShotBase {
		public:
			/**
			 * @brief ボム生成
			 * @param pos ボムの発生位置
			 */
			BossBomb(VECTOR pos);
			~BossBomb();

			OBJECTTYPE GetType()  override { return ObjectBase::OBJECTTYPE::BOSS_BOMB; }

			/**
			 * @brief 初期化
			 */
			void Initialize() override;

			/**
			 * @brief フレーム処理：計算
			 */
			void Process() override;

		private:
			/**
			 * @brief 上昇処理
			 */
			void StateUp();

			/**
			 * @brief 停止処理
			 */
			void StateStop();

			/**
			 * @brief 狙撃処理
			 */
			void StateSniper();

			/**
			 * @brief ボムの削除、爆発エフェクト生成
			 */
			void BombDelete();

			/**
			 * @brief 各種当たり判定呼び出し
			 */
			void CollisionCall();

			/**
			 * @brief 当たり判定：プレイヤー
			 * @param obj オブジェクトのポインタ
			 */
			void CollisionToPlayer(ObjectBase* obj);

			/**
			 * @brief 当たり判定：照準
			 * @param obj オブジェクトのポインタ
			 */
			void CollisionToReticle(ObjectBase* obj);

			/**
			 * @brief 当たり判定：ボス
			 * @param obj オブジェクトのポインタ
			 */
			void CollisionToBoss(ObjectBase* obj);

			const int UP_CNT = 24;  // 上昇カウント
			const int STOP_CNT = 24;  // 停止カウント
		};
	}
}