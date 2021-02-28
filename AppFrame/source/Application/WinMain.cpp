
/**
 * @file WinMain.cpp
 * @brief �G���g���[�|�C���g
 * 
 * @date 2020-12-18
 */

#include "../appframe.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ApplicationBase *appBase = ApplicationBase::GetInstance();
	if (!appBase) { return 0; }

	if (!appBase->Initialize(hInstance)) {
		return 0;
	}
	// ���\�[�X�T�[�o������
	ResourceServer::Init();

	while (ProcessMessage() == 0)
	{
		if (appBase->GetInstance()->GameEndFlag() == true) {
			break;
		}

		if(GetAsyncKeyState(VK_ESCAPE)) { break; }

		appBase->Input();
		appBase->Process();

		ClearDrawScreen();	
		appBase->Render();
		ScreenFlip();	
	}

	ResourceServer::Release();
	appBase->Terminate();

	return 0;
}
