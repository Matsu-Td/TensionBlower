/**
 * @file  CFile.cpp
 * @brief �O���t�@�C���ւ̃A�N�Z�X(�ǂݏ���)
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#include <fstream>
#include <iostream>
#include "CFile.h"
#include "../Utility/UtilMacro.h"

 /*
�@* �t�@�C���ǂݍ���
�@*/
CFile::CFile(const std::string fileName) {
	// �����o�̏�����
	Init();

	_fileName = fileName;

	// �t�@�C�����J��
	std::ifstream ifs(fileName, std::ios::in | std::ios::binary);	// ���͂��o�C�i���`����
	if (!ifs) {
		return;
	}

	// �t�@�C���T�C�Y�̎擾
	ifs.seekg(0, std::ios_base::end);
	_size = (int)ifs.tellg();
	ifs.seekg(0, std::ios_base::beg);

	// ���������m��
	_data = new char[_size + 1];

	ifs.read(_data, _size);

	ifs.close();

	// ������Ƃ��ė��p�ł���悤�ɁA�f�[�^�̖��[�� \0 ��t����
	_data[_size] = '\0';

	_success = true;
}

/*
 * �t�@�C����������
 */
CFile::CFile(const std::string fileName, void* data, int size) {
	// �����o�̏�����
	Init();

	_fileName = fileName;

	// �t�@�C�����J��
	std::ofstream ofs(fileName, std::ios::out | std::ios::binary);	// �o�͂��o�C�i���`����
	if (!ofs) {
		return;
	}

	// �f�[�^�̏�������
	ofs.write(static_cast<char*>(data), size);

	ofs.close();

	_success = true;
}

/*
 * ���
 */
CFile::~CFile() {
	SAFE_DELETE(_data);
}

/*
 * ������
 */
void CFile::Init() {
	_size = 0;
	_data = nullptr;
	_fileName = "";
	_success = false;
}
