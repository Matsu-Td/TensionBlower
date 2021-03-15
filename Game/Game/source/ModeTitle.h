/**
 * @file   ModeTitle.h
 * @brief  �^�C�g�����
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
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
	 * �^�C�g�����j���[�I��
	 */
	void MenuSelect();

	/**
	 * �^�C�g���폜�A���̃��[�h�o�^
	 * @param nextMode �o�^���郂�[�h 
	 * @param layer    �o�^���郂�[�h�̃��C���[
	 * @param name     �o�^���郂�[�h�̖��O
	 */
	void ModeChange(ModeBase* nextMode, int layer, const char* modeName);

protected:
	int _bg;       // �w�i
	int _cgtitle;  // �^�C�g�����S�摜
	int _menuPos;  // ���j���[�I���ʒu

	static constexpr int ALL_MENU_NUM = 8;  // ���j���[UI�摜����
	static constexpr int MENU_NUM = 4;       // ���j���[UI�摜��(ON,OFF��)

	// ���j���[UI�摜�t�@�C����(�I�����:ON)
	const TCHAR* _fileNameOn[MENU_NUM] =
	{ "res/ui/title/on/title_on_1.png",
	  "res/ui/title/on/title_on_2.png",
//	  "res/ui/title/on/title_on_3.png",
	  "res/ui/title/on/title_on_5.png",
      "res/ui/title/on/title_on_6.png" };

	// ���j���[UI�摜�t�@�C����(���I�����:OFF)
	const TCHAR* _fileNameOff[MENU_NUM] =
	{ "res/ui/title/off/title_off_1.png",
	  "res/ui/title/off/title_off_2.png",
//	  "res/ui/title/off/title_off_3.png",
	  "res/ui/title/off/title_off_5.png",
	  "res/ui/title/off/title_off_6.png" };

	int _uiOn[MENU_NUM];  // ���j���[UI�摜(�I�����:ON)
	int _uiOff[MENU_NUM]; // ���j���[UI�摜(���I�����:OFF)

	static constexpr int MENU_POS_X[MENU_NUM] = { 120,435,120,435 }; // ���j���[UI�摜��X���W
	static constexpr int MENU_POS_Y[MENU_NUM] = { 480,575,670,765 }; // ���j���[UI�摜��Y���W

	// ���j���[��
	enum MENU {
		START,     // �Q�[���X�^�[�g
		TUTORIAL,  // �`���[�g���A��
		// TODO:�����L���O�@�\�����ׁ̈A�ꎞ�I�ɏ������폜����(�����\��)
//		RANKING,   // �����L���O
		CREDIT,    // �N���W�b�g
		GAME_END,  // �I��
	};
}; 
