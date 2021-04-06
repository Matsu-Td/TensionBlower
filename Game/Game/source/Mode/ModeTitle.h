/**
 * @file   ModeTitle.h
 * @brief  �^�C�g�����[�h�N���X
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#include "appframe.h"
#include <string>

/**
 * @brief �^�C�g�����[�h�N���X
 */
class ModeTitle : public ModeBase{
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

	/**
	 * @brief �^�C�g�����j���[�I��
	 */
	void MenuSelect();

	/**
	 * @brief �^�C�g���폜�A���̃��[�h�o�^
	 * @param nextMode �o�^���郂�[�h 
	 * @param layer    �o�^���郂�[�h�̃��C���[
	 * @param name     �o�^���郂�[�h�̖��O
	 */
	void ModeChange(ModeBase* nextMode, int layer, const char* modeName);

private:
	int _movieHandle; // ����(�w�i)
	int _cgtitle;     // �^�C�g�����S�摜
	int _menuPos;     // ���j���[�I���ʒu

	const int ALL_MENU_NUM = 8;     // ���j���[UI�摜����
	static const int MENU_NUM = 4;  // ���j���[UI�摜��(ON,OFF��)

	// ���j���[UI�摜�t�@�C����(�I�����:ON)
	const TCHAR* _fileNameOn[MENU_NUM] =
	{ "res/ui/title/on/title_on_1.png",
	  "res/ui/title/on/title_on_2.png",
	  "res/ui/title/on/title_on_5.png",
      "res/ui/title/on/title_on_6.png" };

	// ���j���[UI�摜�t�@�C����(���I�����:OFF)
	const TCHAR* _fileNameOff[MENU_NUM] =
	{ "res/ui/title/off/title_off_1.png",
	  "res/ui/title/off/title_off_2.png",
	  "res/ui/title/off/title_off_5.png",
	  "res/ui/title/off/title_off_6.png" };

	int _uiOn[MENU_NUM];  // ���j���[UI�摜(�I�����:ON)
	int _uiOff[MENU_NUM]; // ���j���[UI�摜(���I�����:OFF)

	const int MENU_POS_X[MENU_NUM] = { 125,565,1005,1445 }; // ���j���[UI�摜��X���W
	const int MENU_POS_Y = 720; // ���j���[UI�摜��Y���W(����)

	// ���j���[��
	enum MENU {
		START,     // �Q�[���X�^�[�g
		TUTORIAL,  // �`���[�g���A��
		CREDIT,    // �N���W�b�g
		GAME_END,  // �I��
	};
}; 
