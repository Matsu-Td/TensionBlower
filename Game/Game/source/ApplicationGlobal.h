
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
};

// ���̃\�[�X��gGlobal���g����悤��
extern ApplicationGlobal gGlobal;