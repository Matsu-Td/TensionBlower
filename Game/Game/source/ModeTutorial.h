/**
 * @file   ModeTutorial.h
 * @brief  �`���[�g���A�����
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appframe.h"

class ModeTutorial : public ModeBase{
	typedef ModeBase base;

public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:
	int _bg;
	
	int _menuPos; // ���j���[�I���ʒu
	int _oldMenuPos;

	std::unordered_map<std::string, int> _mapUi;

	static constexpr int ALL_MENU_NUM = 16;  // ���j���[UI�摜����
	static constexpr int MENU_NUM = 8;      // ���j���[UI�摜��(ON,OFF��)
	int _cg[MENU_NUM];                       // �����摜
	int _movieHandle[MENU_NUM];

	// ���j���[UI�摜�t�@�C����(�I�����:ON)
	const TCHAR* _fileNameOn[MENU_NUM] =
	{ "res/ui/tutorial/on/tutorial_on_1.png",
	  "res/ui/tutorial/on/tutorial_on_2.png",
	  "res/ui/tutorial/on/tutorial_on_3.png",
	  "res/ui/tutorial/on/tutorial_on_5.png",
	  "res/ui/tutorial/on/tutorial_on_7.png",
	  "res/ui/tutorial/on/tutorial_on_8.png",
	  "res/ui/tutorial/on/tutorial_on_9.png",
	  "res/ui/tutorial/on/tutorial_on_10.png" };

	// ���j���[UI�摜�t�@�C����(���I�����:OFF)
	const TCHAR* _fileNameOff[MENU_NUM] =
	{ "res/ui/tutorial/off/tutorial_off_1.png",
	  "res/ui/tutorial/off/tutorial_off_2.png",
	  "res/ui/tutorial/off/tutorial_off_3.png",
	  "res/ui/tutorial/off/tutorial_off_5.png",
	  "res/ui/tutorial/off/tutorial_off_7.png",
	  "res/ui/tutorial/off/tutorial_off_8.png",
	  "res/ui/tutorial/off/tutorial_off_9.png",
	  "res/ui/tutorial/off/tutorial_off_10.png" };

	int _uiOn[MENU_NUM];  // ���j���[UI�摜(�I�����:ON)
	int _uiOff[MENU_NUM]; // ���j���[UI�摜(���I�����:OFF)

	// ���j���[UI�摜��X���W
	static constexpr int MENU_POS_X[MENU_NUM] =
	{ 1200,1515,1200,1515,1200,1515,1200,1515 }; 

	// ���j���[UI�摜��Y���W
	static constexpr int MENU_POS_Y[MENU_NUM] = 
	{ 50,145,240,335,430,525,620,715 };
};

