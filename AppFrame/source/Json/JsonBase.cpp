#define	_CRT_SECURE_NO_WARNINGS
#include "JsonBase.h"
#include "../picojson/picojson.h"
#include <iostream>

JsonBase::JsonBase(std::string filePath, std::string tiledFileName)
{
	
}

JsonBase::~JsonBase()
{

}

std::string JsonBase::StringFileLoad(std::string filePath, std::string strFileName)
{
	
	FILE* fp;
	fp = fopen(strFileName.c_str(), "rb");
	if (fp == NULL)
	{
		// �t�@�C�����J���Ȃ�����
		return "";
	}
	// �t�@�C���̃T�C�Y���擾
	fseek(fp, 0, SEEK_END); int size = ftell(fp); fseek(fp, 0, SEEK_SET);

	char* p;
	p = new char[size + 1];
	fread(p, 1, size, fp);

	fclose(fp);
	p[size] = '\0';

	// �ǂݍ��񂾃f�[�^��string�ɂ���
	std::string s = (char*)p;

	delete[] p;

	return s;
}
