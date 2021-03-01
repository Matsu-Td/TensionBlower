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
	friend Player;
public:
	PlayerAttack();
	~PlayerAttack();

	/**
	 * @brief ������
	 */
	void Initialize();

	/**
	 * @brief �ߐڍU���̃_���[�W�ʂ��ߐڍU���̎�ނɂ���Đؑ�
	 */
	void SwitchAttackDamage(Player* player);

	/**
     * @brief ���ݔ������̋ߐڍU���_���[�W�ʂ��Z�b�g����
	 * @param player �v���C���[�N���X�I�u�W�F�N�g�̃|�C���^
     * @param dmgHP   �V�[���h��Ԃ̃{�X�̃q�b�g�|�C���g�ɗ^����_���[�W��
     * @param dmgSld  �V�[���h��Ԃ̃{�X�̃V�[���h�ɗ^����_���[�W��
     * @param dmgNorm �V�[���h���Ȃ���Ԃ̃{�X�̃q�b�g�|�C���g�ɗ^����_���[�W��
     */
	void SetAttackDamage(Player* player, int dmgHP, int dmgSld, int dmgNorm);

	/**
     * @brief ���ߐڍU���ւ̔h���֘A����
     * @param attackEnergy �w�肳�ꂽ���ߐڍU���ł̏���G�l���M�[��
     * @param nextState    �h�����鋭�ߐڍU���̎��
     * @param attackName   �h�����鋭�ߐڍU���̖��O(�U�����[�V�������ԃZ�b�g�p)
     */
	void NextStrongAttack(Player* player,int attackEnergy, Player::STATE nextState, std::string attackName);

	/**
	 * @brief ��ߐڍU���ւ̔h���֘A����
	 * @param nextState    �h�������ߐڍU���̎��
	 * @param attackName   �h�������ߐڍU���̖��O(�U�����[�V�������ԃZ�b�g�p)
	 */
	void NextWeakAttack(Player* player, Player:: STATE nextState, std::string attackName);
	
	/**
	 * @brief �e�ߐڍU���ւ̃L�[���͏���
	 */
	void AttackAction(Player* player);

	/**
     * @brief �ߐڍU������(����̂�)
     */
	void FirstAttack(Player* player);

	/**
     * @brief �ߐڍU������(2���ڈȍ~)
     */
	void SecondAttack(Player* player);

	static constexpr int RECEPTION_TIME = 30;   // ���ߐڍU����t����
	static constexpr int ATTACK_RELOAD_TIME = 90;   // �ߐځE�ˌ��U�������[�h����
};