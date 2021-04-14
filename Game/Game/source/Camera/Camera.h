/**
 * @file   Camera.h
 * @brief  カメラクラス
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#pragma once

#include "appframe.h"

namespace tensionblower {

	namespace camera {

		/**
		 * @brief カメラクラス
		 */
		class Camera {
		public:
			Camera();
			~Camera();

			/**
			 * @brief 初期化
			 */
			void Initialize();

			/**
			 * @brief フレーム処理：計算
			 */
			void Process();

			/**
			 * @brief フレーム処理：描画
			 */
			void Render();

			/**
			 * インスタンスを取得
			 * @return Cameraのインスタンス
			 */
			static Camera* GetInstance() { return _pInstance; }

			/**
			 * @brief 座標取得
			 * @return 座標
			 */
			VECTOR GetPos() const { return _vPos; }

			/**
			 * @brief  ターゲット座標取得
			 * @return ターゲット座標
			 */
			VECTOR GetTarg() const { return _vTarg; }

			/**
			 * @brief カメラの向いている角度(rad)取得
			 * @return カメラの角度(rad)
			 */
			float GetRad() const;

			/**
			 * @brief カメラの状態
			 */
			enum class STATE {
				NORMAL,    // 通常状態
				MLS_LOCK,  // マルチロックシステム発動状態(FPS視点)
			};
			STATE _state;  // カメラ状態

			/**
			 * @brief  カメラの状態を取得
			 * @return カメラの状態
			 */
			STATE GetState() const { return _state; }

			static Camera* _pInstance;

		private:
			/**
			 * @brief カメラの位置を設定
			 * @param dis プレイヤーからの距離
			 * @param height プレイヤーからの高さ
			 */
			void SetPos(float dis, float height);

			/**
			 * @brief 通常状態の処理
			 */
			void StateNorm();

			/**
			 * @brief マルチロックオンシステム発生中の処理
			 */
			void StateMLSLock();

			VECTOR _vPos;    // 位置
			VECTOR _vTarg;   // 注視点

			struct LOCK_ON { // 構造体：ロックオン状態
				int x, y;  // スクリーン座標
				int cg;    // 画像
			};
			LOCK_ON _lockOn;

			const float NEAR_CLIP = 0.1f;    // 手前クリップ距離
			const float FAR_CLIP = 5000.0f; // 奥クリップ距離
		};
	}
}