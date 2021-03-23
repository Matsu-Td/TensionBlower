/**
 * @file   ModeGame.h
 * @brief  �Q�[���{��
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appframe.h"
#include "ObjectServer.h"
#include "Camera.h"
#include "Stage.h"
#include "Player.h"
#include "Boss.h"
#include "ModePause.h"
#include "CharaData.h"
#include "PlayerStatus.h"
#include "BossStatus.h"

class ModeGame : public ModeBase{
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

	Camera       _cam;
	ObjectServer _objServer;

	std::unique_ptr<CharaData> _charaData; // JSON�t�@�C������L�����f�[�^�ǂݍ���
	bool _stopObjProcess;       // �I�u�W�F�N�g�������X�g�b�v

protected:
	PlayerStatus _playerStatus;
	BossStatus   _bossStatus;
}; 
