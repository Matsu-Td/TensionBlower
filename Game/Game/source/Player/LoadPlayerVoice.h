/**
 * @file   LoadPlayerVoice.h
 * @brief  �v���C���[���D ���f�[�^�ǂݍ��ݏ���
 * 
 * @author matsuo tadahiko
 * @date   2021/03/07
 */

#pragma once

#include "appframe.h"
#include <unordered_map>

namespace tensionblower {

	namespace player {

		/**
		 * @brief �v���C���[���D ���f�[�^�ǂݍ��ݏ���
		 */
		class LoadPlayerVoice {
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
extern tensionblower::player::LoadPlayerVoice gPlayerVoice;