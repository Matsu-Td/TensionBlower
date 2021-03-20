/**
 * @file   ModeTitle.h
 * @brief  タイトル画面
 * 
 * @author matsuo tadahiko
 * @date   2021/03/15
 */

#include "appframe.h"

#include <string>

class ModeTitle : public ModeBase{
	typedef ModeBase base;

public:
	/**
	 * @brief  初期化
	 * @return 処理の成否
	 */
	virtual bool Initialize();

	/**
	 * @brief  解放
	 * @return 処理の成否
	 */
	virtual bool Terminate();

	/**
	 * @brief  フレーム処理：計算
	 * @return 処理の成否
	 */
	virtual bool Process();

	/**
	 * @brief  フレーム処理：描画
	 * @return 処理の成否
	 */
	virtual bool Render();

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

protected:
	int _bg;       // 背景
	int _cgtitle;  // タイトルロゴ画像
	int _menuPos;  // メニュー選択位置

	static constexpr int ALL_MENU_NUM = 8;  // メニューUI画像総数
	static constexpr int MENU_NUM = 4;       // メニューUI画像数(ON,OFF別)

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

	static constexpr int MENU_POS_X[MENU_NUM] = { 125,565,1005,1445 }; // メニューUI画像のX座標
	static constexpr int MENU_POS_Y = 720; // メニューUI画像のY座標(共通)

	// メニュー名
	enum MENU {
		START,     // ゲームスタート
		TUTORIAL,  // チュートリアル
		CREDIT,    // クレジット
		GAME_END,  // 終了
	};
}; 
