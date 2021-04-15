/**
 * @file  CFile.h
 * @brief �O���t�@�C���ւ̃A�N�Z�X(�ǂݏ���)
 *
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#pragma once

#include <string>

namespace cfile {

	/**
	 * @brief �O���t�@�C���ւ̃A�N�Z�X(�ǂݏ���)
	 */
	class CFile {
	public:
		/**
		 * @brief �t�@�C���ǂݍ���
		 * @param fileName �t�@�C����
		 */
		CFile(const std::string fileName);

		/**
		 * @brief �t�@�C����������
		 * @param fileName �t�@�C����
		 * @param data �f�[�^�i�[
		 * @param size �������ރf�[�^�T�C�Y
		 */
		CFile(const std::string fileName, void* data, int size);		// �o�C�i���f�[�^

		~CFile();

		/**
		 * @brief  �t�@�C���̖��O��Ԃ�
		 * @return �t�@�C����
		 */
		std::string	FileName() const { return _fileName; }

		/**
		 * @brief  �t�@�C���̃f�[�^��Ԃ�
		 * @return �t�@�C���f�[�^
		 */
		void* Data() const { return _data; }

		/**
		 * @brief  �t�@�C���f�[�^�𕶎���Ƃ��ĕԂ�
		 * @return �t�@�C���f�[�^�̕�����
		 */
		std::string DataStr() const { return std::string(_data); }

		/**
		 * @brief  �t�@�C���̃T�C�Y��Ԃ�
		 * @return �t�@�C���̃T�C�Y
		 */
		int Size() const { return _size; }

		/**
		 * @brief  �t�@�C�����J�������ǂ���
		 * @return ���ی���_success
		 */
		bool Success() const { return _success; }

	private:
		/**
		 * @brief ������
		 */
		void Init();

		std::string	_fileName; // �t�@�C����

		int	  _size;     // �t�@�C���̃T�C�Y
		char* _data;     // �t�@�C���f�[�^���i�[
		bool  _success;  // �t�@�C�����J�������ǂ���(true:�t�@�C�����J���̂ɐ���)
	};
}