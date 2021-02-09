
/**
 * @file  ModeTitle.h
 * @brief �^�C�g�����
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
	int _cgtitle;  // �^�C�g�����S�摜
	int _menuPos;  // ���j���[�I���ʒu

	std::unordered_map <std::string,int> _ui;  // UI�摜

	// ���j���[��
	enum MENU {
		START,     // �Q�[���X�^�[�g
		TUTORIAL,  // �`���[�g���A��
		RANKING,   // �����L���O
		CREDIT,    // �N���W�b�g
		GAME_END,  // �I��
	};
}; 
