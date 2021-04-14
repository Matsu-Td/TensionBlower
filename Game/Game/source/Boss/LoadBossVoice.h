/**
 * @file   LoadBossVoice.h
 * @brief  �{�X���D ���f�[�^�ǂݍ��ݏ���
 * 
 * @author matsuo tadahiko
 * @date   2021/03/07
 */

#pragma once

#include "appframe.h"
#include <unordered_map>

namespace tensionblower {

	namespace boss {

		/**
		 * @brief �{�X���D ���f�[�^�ǂݍ��ݏ���
		 */
		class LoadBossVoice {
		public:
			/**
			 * @brief ���f�[�^�ǂݍ���
			 */
			void Initialize();

			/**
			 * @brief ���f�[�^�ǂݍ���
			 * @param filePath �t�@�C���p�X�w��
			 * @return �ǂݍ��񂾃f�[�^�̃n���h��
			 */
			int LoadVoice(const TCHAR* filePath);

			std::unordered_map<std::string, int> _vc;  // ���f�[�^
		};
	}
}
extern tensionblower::boss::LoadBossVoice gBossVoice;