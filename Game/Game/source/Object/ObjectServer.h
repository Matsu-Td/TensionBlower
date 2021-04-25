/**
 * @file  ObjectServer.h
 * @brief �I�u�W�F�N�g�Ǘ��T�[�o�[
 *
 * @date 2021/03/20
 */

#pragma once

#include <vector>
#include "ObjectBase.h"

namespace tensionblower {

	namespace object {
		/**
		 * @brief �I�u�W�F�N�g�Ǘ��T�[�o�[
		 */
		class ObjectServer {
		public:
			ObjectServer();
			~ObjectServer();

			/**
			 * @brief �o�^�����I�u�W�F�N�g��Process()��o�^���ɉ�
			 */
			void Process();

			/**
			 * @brief �o�^�����I�u�W�F�N�g�� Render()��o�^���ɉ�
			 */
			void Render();

			/**
			 * @brief Add���X�g�ɃI�u�W�F�N�g��ǉ�����
			 */
			void Add(ObjectBase* obj);

			/**
			 * @brief Del���X�g�ɃI�u�W�F�N�g��ǉ�����
			 */
			void Del(ObjectBase* obj);

			/**
			 * @brief ���X�g�ɓo�^����Ă���I�u�W�F�N�g��S�č폜
			 */
			void Clear();

			/**
			 * @brief  _vObject���X�g��߂�l�Ƃ��ĕԂ�
			 * @return �I�u�W�F�N�g�i�[���X�g
			 */
			std::vector<ObjectBase*>* List() { return &_vObject; }

		private:
			/**
			 * @brief Add���X�g�ɓo�^����Ă���I�u�W�F�N�g��ǉ�����
			 */
			void AddListObjects();

			/**
			 * @brief Del���X�g�ɓo�^����Ă���I�u�W�F�N�g��ǉ�����
			 */
			void DelListObjects();

		protected:
			std::vector<ObjectBase*> _vObject; // ObjectBase��o�^���郊�X�g
			std::vector<ObjectBase*> _vAdd;    // �ǉ�����I�u�W�F�N�g���X�g
			std::vector<ObjectBase*> _vDel;	   // �폜����I�u�W�F�N�g���X�g
		};
	}
}