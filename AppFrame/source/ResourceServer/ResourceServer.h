/**
 * @file  ResourceServer.h
 * @brief ���\�[�X�Ǘ��N���X
 *
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#pragma once

#include <unordered_map>

/**
 * @brief ���\�[�X�Ǘ��N���X
 */
class ResourceServer {
public:
	/**
	 * @brief ������
	 */
	static void	Init();

	/**
	 * @brief ClearGraph()�Ăяo���A���ׂẴf�[�^�폜
	 */
	static void	Release();

	/**
	 * @brief ���ׂẴf�[�^�폜
	 */
	static void	ClearGraph();

	/**
	 * @brief �摜�f�[�^�ǂݍ���
	 * @param fileName �ǂݍ��މ摜�f�[�^�̕�����|�C���^
	 * @return �摜�̃n���h��
	 */
	static int LoadGraph(const TCHAR* fileName);

	/**
	 * @brief �摜�f�[�^�����ǂݍ���
	 * @param fileName �ǂݍ��މ摜�f�[�^�̕�����|�C���^
	 * @param allNum �摜�̕�������
	 * @param xNum �摜�̉������ɑ΂��镪����
	 * @param yNum �摜�̏c�����ɑ΂��镪����
	 * @param xSize �������ꂽ�摜1�̉������̑傫��
	 * @param ySize �������ꂽ�摜1�̏c�����̑傫��
	 * @param handleBuf �ǂݍ��񂾃O���t�B�b�N�n���h����ۑ�����int�^�z��ւ̃|�C���^
	 * @return �摜�̃n���h��
	 */
	static int LoadDivGraph(const TCHAR* fileName, int allNum,
	int xNum, int yNum, int xSize, int ySize, int* handleBuf);

	/**
	 * @brief �����f�[�^�ǂݍ���
	 * @param fileName �ǂݍ��ރf�[�^�̕�����|�C���^
	 * @return �����f�[�^�̃n���h��
	 */
	static int LoadSoundMem(const TCHAR* fileName);

	/**
	 * @brief 3D���f���f�[�^�ǂݍ���
     * @param fileName �ǂݍ��ރf�[�^�̕�����|�C���^
     * @return ���f���̃n���h��
	 */
	static int MV1LoadModel(const TCHAR* fileName);

	/**
	 * @brief �G�t�F�N�g�f�[�^�ǂݍ���
	 * @param  fileName  �ǂݍ��ރf�[�^�̕�����|�C���^
	 * @param  mag�@�G�t�F�N�g�̊g�嗦
	 * @return �G�t�F�N�g�̃n���h��
	 */
	static int LoadEffekseerEffect(const char* fileName, float mag);

private:
	static std::unordered_map<std::string, int>	_mapGraph;         // �摜�f�[�^�i�[

	struct DIVGRAPH {
		int		allNum;
		int*	handle;
	};
	static std::unordered_map<std::string, DIVGRAPH> _mapDivGraph; // �����摜�f�[�^�i�[

	static std::unordered_map<std::string, int>	_mapSound;   // �����f�[�^�i�[
	static std::unordered_map<std::string, int>	_mapModel;   // ���f���f�[�^�i�[
	static std::unordered_map<std::string, int>	_mapEffect;  // �G�t�F�N�g�f�[�^�i�[
};

