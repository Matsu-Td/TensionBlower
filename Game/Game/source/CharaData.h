#pragma once

/**
 * @file  CharaData.h
 * @brief �L�����f�[�^(�v���C���[�A�{�X)JSON�t�@�C���ǂݍ��ݏ���
 * 
 * @date 2021-02-08
 */

#include "appframe.h"

class CharaData{
public:
	CharaData(std::string filePath, std::string fileName);
	~CharaData();

	/**
	* �v���C���[�f�[�^
	*/
	int _maxHP;         // �ő�HP
	int _maxEnergy;     // �ő�G�l���M�[
	float _mvSpdNorm;   // �ړ����x(�ʏ���)
	float _mvSpdChrg;   // �ړ����x(���ߏ��)  
	float _mvSpdDash;   // �ړ����x(�_�b�V�����)

	int _egJump;        // �G�l���M�[����ʁF�W�����v
	int _egDash;        // �G�l���M�[����ʁF�_�b�V��
	int _egMLS;         // �G�l���M�[����ʁF�}���`���b�N�V�X�e��
	int _egAtck1;       // �G�l���M�[����ʁF���ߐڍU��1
	int _egAtck2;       // �G�l���M�[����ʁF���ߐڍU��2
	int _egAtck3;       // �G�l���M�[����ʁF���ߐڍU��3
	int _egAtck4;       // �G�l���M�[����ʁF���ߐڍU��4

	int _egAutoRec;     // �G�l���M�[�񕜗ʁF������
	float _egAutoXChrg; // �G�l���M�[�񕜗ʁF���ߍs��
	int _egAutoXArea;   // �G�l���M�[�񕜗ʁF�{�X�t�߂ł̍s��
	int _egAvoid;       // �G�l���M�[�񕜗ʁF�{�X�̒e�J�X������
	int _egShotNum;     // �G�l���M�[�񕜗ʁF�{�X�_�E�����̋z�������e1������

	int _wkDmgHP1;      // HP�_���[�W��(�V�[���h�L)�F��ߐڍU��1
	int _wkDmgHP2;      // HP�_���[�W��(�V�[���h�L)�F��ߐڍU��2
	int _wkDmgHP3;      // HP�_���[�W��(�V�[���h�L)�F��ߐڍU��3
	int _wkDmgHP4;      // HP�_���[�W��(�V�[���h�L)�F��ߐڍU��4
	int _stDmgHP1;      // HP�_���[�W��(�V�[���h�L)�F���ߐڍU��1
	int _stDmgHP2;      // HP�_���[�W��(�V�[���h�L)�F���ߐڍU��2
	int _stDmgHP3;      // HP�_���[�W��(�V�[���h�L)�F���ߐڍU��3
	int _stDmgHP4;      // HP�_���[�W��(�V�[���h�L)�F���ߐڍU��4
	int _shotDmgHP;     // HP�_���[�W��(�V�[���h�L)�F�ˌ��U�� 
	int _repelDmgHP;    // HP�_���[�W��(�V�[���h�L)�F�e���Ԃ�

	int _wkDmgSld1;     // �V�[���h�_���[�W�ʁF��ߐڍU��1
	int _wkDmgSld2;     // �V�[���h�_���[�W�ʁF��ߐڍU��2
	int _wkDmgSld3;     // �V�[���h�_���[�W�ʁF��ߐڍU��3
	int _wkDmgSld4;     // �V�[���h�_���[�W�ʁF��ߐڍU��4
	int _stDmgSld1;     // �V�[���h�_���[�W�ʁF���ߐڍU��1
	int _stDmgSld2;     // �V�[���h�_���[�W�ʁF���ߐڍU��2
	int _stDmgSld3;     // �V�[���h�_���[�W�ʁF���ߐڍU��3
	int _stDmgSld4;     // �V�[���h�_���[�W�ʁF���ߐڍU��4
	int _shotDmgSld;    // �V�[���h�_���[�W�ʁF�ˌ��U��
	int _repelDmgSld;   // �V�[���h�_���[�W�ʁF�e���Ԃ�

	int _wkDmg1;        // HP�_���[�W��(�V�[���h��)�F��ߐڍU��1
	int _wkDmg2;        // HP�_���[�W��(�V�[���h��)�F��ߐڍU��2
	int _wkDmg3;        // HP�_���[�W��(�V�[���h��)�F��ߐڍU��3
	int _wkDmg4;        // HP�_���[�W��(�V�[���h��)�F��ߐڍU��4
	int _stDmg1;        // HP�_���[�W��(�V�[���h��)�F���ߐڍU��1
	int _stDmg2;        // HP�_���[�W��(�V�[���h��)�F���ߐڍU��2
	int _stDmg3;        // HP�_���[�W��(�V�[���h��)�F���ߐڍU��3
	int _stDmg4;        // HP�_���[�W��(�V�[���h��)�F���ߐڍU��4
	int _shotDmg;       // HP�_���[�W��(�V�[���h��)�F�ˌ��U��
	int _repelDmg;      // HP�_���[�W��(�V�[���h��)�F�e���Ԃ�

	/**
	* �{�X�f�[�^
	*/
	struct BOSS {
		int maxHP;       // �ő�HP
		int maxShield;   // �ő�V�[���h�l
		int shotDmg;     // �_���[�W�ʁF�e��(�e1������)
		int exolosionDmg;// �_���[�W�ʁF�U��
		int laserDmg;    // �_���[�W�ʁF���[�U�[
	};
	BOSS _boss;

private:
	std::string StringFileLoad(std::string fileName);
	int JsonLoad(std::string filePath, std::string fileName);
};
