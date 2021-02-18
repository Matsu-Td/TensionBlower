#pragma once

/**
 * @file ObjectServer.h
 * @brief �I�u�W�F�N�g�T�[�o�[
 * 
 * @date 2021-01-15
 */

#include <vector>
#include "ObjectBase.h"

class ObjectServer {
public:
	ObjectServer();
	~ObjectServer();

	/**
	 * �o�^�����I�u�W�F�N�g��Process()��o�^���ɉ�
	 */
	void Process();

	/**
	 * �o�^�����I�u�W�F�N�g�� Render()��o�^���ɉ�
	 */
	void Render();

	/**
	 * Add���X�g�ɃI�u�W�F�N�g��ǉ�����
	 */
	void Add(ObjectBase* obj);

	/**
	 * Del���X�g�ɃI�u�W�F�N�g��ǉ�����
	 */
	void Del(ObjectBase* obj);

	/**
	 * ���X�g�ɓo�^����Ă���I�u�W�F�N�g��S�č폜
	 */
	void Clear();

	/**
	 * _vObject���X�g��߂�l�Ƃ��ĕԂ� 
	 * @return _vObject���X�g
	 */
	std::vector<ObjectBase*>* List() { return &_vObject; }

private:
	/**
	 * Add���X�g�̃I�u�W�F�N�g��ǉ�����
	 */
	void AddListObjects();

	/**
	 * Del���X�g�̃I�u�W�F�N�g��ǉ�����
	 */
	void DelListObjects();

protected:
	std::vector<ObjectBase*> _vObject; // ObjectBase��o�^���郊�X�g
	std::vector<ObjectBase*> _vAdd;    // �ǉ�����I�u�W�F�N�g���X�g
	std::vector<ObjectBase*> _vDel;	   // �폜����I�u�W�F�N�g���X�g
};
