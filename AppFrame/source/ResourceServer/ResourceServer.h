#pragma once

/**
 * @file  ResourceServer.h
 * @brief ���\�[�X�Ǘ��T�[�o
 * @brief ���ׂĐÓI�����o�ō\������
 * 
 * @date 2020-12-18
 */

#include <unordered_map>

class ResourceServer {
public:
	static void	Init();

	/**
	 * ClearGraph()�Ăяo��
	 */
	static void	Release();

	/**
	 * ���ׂẴf�[�^�폜
	 */
	static void	ClearGraph();

	/**
	 * �摜�f�[�^�ǂݍ���
	 * @param fileName �ǂݍ��މ摜�f�[�^�̕�����|�C���^
	 */
	static int LoadGraph(const TCHAR* fileName);

	/**
	 * �摜�f�[�^�����ǂݍ���
	 * @param fileName �ǂݍ��މ摜�f�[�^�̕�����|�C���^
	 * @param allNum �摜�̕�������
	 * @param xNum �摜�̉������ɑ΂��镪����
	 * @param yNum �摜�̏c�����ɑ΂��镪����
	 * @param xSize �������ꂽ�摜1�̉������̑傫��
	 * @param ySize �������ꂽ�摜1�̏c�����̑傫��
	 * @param handleBuf �ǂݍ��񂾃O���t�B�b�N�n���h����ۑ�����int�^�z��ւ̃|�C���^
	 */
	static int LoadDivGraph(const TCHAR* fileName, int allNum,
		int xNum, int yNum, int xSize, int ySize, int* handleBuf);

	/**
	 * ���f�[�^�ǂݍ���
	 * @param fileName �ǂݍ��މ摜�f�[�^�̕�����|�C���^
	 */
	static int LoadSoundMem(const TCHAR* fileName);

	/**
	 * 3D���f���f�[�^�ǂݍ���
     * @param fileName �ǂݍ��މ摜�f�[�^�̕�����|�C���^
	 */
	static int MV1LoadModel(const TCHAR* fileName);

private:
	static std::unordered_map<std::string, int>	_mapGraph;         // �摜�f�[�^�i�[
	typedef struct {
		int		allNum;
		int*	handle;
	} DIVGRAPH;
	static std::unordered_map<std::string, DIVGRAPH> _mapDivGraph; // �����摜�f�[�^�i�[

	static std::unordered_map<std::string, int>	_mapSound;   // ���f�[�^�i�[
	static std::unordered_map<std::string, int>	_mapModel;   // ���f���f�[�^�i�[
};

