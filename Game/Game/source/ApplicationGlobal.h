
#include "appframe.h"

class ApplicationGlobal
{
public:
	ApplicationGlobal();
	virtual ~ApplicationGlobal();

	bool Init();

public:
	bool _gameEndFlag;
	int _gameTime;
	int _remainingHP;
	int _totalGetEnergy;
	int _totalRepelCnt;
};

// ���̃\�[�X��gGlobal���g����悤��
extern ApplicationGlobal gGlobal;