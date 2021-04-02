/**
 * @file   ModeGame.h
 * @brief  �Q�[�����[�h�N���X
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appframe.h"
#include "../Object/ObjectServer.h"
#include "../Camera/Camera.h"
#include "../Stage/Stage.h"
#include "../Player/Player.h"
#include "../Boss/Boss.h"
#include "../Mode/ModePause.h"
#include "../CharaData/CharaData.h"
#include "../Player/PlayerStatus.h"
#include "../Boss/BossStatus.h"

/**
 * �Q�[�����[�h�N���X
 */
class ModeGame : public ModeBase{
	using base = ModeBase;

public:
	/**
	 * ������
	 * @return �����̐���
	 */
	bool Initialize() override;

	/**
	 * ��� 
	 * @return �����̐���
	 */
	bool Terminate() override;

	/**
	 * �t���[�������F�v�Z
	 * @return �����̐��� 
	 */
	bool Process() override;

	/**
	 * �t���[�������F�`��
	 * @return �����̐��� 
	 */
	bool Render() override;

	/**
	 * ���C�g�̃f�B�t���[�Y�J���[��ݒ肷��
	 * @param lightHandle ���C�g�n���h��
	 */
	void SetLightColorHandle(int lightHandle);

	Camera       _cam;
	ObjectServer _objServer;

	std::unique_ptr<CharaData> _charaData; // JSON�t�@�C������L�����f�[�^�ǂݍ���
	bool _stopObjProcess;       // �I�u�W�F�N�g�������X�g�b�v
	int _shadowMapHandle;
private:
	PlayerStatus _playerStatus;
	BossStatus   _bossStatus;
	
}; 
