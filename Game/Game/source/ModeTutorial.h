/**
 * @file   ModeTutorial.h
 * @brief  チュートリアル画面
 * 
 * @author matsuo tadahiko
 * @date   2021/03/15
 */

#include "appframe.h"

class ModeTutorial : public ModeBase{
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

protected:
	int _bg;  // 背景
	
	int _menuPos;     // メニュー選択位置
	int _oldMenuPos;  // 処理前のメニュー選択位置

	std::unordered_map<std::string, int> _mapUi;  // UI用コンテナ

	static constexpr int ALL_MENU_NUM = 16;  // メニューUI画像総数
	static constexpr int MENU_NUM = 8;		 // メニューUI画像数(ON,OFF別)
	int _cg[MENU_NUM];                       // 説明画像
	int _movieHandle[MENU_NUM];              // 動画

	// メニューUI画像ファイル名(選択状態:ON)
	const TCHAR* _fileNameOn[MENU_NUM] =
	{ "res/ui/tutorial/on/tutorial_on_1.png",
	  "res/ui/tutorial/on/tutorial_on_2.png",
	  "res/ui/tutorial/on/tutorial_on_3.png",
	  "res/ui/tutorial/on/tutorial_on_5.png",
	  "res/ui/tutorial/on/tutorial_on_7.png",
	  "res/ui/tutorial/on/tutorial_on_8.png",
	  "res/ui/tutorial/on/tutorial_on_9.png",
	  "res/ui/tutorial/on/tutorial_on_10.png" };

	// メニューUI画像ファイル名(未選択状態:OFF)
	const TCHAR* _fileNameOff[MENU_NUM] =
	{ "res/ui/tutorial/off/tutorial_off_1.png",
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
	static constexpr int MENU_POS_X[MENU_NUM] =
	{ 1200,1515,1200,1515,1200,1515,1200,1515 }; 

	// メニューUI画像のY座標
	static constexpr int MENU_POS_Y[MENU_NUM] = 
	{ 50,145,240,335,430,525,620,905 };
};

