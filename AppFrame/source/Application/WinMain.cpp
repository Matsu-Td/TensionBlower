/*
** WinMain
*/

//
// include •”
//

#include "../appframe.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ApplicationBase *appBase = ApplicationBase::GetInstance();
	if (!appBase) { return 0; }

	if (!appBase->Initialize(hInstance)) {
		return 0;
	}
	
	while (ProcessMessage() == 0)
	{

		appBase->Input();
		appBase->Process();

		ClearDrawScreen();	
		appBase->Render();
		ScreenFlip();	

		if (appBase->GetInstance()->GameEndFlag() == true) {

			break;
		}
	}
	ResourceServer::Release();
	appBase->Terminate();

	return 0;
}
