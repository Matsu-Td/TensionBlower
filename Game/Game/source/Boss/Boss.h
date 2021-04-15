/**
 * @file   Boss.h
 * @brief  �{�X�N���X
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#pragma once

#include "appframe.h"
#include "../Object/ObjectBase.h"

namespace tensionblower {

	namespace boss {

		/**
		 * @brief �{�X�N���X
		 */
		class Boss : public ObjectBase {
		public:
			Boss();
			~Boss();

			OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS; }

			/**
			 * @brief ������
			 */
			void Initialize() override;

			/**
			 * @brief �t���[�������F�v�Z
			 */
			void Process() override;

			/**
			 * @brief �t���[�������F�`��
			 */
			void Render() override;

			/**
			 * @brief  �q�b�g�|�C���g�l�擾
			 * @return �q�b�g�|�C���g
			 */
			int GetHitPoint() const { return _hitpoint; }

			/**
			 * @brief  �V�[���h�l�擾
			 * @return �V�[���h�l
			 */
			int GetShield() const { return _shield; }

			/**
			 * @brief  �t�F�[�Y���擾
			 * @return ���݂̃t�F�[�Y
			 */
			int GetPhaseNo() const { return _phaseNo; }

			/**
		�@�@ * @brief �v���C���[�ɒe���Ԃ��ꂽ�e�ɂ��_���[�W����
			 */
			void RepelDamage();

			/**
			 * @brief �v���C���[����󂯂��_���[�W�ʌv�Z
			 */
			void AttackDamage();

			/**
			 * @brief �q�b�g�|�C���g�ւ̔����_���[�W
			 */
			void ExplosionDamageHP();

			/**
			 * @brief �V�[���h�ւ̔����_���[�W
			 */
			void ExplosionDamageShield();

			/**
			 * @brief Boss�C���X�^���X���擾����
			 */
			static Boss* GetInstance() { return _pInstance; }

			static Boss* _pInstance;

			// �v���C���[�N���X�Ŏg�p
			int  _bulletNum;     // �_�E�����O�ɏo�����Ă����e�̐��J�E���g
			bool _mlsDownFlag;   // MLS�Œe���Ԃ��ꂽ�e�Ń_�E������Ɓutrue�v

			/**
			 * @brief ���
			 */
			enum class STATE {
				NORMAL,  // �ʏ�
				DOWN,    // �_�E��
				RETURN,  // ���A
				DEATH,   // ���S
			};
			STATE GetState() const { return _state; };

		private:
			/**
			 * @brief �ʏ��ԏ���
			 */
			void StateNormal();

			/**
			 * @brief �_�E����ԏ���
			 */
			void StateDown();

			/**
			 * @brief ���A��ԏ���
			 */
			void StateReturn();

			/**
			 * ���[�V�����ؑ�
			 * @param  oldState �����O�̏��
			 */
			void MotionSwitch();

			/**
			 * @brief ���S����
			 */
			void Death();

			/**
			 * @brief �e���̒e�𐶐�����
			 * @param posY �e�̐�������Y���W(����)
			 * @param shotSpd �e�̈ړ����x
			 * @param ShotAngle �e�𐶐�����p�x�A�ʒu
			 */
			void ShotGeneration(float posY, float shotSpd, float shotAngle);

			/**
			 * @brief ���[�U�[�𐶐�����
			 * @param laserAngle ���[�U�[�̔��ˊp�x�A�ʒu
			 * @param roteSpd ���[�U�[�̔��ˈʒu����]���鑬�x(�f�t�H���g:1.0f)
			 */
			void LaserGeneration(float laserAngle, float roteSpd = 1.0f);

			/**
			 * @brief �e���p�^�[���ؑ֏���
			 */
			void BarragePatternSwitch();
			/**
			 * @brief �e���p�^�[��1&2
			 * @brief �{�X�𒆐S�Ƃ��Ĕ��ˈʒu����]�����Ȃ���8�̒e�𓯎��ɔ��˂���
			 */
			void BarragePattern1and2();

			/**
			 * @brief �e���p�^�[��3
			 * @brief �{�X�𒆐S�Ƃ��Ĕ��ˈʒu����]�����Ȃ���8�̒e�𓯎��ɔ��˂���
			 * @brief �Z�������ŉ�]������ω������A�e�����ɔg�ł悤�Ȓe���𔭐�������
			 */
			void BarragePattern3();

			/**
			 * @brief �e���p�^�[��4-1
			 * @brief �{�X�𒆐S�Ƃ��Ĕ��ˈʒu�������ɉ�]�����Ȃ���8�̒e�𓯎��ɔ��˂���
			 */
			void BarragePattern4_1();

			/**
			 * @brief �e���p�^�[��4-2
			 * @brief �{�X�𒆐S�Ƃ��Ĕ��ˈʒu���E���ɉ�]�����Ȃ���8�̒e�𓯎��ɔ��˂���
			 */
			void BarragePattern4_2();

			/**
			 * @brief �e���p�^�[��5
			 * @brief ������7���̒e�𔭎�
			 * @brief �ׂ荇���e�̍��፷�����ɂ����܂ܔ��ˈʒu�����X�ɕω������A
			 * @brief �����ɔg�łe���𔭐�������
			 */
			void BarragePattern5();

			/**
			 * @brief �e���p�^�[��6
			 * @brief ������3�����ˁA�v���C���[��_�����U��
			 */
			void BarragePattern6();

			/**
			 * @brief �e���p�^�[��7
			 * @brief �{���ɂ��U��
			 */
			void BarragePattern7();

			/**
			 * @brief ���[�U�[�U��1-1
			 * @brief ���[�U�[1�{�������A���ˈʒu���{�X�𒆐S�ɍ����ɉ�]������
			 */
			void LaserAttack1_1();

			/**
			 * @brief ���[�U�[�U��1-2
			 * @brief ���[�U�[1�{�������A���ˈʒu���{�X�𒆐S�ɉE���ɉ�]������
			 */
			void LaserAttack1_2();

			/**
			 * @brief ���[�U�[�U��2
			 * @brief ���ˈʒu���{�X�𒆐S�ɁA������4�{�̃��[�U�[�𔭎˂���
			 */
			void LaserAttack2();

			/**
			 * @brief �t�F�[�Y�ύX����
			 */
			void FhaseChange();

			/**
			 * @brief 6��ނ̐��f�[�^�������_���ōĐ�
			 */
			void PlayAttackVoiceChange();

			/**
			 * @brief ���f�[�^�Đ�
			 * @param voiceName ���f�[�^�̖��O
			 */
			void PlayVoice(std::string voiceName);

			/**
			 * @brief �{�X���ʕ�����]����
			 * @param rotSpdChenge ��]���x�ؑ֗p
			 */
			void DirectionalRotation(float rotSpdChange);

		private:
			int   _hitpoint;      // �q�b�g�|�C���g�l
			int   _shield;        // �V�[���h�l
			int   _downTime;      // �_�E������
			int   _deathCnt;      // ���S�J�E���g
			bool  _stateDown;     // �_�E����Ԃ�(true:�_�E�����)
			float _sinCnt;        // �㉺�^���p�T�C���g�J�E���g

			int   _shotCnt;       // �e�����˃^�C�~���O�J�E���g
			int   _mlsCnt;        // �}���`���b�N�I���V�X�e���������̃J�E���g
			int   _reverseCnt;    // �e����]���������]����J�E���g
			int   _patternRandom; // �e���p�^�[��3�탉���_���Őؑ�
			int   _phaseNo;       // �t�F�[�Y�FHP�c�ʂŕω�
			float _shotAngle;     // �e���̔��ˊp�x
			float _shotAngleUp;   // �ʏ�̒e���̏㑤�ɔ�������e���̔��ˊp�x(�e���p�^�[��4�p)
			float _setRotAngle;   // ���ˈ��p�x�Z�b�g
			float _shotHeight;    // �e���𔭎˂��鍂��
			float _laserAngle;    // ���[�U�[�̔��ˊp�x

			static const int ATTACK_VOICE_NUM = 6;        // �U�����̐��f�[�^����
			std::string _attackNameNo[ATTACK_VOICE_NUM] = // �U�����̐��f�[�^�̖��O���i�[
			{ "attack1","attack1" ,"attack2" ,"attack4" ,"attack5" ,"attack6" };

			STATE  _state;    // ���
			STATE  _oldState; // �����O�̏��
			VECTOR _cross;    // �O��(�{�X�̌�����]�v�Z�p)

			const int PHASE_ONE_HP       = 4000; // �t�F�[�Y1�ֈڍs����c��HP��
			const int PHASE_TWO_HP       = 3000; // �t�F�[�Y2�ֈڍs����c��HP��
			const int PHASE_THREE_HP     = 2000; // �t�F�[�Y3�ֈڍs����c��HP��
			const int PHASE_FOUR_HP      = 1000; // �t�F�[�Y4�ֈڍs����c��HP��
			const int MIN_DOWN_TIME      = 180;  // �_�E�����ԍŏ��l(�_�E�����Ԍv�Z�p)
			const int PATTERN_CHANGE_CNT = 240;  // �e���p�^�[����ω�������J�E���g�ő�l
			const int SHOT_REVERSE_CNT   = 90;   // �e����]������ω�������J�E���g�ő�l
			const int EXPLOSION_DMG_NORM = 2;    // ����HP�_���[�W�ʁF�ʏ펞(�V�[���h��)
			const int EXPLOSION_DMG_HP   = 1;    // ����HP�_���[�W��(�V�[���h�L)
			const int EXPLOSION_DMG_SLD  = 2;    // �����V�[���h�_���[�W��(�V�[���h�L)
		
			const float ADD_POS_Y     = 9.0f;    // �����蔻��pY���W���Z�l
			const float ROT_SPD       = 0.01f;   // �{�X�̌�����]�p�p���x
			const float SHOT_DISTANCE = 10.0f;   // �e���𔭐�������ʒu(�{�X���S����̋���)
			const float LESER_POS_Y   = 4.5f;    // ���[�U�[�𔭎˂���ʒuY���W(����)
			const float SHOT_Y_MAX    = 12.0f;   // �e���̍������
		};
	}
}