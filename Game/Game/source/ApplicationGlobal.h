/**
 * @file   ApplicationGlobal.h
 * @brief  �O���[�o���ϐ���`
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appframe.h"

class ApplicationGlobal{
public:
	ApplicationGlobal();
	virtual ~ApplicationGlobal();

	bool Init();

public:
	bool _gameEndFlag;    // �Q�[���I���t���O(true:�Q�[���I��)
	int  _gameTime;       // �N���A�܂ł̌o�ߎ���
	int  _remainingHP;    // �c��HP
	int  _totalGetEnergy; // ���G�l���M�[�����
	int  _totalRepelCnt;  // ���v�e���Ԃ���
};

extern ApplicationGlobal gGlobal; 