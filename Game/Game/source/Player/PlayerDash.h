/**
 * @file   PlayerDash.h
 * @brief  �v���C���[�_�b�V������
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"
#include "Player.h"

/**
 * @brief �v���C���[�_�b�V������
 */
class PlayerDash {
public:
	/**
     * @brief �J�������b�N���̈ړ��A�_�b�V�����[�V�����ؑ֏����^
     * @brief ���A�i���O�X�e�B�b�N�̓|�����p�x�ɂ���ăL�����̏�ԁA���[�V������J��
	 * @param player �v���C���[�N���X�I�u�W�F�N�g�̃|�C���^
     * @param length  := sqrt(lx * lx + ly * ly) ���A�i���O�X�e�B�b�N�̓��͒l
     */
	void LeftAnalogDeg(Player* player, float length);

	/**
	 * @brief �_�b�V������
	 * @param player �v���C���[�N���X�I�u�W�F�N�g�̃|�C���^
	 * @param nowAngle �v���C���[�������Ă������(�p�x)
	 * @param length  := sqrt(lx * lx + ly * ly) ���A�i���O�X�e�B�b�N�̓��͒l
	 */
	void Dash(Player* player, float nowAngle, float length);

private:
	static constexpr int SHORT_DASH_CNT   = 10;   // �Z�����_�b�V���ړ�����
	static constexpr int ANALOG_REG_FOR   = 120;  // ���A�i���O�X�e�B�b�N��|���O��������̊p�x�͈�(�^�[�Q�b�g���b�N���̂ݎg�p)
	static constexpr int ANALOG_REG_OTHER = 45;   // ���A�i���O�X�e�B�b�N��|���O�����ȊO�̊p�x�͈�(�^�[�Q�b�g���b�N���̂ݎg�p)
	static constexpr float ANALOG_MIN = 0.3f; // �A�i���O�X�e�B�b�N���͔����̍ŏ��l
	
};