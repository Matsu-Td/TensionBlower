/**
 * @file   ModeTutorial.h
 * @brief  チュートリアルモードクラス
 * 
 * @author matsuo tadahiko
 * @date   2021/03/15
 */

#include "appframe.h"

/**
 * @brief チュートリアルモードクラス
 */
class ModeTutorial : public ModeBase{
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

private:
	int _bg;  // 背景
	
	int _menuPos;     // メニュー選択位置
	int _oldMenuPos;  // 処理前のメニュー選択位置

	std::unordered_map<std::string, int> _mapUi;  // UI用コンテナ

	const int ALL_MENU_NUM = 20;  // メニューUI画像総数
	static const int MENU_NUM = 10;		 // メニューUI画像数(ON,OFF別)
	int _cg[MENU_NUM];                       // 説明画像
	int _movieHandle[MENU_NUM];              // 動画

	// メニューUI画像ファイル名(選択状態:ON)
	const TCHAR* _fileNameOn[MENU_NUM] =
	{ "res/ui/tutorial/on/tutorial_button_on.png",
	  "res/ui/tutorial/on/tutorial_game_on.png",
      "res/ui/tutorial/on/tutorial_on_1.png",
	  "res/ui/tutorial/on/tutorial_on_2.png",
	  "res/ui/tutorial/on/tutorial_on_3.png",
	  "res/ui/tutorial/on/tutorial_on_5.png",
	  "res/ui/tutorial/on/tutorial_on_7.png",
	  "res/ui/tutorial/on/tutorial_on_8.png",
	  "res/ui/tutorial/on/tutorial_on_9.png",
	  "res/ui/tutorial/on/tutorial_on_10.png" };

	// メニューUI画像ファイル名(未選択状態:OFF)
	const TCHAR* _fileNameOff[MENU_NUM] =
	{ "res/ui/tutorial/off/tutorial_button_off.png",
	  "res/ui/tutorial/off/tutorial_game_off.png",
	  "res/ui/tutorial/off/tutorial_off_1.png",
	  "res/ui/tutorial/off/tutorial_off_2.png",
	  "res/ui/tutorial/off/tutorial_off_3.png",
	  "res/ui/tutorial/off/tutorial_off_5.png",
	  "res/ui/tutorial/off/tutorial_off_7.png",
	  "res/ui/tutorial/off/tutorial_off_8.png",
	  "res/ui/tutorial/off/tutorial_off_9.png",
	  "res/ui/tutorial/off/tutorial_off_10.png" };

	int _uiOn[MENU_NUM];  // メニューUI画像(選択状態:ON)
	int _uiOff[MENU_NUM]; // メニューUI画像(未選択状態:OFF)

	// メニューUI画像のX座標
	const int MENU_POS_X[MENU_NUM] =
	{ 1200,1515,1200,1515,1200,1515,1200,1515,1200,1515 }; 

	// メニューUI画像のY座標
	const int MENU_POS_Y[MENU_NUM] =
	{ 50,145,240,335,430,525,620,715,810,905 };

	const int MOVIE_POS_X = 120;   // 動画を描画するX座標
	const int MOVIE_POS_Y = 130;   // 動画を描画するY座標
	const int SETSUMEI_POS = 50;   // 説明画像を描画する座標
};

