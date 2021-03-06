/**
 * @file   ModeGame.h
 * @brief  ゲームモードクラス
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#pragma once

#include "appframe.h"
#include "../Object/ObjectServer.h"
#include "../Camera/Camera.h"
#include "../Stage/Stage.h"
#include "../Player/Player.h"
#include "../Boss/Boss.h"
#include "../Mode/ModePause.h"
#include "../CharaData/CharaData.h"
#include "../Player/PlayerStatus.h"
#include "../Boss/BossStatus.h"

namespace tensionblower {

	namespace mode {

		/**
		 * @brief ゲームモードクラス
		 */
		class ModeGame : public ::mode::ModeBase {
			using base = ModeBase;

		public:
			/**
			 * @brief  初期化
			 * @return 処理の成否
			 */
			bool Initialize() override;

			/**
			 * @brief  解放
			 * @return 処理の成否
			 */
			bool Terminate() override;

			/**
			 * @brief  フレーム処理：計算
			 * @return 処理の成否
			 */
			bool Process() override;

			/**
			 * @brief  フレーム処理：描画
			 * @return 処理の成否
			 */
			bool Render() override;

			/**
			 * @brief  ゲームモードを取得
			 * @return ゲームモードのインスタンス
			 */
			static ModeGame* GetModeGame() {
				return static_cast<mode::ModeGame*>(::mode::ModeServer::GetInstance()->Get("game"));
			}

			camera::Camera     _cam;  // カメラ
			object::ObjectServer _objServer;  // オブジェクト管理サーバー

			std::unique_ptr<charadata::CharaData> _charaData; // JSONファイルからキャラデータ読み込み

			bool _stopObjProcess;       // オブジェクト処理をストップ

		private:
			/**
			 * @brief ライトの設定
			 */
			void SetLight();

			/**
			 * @brief ライトのディフューズカラーを設定する
			 * @param lightHandle ライトハンドル
			 */
			void SetLightColorHandle(int lightHandle);

			player::PlayerStatus _playerStatus;  // プレイヤーのステータス
			boss::BossStatus     _bossStatus;    // ボスのステータス
		};
	}
}
