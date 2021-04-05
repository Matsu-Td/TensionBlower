/**
 * @file   ModeTutorial.h
 * @brief  �`���[�g���A�����[�h�N���X
 * 
 * @author matsuo tadahiko
 * @date   2021/03/15
 */

#include "appframe.h"

/**
 * @brief �`���[�g���A�����[�h�N���X
 */
class ModeTutorial : public ModeBase{
	using base = ModeBase;

public:
	/**
	 * @brief  ������
	 * @return �����̐���
	 */
	bool Initialize() override;

	/**
	 * @brief  ���
	 * @return �����̐���
	 */
	bool Terminate() override;

	/**
	 * @brief  �t���[�������F�v�Z
	 * @return �����̐���
	 */
	bool Process() override;

	/**
	 * @brief  �t���[�������F�`��
	 * @return �����̐���
	 */
	bool Render() override;

private:
	int _bg;  // �w�i
	
	int _menuPos;     // ���j���[�I���ʒu
	int _oldMenuPos;  // �����O�̃��j���[�I���ʒu

	std::unordered_map<std::string, int> _mapUi;  // UI�p�R���e�i

	const int ALL_MENU_NUM = 20;  // ���j���[UI�摜����
	static const int MENU_NUM = 10;		 // ���j���[UI�摜��(ON,OFF��)
	int _cg[MENU_NUM];                       // �����摜
	int _movieHandle[MENU_NUM];              // ����

	// ���j���[UI�摜�t�@�C����(�I�����:ON)
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

	// ���j���[UI�摜�t�@�C����(���I�����:OFF)
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

	int _uiOn[MENU_NUM];  // ���j���[UI�摜(�I�����:ON)
	int _uiOff[MENU_NUM]; // ���j���[UI�摜(���I�����:OFF)

	// ���j���[UI�摜��X���W
	const int MENU_POS_X[MENU_NUM] =
	{ 1200,1515,1200,1515,1200,1515,1200,1515,1200,1515 }; 

	// ���j���[UI�摜��Y���W
	const int MENU_POS_Y[MENU_NUM] =
	{ 50,145,240,335,430,525,620,715,810,905 };

	const int MOVIE_POS_X = 120;   // �����`�悷��X���W
	const int MOVIE_POS_Y = 130;   // �����`�悷��Y���W
	const int SETSUMEI_POS = 50;   // �����摜��`�悷����W
};

