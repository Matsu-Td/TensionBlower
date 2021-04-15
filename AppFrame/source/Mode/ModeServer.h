/**
 * @file  ModeServer.h
 * @brief モード管理クラス
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#pragma once

#include <list>
#include "ModeBase.h"

namespace mode {

	/**
	 * @brief モード管理クラス
	 */
	class ModeServer {
		using lstModeBase = std::list<ModeBase*>;

	public:
		ModeServer();
		virtual	~ModeServer();
		static ModeServer* _pInstance;
		static ModeServer* GetInstance() { return (ModeServer*)_pInstance; }

		/**
		 * @brief モードサーバーに新たなモードを追加予約する、追加実行は1フレーム後
		 * @param mode  追加するモード
		 * @param layer 表示するレイヤー
		 * @param name  モードの名前
		 * @return 追加したモードのID
		 */
		int Add(ModeBase* mode, int layer, const char* name);		// 登録はするが、一度メインを回さないといけない

		/**
		 * @brief 登録しているモードの削除予約をする、削除実行は1フレーム後
		 * @param 削除するモード
		 * @return 0
		 */
		int Del(ModeBase* mode);

		/**
		 * @brief uidから指定したモードを取得
		 * @param uid モードのID
		 * @return 指定したIDのモード
		 */
		ModeBase* Get(int uid);

		/**
		 * @brief モードの名前から指定したモードを取得
		 * @param name モードの名前
		 * @return 指定した名前のモード
		 */
		ModeBase* Get(const char* name);

		/**
		 * @brief モードからIDを取得
		 * @param mode モードのポインタ
		 * @return 指定したモードのID　登録されていない場合は 0 を返す
		 */
		int GetId(ModeBase* mode);

		/**
		 * @brief モードの名前からIDを取得
		 * @param name モードの名前
		 * @return 指定したモードのID　登録されていない場合は 0 が返る
		 */
		int GetId(const char* name);

		/**
		 * @brief モードのポインタからモードの名前を取得
		 * @param mode モードのポインタ
		 * @return 指定したモードの名前
		 */
		const char* GetName(ModeBase* mode);

		/**
		 * @brief IDからモードの名前を取得
		 * @param uid モードのID
		 * @return 指定したモードの名前
		 */
		const char* GetName(int uid);

		/**
		 * @brief 登録していたモードをモードサーバーから全て削除、メモリ解放
		 */
		void Clear();

		/**
		 * @brief  レイヤーを最大値に指定
		 * @return int32_t の最大値
		 */
		int	LayerTop() { return INT32_MAX; }

		/**
		 * @brief レイヤーの順にソートを行う
		 * @param x モード1
		 * @param y モード2
		 * @return x が y のレイヤーより小さいか、その結果
		 */
		static bool modeSort(const ModeBase* x, const ModeBase* y) {
			return x->_layer < y->_layer;
		}

		/**
		 * @brief  プロセスを回すための初期化
		 * @return 0
		 */
		int ProcessInit();

		/**
		 * @brief  レイヤーの上の方からProcessを回す
		 * @return 0
		 */
		int Process();

		/**
		 * @brief  プロセスを回した後の後始末
		 * @return 0
		 */
		int ProcessFinish();

		/**
		 * @brief  描画を回すための初期化
		 * @return 0
		 */
		int RenderInit();

		/**
		 * @brief  レイヤーの下の方からRenderを回す
		 * @return 0
		 */
		int Render();

		/**
		 * @brief  描画を回した後の後始末
		 * @return 0
		 */
		int RenderFinish();

		/**
		 * @brief  現Processで、今処理しているレイヤーより下のレイヤーは処理は呼ばない
		 * @return 0
		 */
		int SkipProcessUnderLayer();

		/**
		 * @brief  現Processで、今処理しているレイヤーより下のレイヤーは描画は呼ばない
		 * @return 0
		 */
		int SkipRenderUnderLayer();

		/**
		 * @brief  現Processで、今処理しているレイヤーより下のレイヤーは時間経過を止める
		 * @return 0
		 */
		int PauseProcessUnderLayer();

	private:
		/**
		 * @brief 指定したモードをモードサーバーから削除、メモリ解放
		 * @param mode モードのポインタ
		 * @return 1
		 */
		int Release(ModeBase* mode);

		/**
		 * @brief 指定したモードが削除予約されているか確認
		 * @param mode モードのポインタ
		 * @return true:削除予約あり、false:削除予約なし
		 */
		bool IsDelRegist(ModeBase* mode);

		/**
		 * @brief 指定したモードがリストに登録、登録予約されているか確認
		 * @param mode モードのポインタ
		 * @return true:登録あり　false:登録なし
		 */
		bool IsAdd(ModeBase* mode);

	private:
		lstModeBase	_vMode;		 	// モードリスト
		int			_uid_count;		// uidカウンタ
		lstModeBase	_vModeAdd;		// 追加予約
		lstModeBase	_vModeDel;		// 削除予約

		ModeBase* _nowMode;		    // 現在呼び出し中のモード
		ModeBase* _skipProcessMode;	// このモードより下はProcessを呼ばない
		ModeBase* _skipRenderMode;	// このモードより下はRenderを呼ばない
		ModeBase* _pauseProcessMode;	// このモードより下はProcess時に時間経過をさせない
	};
}