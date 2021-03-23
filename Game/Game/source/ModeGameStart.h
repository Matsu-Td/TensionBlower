/**
 * @file   ModeGameStart.h
 * @brief  MISSION START�����\��
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appframe.h"

class ModeGameStart : public ModeBase{
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

protected:
	int _cg[2];   // �摜

	static constexpr int POS_Y = 390;  // �摜�`��ʒu�FY���W
};