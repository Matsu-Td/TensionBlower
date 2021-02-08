
#include "AppFrame.h"
#include "ApplicationGlobal.h"

// ŽÀ‘Ì
ApplicationGlobal	gGlobal;

ApplicationGlobal::ApplicationGlobal() 
{
}

ApplicationGlobal::~ApplicationGlobal() 
{
}


bool ApplicationGlobal::Init() {

	_gameEndFlag = false;

	return true;
}
