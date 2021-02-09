
/**
 * @file  ModeTitle.h
 * @brief タイトル画面
 *
 * @date 2021-02-09
 */

#include "appframe.h"

#include <string>

class ModeTitle : public ModeBase{
	typedef ModeBase base;

public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	/**
	 * タイトルメニュー選択
	 */
	void MenuSelect();

	/**
	 * タイトル削除、次のモード登録
	 * @param nextMode 登録するモード 
	 * @param layer    登録するモードのレイヤー
	 * @param name     登録するモードの名前
	 */
	void ModeChange(ModeBase* nextMode, int layer, const char* modeName);

protected:
	int _cgtitle;  // タイトルロゴ画像
	int _menuPos;  // メニュー選択位置

	std::unordered_map <std::string,int> _ui;  // UI画像

	// メニュー名
	enum MENU {
		START,     // ゲームスタート
		TUTORIAL,  // チュートリアル
		RANKING,   // ランキング
		CREDIT,    // クレジット
		GAME_END,  // 終了
	};
}; 
