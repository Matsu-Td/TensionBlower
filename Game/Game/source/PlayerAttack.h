#pragma once

/**
 * @file  PlayerAttack.h
 * @brief �v���C���[�ߐڍU������
 *
 * @date 2021-02-10
 */

#include "Player.h"

class PlayerAttack{
	friend Player;
public:
	PlayerAttack();
	~PlayerAttack();

	void Initialize();
	/**
	 * �ߐڍU���̃_���[�W�ʂ��ߐڍU���̎�ނɂ���Đؑ�
	 */
	void SwitchAttackDamage(Player* player);

	/**
     * ���ݔ������̋ߐڍU���_���[�W�ʂ��Z�b�g����
	 * @param player �v���C���[�N���X�I�u�W�F�N�g�̃|�C���^
     * @param dmgHP   �V�[���h��Ԃ̃{�X�̃q�b�g�|�C���g�ɗ^����_���[�W��
     * @param dmgSld  �V�[���h��Ԃ̃{�X�̃V�[���h�ɗ^����_���[�W��
     * @param dmgNorm �V�[���h���Ȃ���Ԃ̃{�X�̃q�b�g�|�C���g�ɗ^����_���[�W��
     */
	void SetAttackDamage(Player* player, int dmgHP, int dmgSld, int dmgNorm);

	/**
     * ���ߐڍU���ւ̔h���֘A����
     * @param attackEnergy �w�肳�ꂽ���ߐڍU���ł̏���G�l���M�[��
     * @param nextState    �h�����鋭�ߐڍU���̎��
     * @param attackName   �h�����鋭�ߐڍU���̖��O(�U�����[�V�������ԃZ�b�g�p)
     */
	void NextStrongAttack(Player* player,int attackEnergy, Player::STATE nextState, std::string attackName);

	/**
	 * ��ߐڍU���ւ̔h���֘A����
	 * @param nextState    �h�������ߐڍU���̎��
	 * @param attackName   �h�������ߐڍU���̖��O(�U�����[�V�������ԃZ�b�g�p)
	 */
	void NextWeakAttack(Player* player, Player:: STATE nextState, std::string attackName);
	
	/**
	 * �e�ߐڍU���ւ̃L�[���͏���
	 */
	void AttackAction(Player* player);

	/**
     * �ߐڍU������(����̂�)
     */
	void FirstAttack(Player* player);

	/**
     * �ߐڍU������(2���ڈȍ~)
     */
	void SecondAttack(Player* player);
	int a = 0;
	// �ߐڍU���֘A
//	bool _attackFlag;      // �U�������t���O(�U��������)
//	int _attackCnt;        // �U���J�ځA�I���J�E���g(�U�����[�V�������Đ����Ԃ���)
//	int _attackReloadTime; // �ߐڍU���p�����[�h����(�����[�h���͋ߐڍU���s��)
//	int _receptionTime;    // ���̋ߐڍU���J�ڎ�t����
//	int _canHitFlag;       // �ߐڍU�������蔻���(true:�\, false:�s��)
//	std::unordered_map<std::string, int> _attackTotalTime;  // �e�U�����[�V�����̑��Đ����Ԃ��i�[����

//	static constexpr int ATTACK_NUM = 8;  // �ߐڍU���̎�ނ̐�
//	std::string AttackName[ATTACK_NUM] =  // �e�ߐڍU���̖��O���i�[
//	{ "weak_atck1" ,"weak_atck2" ,"weak_atck3" ,"weak_atck4", 
//	  "strg_atck1", "strg_atck2", "strg_atck3", "strg_atck4" };
	static constexpr int RECEPTION_TIME = 30;   // ���ߐڍU����t����
	static constexpr int ATTACK_RELOAD_TIME = 90;   // �ߐځE�ˌ��U�������[�h����
};