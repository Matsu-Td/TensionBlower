/**
 * @file   TitleBGM.h
 * @brief  アウトゲーム用BGM再生処理
 * 
 * @author matsuo tadahiko
 * @date   2021/02/13
 */

#include "appframe.h"

namespace tensionblower {

	namespace mode {

		/**
		 * @brief アウトゲーム用BGM再生処理
		 */
		class TitleBGM : public ::mode::ModeBase {
		public:
			TitleBGM();
			~TitleBGM();
		};
	}
}
