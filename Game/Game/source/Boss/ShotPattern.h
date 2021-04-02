/**
 * @file   ShotPattern.h
 * @brief  �e���p�^�[������
 * 
 * @author matsuo tadahiko
 * @date   2021/03/22
 */

#pragma once

#include "Boss.h"

/**
 * �e���p�^�[������
 */
class ShotPattern {
public:
	/**
     * @brief �e���p�^�[���ؑ֏���
     */
	void ShotPatternSwitch(Boss* boss);
	/**
     * @brief �e���p�^�[��1&2
     */
	void ShotPattern1and2(Boss* boss);

	/**
	 * @brief �e���p�^�[��3
	 */
	void ShotPattern3(Boss* boss);

	/**
	 * @brief �e���p�^�[��4-1
	 */
	void ShotPattern4_1(Boss* boss);

	/**
	 * @brief �e���p�^�[��4-2
	 */
	void ShotPattern4_2(Boss* boss);

	/**
	 * @brief �e���p�^�[��5
	 */
	void ShotPattern5(Boss* boss);

	/**
	 * @brief �e���p�^�[��6
	 */
	void ShotPattern6(Boss* boss);

	/**
	 * @brief �e���p�^�[��7
	 */
	void ShotPattern7(Boss* boss);

	/**
	 * @brief ���[�U�[�U��1-1
	 */
	void LaserAttack1_1(Boss* boss);

	/**
	 * @brief ���[�U�[�U��1-2
	 */
	void LaserAttack1_2(Boss* boss);

	/**
	 * @brief ���[�U�[�U��2
	 */
	void LaserAttack2(Boss* boss);

private:
	static constexpr int PATTERN_CHANGE_CNT = 240; // �e���p�^�[����ω�������J�E���g�ő�l
	static constexpr int SHOT_REVERSE_CNT = 90;    // �e����]������ω�������J�E���g�ő�l
	static constexpr float SHOT_DISTANCE = 10.0f;  // �e���𔭐�������ʒu(�{�X���S����̋���)
};
