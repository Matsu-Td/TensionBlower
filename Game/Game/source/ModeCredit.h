/**
 * @file   ModeCredit.h
 * @brief  �N���W�b�g���
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appframe.h"

class ModeCredit : public ModeBase{
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
	int _cg;  // �摜
};
