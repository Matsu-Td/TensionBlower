
#include "appframe.h"

class ApplicationGlobal
{
public:
	ApplicationGlobal();
	virtual ~ApplicationGlobal();

	bool Init();

public:
	int		_cgCursor;
	bool _gameEndFlag;
	int _gameTime;
};

// ���̃\�[�X��gGlobal���g����悤��
extern ApplicationGlobal gGlobal;