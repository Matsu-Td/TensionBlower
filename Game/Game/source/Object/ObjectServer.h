/**
 * @file  ObjectServer.h
 * @brief オブジェクト管理サーバー
 *
 * @date 2021/03/20
 */

#pragma once

#include <vector>
#include "ObjectBase.h"

namespace tensionblower {

	namespace object {
		/**
		 * @brief オブジェクト管理サーバー
		 */
		class ObjectServer {
		public:
			ObjectServer();
			~ObjectServer();

			/**
			 * @brief 登録したオブジェクトのProcess()を登録順に回す
			 */
			void Process();

			/**
			 * @brief 登録したオブジェクトの Render()を登録順に回す
			 */
			void Render();

			/**
			 * @brief Addリストにオブジェクトを追加する
			 */
			void Add(ObjectBase* obj);

			/**
			 * @brief Delリストにオブジェクトを追加する
			 */
			void Del(ObjectBase* obj);

			/**
			 * @brief リストに登録されているオブジェクトを全て削除
			 */
			void Clear();

			/**
			 * @brief  _vObjectリストを戻り値として返す
			 * @return オブジェクト格納リスト
			 */
			std::vector<ObjectBase*>* List() { return &_vObject; }

		private:
			/**
			 * @brief Addリストに登録されているオブジェクトを追加する
			 */
			void AddListObjects();

			/**
			 * @brief Delリストに登録されているオブジェクトを追加する
			 */
			void DelListObjects();

		protected:
			std::vector<ObjectBase*> _vObject; // ObjectBaseを登録するリスト
			std::vector<ObjectBase*> _vAdd;    // 追加するオブジェクトリスト
			std::vector<ObjectBase*> _vDel;	   // 削除するオブジェクトリスト
		};
	}
}