/**
 * @file   ModePause.h
 * @brief  �|�[�Y���[�h�N���X
 * 
 * @author matsuo tadahiko
 * @date   2020/12/27
 */

#include "appframe.h"

/**
 * @brief �|�[�Y���[�h�N���X
 */
class ModePause : public ModeBase{
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
	int _cg;      // �摜
	int _ui[4];   // UI�摜
	int _menuPos; // �I���ʒu
};