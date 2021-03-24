/**
 * @file   ModeResult.h
 * @brief  ���U���g���
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appframe.h"

class ModeResult : public ModeBase{
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

private:
	int _cg;          // �摜
	int _timeScore;   // �X�R�A�F�o�ߎ��ԗp
	int _hpScore;     // �X�R�A�F�c��HP�ʗp
	int _repelScore;  // �X�R�A�F���e����
	int _energyScore; // �X�R�A�F���l���G�l���M�[�ʗp
	int _allScore;    // �X�R�A�F���X�R�A(�S�X�R�A�̍��v)

	const int MMSEC2SEC = 1000;      // �~���b�˕b�ϊ��p
	const int MAX_SCORE = 100000;    // �X�R�A�ő�l(�o�ߎ��ԁA�c��HP�ʗp)
	const int TIME_LOWER = 120;      // �o�ߎ��ԃX�R�A�v�Z�p
};
