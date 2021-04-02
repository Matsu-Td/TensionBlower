/**
 * @file   ModeGame.h
 * @brief  ゲームモードクラス
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

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

/**
 * ゲームモードクラス
 */
class ModeGame : public ModeBase{
	using base = ModeBase;

public:
	/**
	 * 初期化
	 * @return 処理の成否
	 */
	bool Initialize() override;

	/**
	 * 解放 
	 * @return 処理の成否
	 */
	bool Terminate() override;

	/**
	 * フレーム処理：計算
	 * @return 処理の成否 
	 */
	bool Process() override;

	/**
	 * フレーム処理：描画
	 * @return 処理の成否 
	 */
	bool Render() override;

	/**
	 * ライトのディフューズカラーを設定する
	 * @param lightHandle ライトハンドル
	 */
	void SetLightColorHandle(int lightHandle);

	Camera       _cam;
	ObjectServer _objServer;

	std::unique_ptr<CharaData> _charaData; // JSONファイルからキャラデータ読み込み
	bool _stopObjProcess;       // オブジェクト処理をストップ
	int _shadowMapHandle;
private:
	PlayerStatus _playerStatus;
	BossStatus   _bossStatus;
	
}; 
