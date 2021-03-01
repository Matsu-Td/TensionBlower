#pragma once

/**
 * @file CFile.h
 * @brief �O���t�@�C���̓ǂݍ��݁A��������
 *
 * @date 2020-12-18
 */

#include <string>

class CFile{
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

	std::string	FileName() { return _fileName; }
	void* Data() { return _data; }
	std::string DataStr() { return std::string(_data); }
	int Size() { return _size; }
	bool Success() { return _success; }

private:
	void Init();

	std::string	_fileName;

	int	  _size;
	char* _data;
	bool  _success;
};
