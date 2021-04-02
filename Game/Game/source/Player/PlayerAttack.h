/**
 * @file   PlayerAttack.h
 * @brief  �v���C���[�ߐڍU������
 * 
 * @author matsuo tadahiko
 * @date   2021/02/25
 */

#pragma once

#include "Player.h"

class PlayerAttack{
public:
	PlayerAttack();
	~PlayerAttack();

	/**
	 * �ߐڍU���̃_���[�W�ʂ��ߐڍU���̎�ނɂ���Đؑ�
	 * @param player  �v���C���[�N���X�I�u�W�F�N�g�̃|�C���^
	 */
	void SwitchAttackDamage(Player* player);

	/**
     * ���ݔ������̋ߐڍU���_���[�W�ʂ��Z�b�g����
	 * @param player  �v���C���[�N���X�I�u�W�F�N�g�̃|�C���^
     * @param dmgHP   �V�[���h��Ԃ̃{�X�̃q�b�g�|�C���g�ɗ^����_���[�W��
     * @param dmgSld  �V�[���h��Ԃ̃{�X�̃V�[���h�ɗ^����_���[�W��
     * @param dmgNorm �V�[���h���Ȃ���Ԃ̃{�X�̃q�b�g�|�C���g�ɗ^����_���[�W��
     */
	void SetAttackDamage(Player* player, int dmgHP, int dmgSld, int dmgNorm);

	/**
     * ���ߐڍU���ւ̔h���֘A����
     * @param player  �v���C���[�N���X�I�u�W�F�N�g�̃|�C���^
     * @param attackEnergy �w�肳�ꂽ���ߐڍU���ł̏���G�l���M�[��
     * @param nextState    �h�����鋭�ߐڍU���̎��
     * @param attackName   �h�����鋭�ߐڍU���̖��O(�U�����[�V�������ԃZ�b�g�p)
     */
	void NextStrongAttack(Player* player,int attackEnergy, Player::STATE nextState, std::string attackName);

	/**
	 * ��ߐڍU���ւ̔h���֘A����
	 * @param player  �v���C���[�N���X�I�u�W�F�N�g�̃|�C���^
	 * @param nextState    �h�������ߐڍU���̎��
	 * @param attackName   �h�������ߐڍU���̖��O(�U�����[�V�������ԃZ�b�g�p)
	 */
	void NextWeakAttack(Player* player, Player:: STATE nextState, std::string attackName);
	
	/**
	 * �e�ߐڍU���ւ̃L�[���͏���
	 * @param player  �v���C���[�N���X�I�u�W�F�N�g�̃|�C���^
	 */
	void AttackAction(Player* player);

	/**
     * �ߐڍU������(����̂�)
	 * @param player  �v���C���[�N���X�I�u�W�F�N�g�̃|�C���^
     */
	void FirstAttack(Player* player);

	/**
     * �ߐڍU������(2���ڈȍ~)
	 * @param player  �v���C���[�N���X�I�u�W�F�N�g�̃|�C���^
     */
	void SecondAttack(Player* player);

	/**
	 * �U���������̐��f�[�^���Đ�����
	 * @param player  �v���C���[�N���X�I�u�W�F�N�g�̃|�C���^
	 * @param voiceName �Đ����鐺�f�[�^�̖��O
	 */
	void PlayAttackVoice(std::string voiceName);

	/**
	 * ��ߐڍU���̃q�b�g���莞�Ԃ�ݒ肷��
	 * @param player  �v���C���[�N���X�I�u�W�F�N�g�̃|�C���^
	 */
	void SetWeakHitTime(Player* player);

	/**
	 * ���ߐڍU���̃q�b�g���莞�Ԃ�ݒ肷��
	 * @param player  �v���C���[�N���X�I�u�W�F�N�g�̃|�C���^
	 */
	void SetStrongHitTime(Player* player);

	static constexpr int RECEPTION_TIME = 30;      // ���ߐڍU����t����
	static constexpr int ATTACK_RELOAD_TIME = 90;  // �ߐځE�ˌ��U�������[�h����
};