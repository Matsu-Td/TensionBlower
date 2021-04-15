/**
 * @file   Destruction.h
 * @brief  ボスの死亡爆発エフェクトクラス
 * 
 * @author matsuo tadahiko
 * @date   2021/03/07
 */

#pragma once

#include "appframe.h"
#include "../Object/ObjectBase.h"

namespace tensionblower {

	namespace effect {

		/**
		 * @brief ボスの死亡爆発エフェクトクラス
		 */
		class Destruction : public ObjectBase {
		public:
			/**
			 * @brief ボスの死亡エフェクト生成
			 * @param pos エフェクト生成位置
			 */
			Destruction(VECTOR pos);
			~Destruction();

			OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::DESTRUCTION; }

			/**
			 * @brief フレーム処理：計算
			 */
			void Process() override;

			/**
			 * @brief フレーム処理：描画
			 */
			void Render() override;

		private:
			int _gameClearCnt;  // ゲームクリア表示までのカウント
			int	_effectHandle;  // エフェクトファイルをロードするハンドル
			int	_playingHandle;	// ロードしたエフェクトファイルから、エフェクトを生成したもの
		};
	}
}