/**
 * @file   ModeAmgLogo.h
 * @brief  AMG���S�\��
 * 
 * @author matsuo tadahiko
 * @date   2021/03/07
 */

#pragma once
#include "appframe.h"

class ModeAmgLogo :public ModeBase {
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
	int _bg;      // �w�i
	int _cg;      // �摜
	int _mode;    // �t�F�[�h���䃂�[�h
	int _fadeCnt; // �t�F�[�h�J�E���g 
	int _dispCnt; // �\���J�E���g
	int _alpha;   // �摜�̃��l

	static constexpr int MAX_ALPHA = 255;    // �摜���l�̍ő�l
	static constexpr int MAX_FADE_CNT = 30;  // �t�F�[�h�J�E���g�ő�l
	static constexpr int MAX_DISP_CNT = 90;  // �`��J�E���g�ő�l
	static constexpr int LOGO_POS_X = 460;   // ���S�摜X���W
	static constexpr int LOGO_POS_Y = 425;   // ���S�摜Y���W
};