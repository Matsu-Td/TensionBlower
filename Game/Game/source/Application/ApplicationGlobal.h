/**
 * @file   ApplicationGlobal.h
 * @brief  �O���[�o���ϐ���`
 * 
 * @author matsuo tadahiko
 * @date   2021/01/20
 */

#include "appframe.h"

namespace tensionblower {

	/**
	 * @brief �O���[�o���ϐ���`
	 */
	class ApplicationGlobal {
	public:
		ApplicationGlobal();
		virtual ~ApplicationGlobal();

		/**
		 * @brief  ������
		 * @return �����̐���
		 */
		bool Initialize();

	public:
		bool _gameEndFlag;    // �Q�[���I���t���O(true:�Q�[���I��)
		int  _gameTime;       // �N���A�܂ł̌o�ߎ���
		int  _remainingHP;    // �c��HP
		int  _totalGetEnergy; // ���G�l���M�[�����
		int  _totalRepelCnt;  // ���v�e���Ԃ���
	};
}
extern tensionblower::ApplicationGlobal gGlobal;