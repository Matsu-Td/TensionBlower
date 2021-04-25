/**
 * @file   Stage.h
 * @brief  ステージクラス
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#pragma once

#include "appframe.h"
#include "../Object/ObjectBase.h"

namespace tensionblower {

	namespace stage {

		/**
		 * @brief ステージクラス
		 */
		class Stage : public object::ObjectBase {
		public:
			Stage();
			~Stage();

			OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::STAGE; }

			/**
			 * @brief フレーム処理：描画
			 */
			void Render() override;
		private:
			int _mhMap; // ステージモデル
		};
	}
}