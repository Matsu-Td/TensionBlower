/**
 * @file   ModeRanking.h
 * @brief  �����L���O���
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appframe.h"

class ModeRanking : public ModeBase{
	typedef ModeBase base;

public:
	/**
	 * @brief  ������
	 * @return �����̐���
	 */
	virtual bool Initialize();

	/**
	 * @brief  ���
	 * @return �����̐���
	 */
	virtual bool Terminate();

	/**
	 * @brief  �t���[�������F�v�Z
	 * @return �����̐���
	 */
	virtual bool Process();

	/**
	 * @brief  �t���[�������F�`��
	 * @return �����̐���
	 */
	virtual bool Render();

protected:
	int _cg;  // �摜
};
