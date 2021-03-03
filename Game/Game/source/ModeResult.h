/**
 * @file   ModeResult.h
 * @brief  ���U���g���
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appframe.h"

class ModeResult : public ModeBase{
	typedef ModeBase base;

public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:
	int _cg;          // �摜
	int _timeScore;   // �X�R�A�F�o�ߎ��ԗp
	int _hpScore;     // �X�R�A�F�c��HP�ʗp
	int _repelScore;  // �X�R�A�F���e����
	int _energyScore; // �X�R�A�F���l���G�l���M�[�ʗp
	int _allScore;    // �X�R�A�F���X�R�A(�S�X�R�A�̍��v)

	static constexpr int MMSEC2SEC = 1000;      // �~���b�˕b�ϊ��p
	static constexpr int MAX_SCORE = 100000;    // �X�R�A�ő�l(�o�ߎ��ԁA�c��HP�ʗp)
	static constexpr int TIME_LOWER_LIMIT = 120;
};
