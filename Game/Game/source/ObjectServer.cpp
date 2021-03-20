
/**
 * @file ObjectServer.cpp
 * @brief �I�u�W�F�N�g�Ǘ��T�[�o�[
 *
 * @date 2021-01-15
 */

#include "DxLib.h"
#include "ObjectServer.h"

ObjectServer::ObjectServer() {

	_vObject.clear();
	_vAdd.clear();
	_vDel.clear();
}

ObjectServer::~ObjectServer() {

	Clear();
}

/**
 * ���X�g�ɓo�^����Ă���I�u�W�F�N�g��S�č폜
 */
void ObjectServer::Clear() {

	for (auto itr = _vObject.begin(); itr != _vObject.end(); itr++) {
		delete(*itr);
	}
	_vObject.clear();
}

/**
 * Add���X�g�ɃI�u�W�F�N�g��ǉ�����
 */
void ObjectServer::Add(ObjectBase* obj) {

	_vAdd.push_back(obj);
}

/**
 * Del���X�g�ɃI�u�W�F�N�g��ǉ�����
 */
void ObjectServer::Del(ObjectBase* obj) {

	_vDel.push_back(obj);
}

/**
 * Add���X�g�̃I�u�W�F�N�g��ǉ�����
 */
void ObjectServer::AddListObjects() {

	for (auto itrAdd = _vAdd.begin(); itrAdd != _vAdd.end(); itrAdd++) {
		_vObject.push_back((*itrAdd));
	}
	_vAdd.clear();
}

/**
 * Del���X�g�̃I�u�W�F�N�g��ǉ�����
 */
void ObjectServer::DelListObjects() {

	for (auto itrDel = _vDel.begin(); itrDel != _vDel.end(); ++itrDel) {
		for (auto itr = _vObject.begin(); itr != _vObject.end();) {
			if ((*itr) == (*itrDel)) {
				delete (*itr);
				itr = _vObject.erase(itr);
			}
			else {
				itr++;
			}
		}
	}
	_vDel.clear();
}

/**
 * �o�^�����I�u�W�F�N�g��Process()��o�^���ɉ�
 */
void ObjectServer::Process() {
	// Add���X�g�ɂ���I�u�W�F�N�g�����X�g�ɓo�^����
	AddListObjects();

	// Process()���Ăяo��
	for (auto itr = _vObject.begin(); itr != _vObject.end(); itr++) {
		(*itr)->Process();
	}

	// Del���X�g�ɂ���I�u�W�F�N�g�����X�g����폜����
	DelListObjects();
}

/**
 * �o�^�����I�u�W�F�N�g��Render()��o�^���ɉ�
 */
void ObjectServer::Render() {

	for (auto itr = _vObject.begin(); itr != _vObject.end(); itr++) {
		(*itr)->Render();
	}
}