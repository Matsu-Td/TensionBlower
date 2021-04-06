/**
 * @file   ModeTitle.h
 * @brief  タイトルモードクラス
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#include "appframe.h"
#include <string>

/**
 * @brief タイトルモードクラス
 */
class ModeTitle : public ModeBase{
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
	 * @brief タイトルメニュー選択
	 */
	void MenuSelect();

	/**
	 * @brief タイトル削除、次のモード登録
	 * @param nextMode 登録するモード 
	 * @param layer    登録するモードのレイヤー
	 * @param name     登録するモードの名前
	 */
	void ModeChange(ModeBase* nextMode, int layer, const char* modeName);

private:
	int _movieHandle; // 動画(背景)
	int _cgtitle;     // タイトルロゴ画像
	int _menuPos;     // メニュー選択位置

	const int ALL_MENU_NUM = 8;     // メニューUI画像総数
	static const int MENU_NUM = 4;  // メニューUI画像数(ON,OFF別)

	// メニューUI画像ファイル名(選択状態:ON)
	const TCHAR* _fileNameOn[MENU_NUM] =
	{ "res/ui/title/on/title_on_1.png",
	  "res/ui/title/on/title_on_2.png",
	  "res/ui/title/on/title_on_5.png",
      "res/ui/title/on/title_on_6.png" };

	// メニューUI画像ファイル名(未選択状態:OFF)
	const TCHAR* _fileNameOff[MENU_NUM] =
	{ "res/ui/title/off/title_off_1.png",
	  "res/ui/title/off/title_off_2.png",
	  "res/ui/title/off/title_off_5.png",
	  "res/ui/title/off/title_off_6.png" };

	int _uiOn[MENU_NUM];  // メニューUI画像(選択状態:ON)
	int _uiOff[MENU_NUM]; // メニューUI画像(未選択状態:OFF)

	const int MENU_POS_X[MENU_NUM] = { 125,565,1005,1445 }; // メニューUI画像のX座標
	const int MENU_POS_Y = 720; // メニューUI画像のY座標(共通)

	// メニュー名
	enum MENU {
		START,     // ゲームスタート
		TUTORIAL,  // チュートリアル
		CREDIT,    // クレジット
		GAME_END,  // 終了
	};
}; 
