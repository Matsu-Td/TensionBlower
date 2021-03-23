/**
 * @file   ModeRanking.h
 * @brief  �����L���O���
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appframe.h"

class ModeRanking : public ModeBase{
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
