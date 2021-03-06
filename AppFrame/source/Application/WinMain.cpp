/**
 * @file  WinMain.cpp
 * @brief エントリーポイント
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#include "../appframe.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	// ログの出力を行わない
	SetOutApplicationLogValidFlag(false);

	// メモリリークのレポートを表示させる
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	appframe::ApplicationBase *appBase = appframe::ApplicationBase::GetInstance();
	if (!appBase) { return 0; }

	if (!appBase->Initialize(hInstance)) {
		return 0;
	}
	// リソースサーバ初期化
	resource::ResourceServer::Init();

	while (ProcessMessage() == 0)
	{
		// ゲーム終了フラグ
		if (appBase->GetInstance()->GameEndFlag() == true) {
			break;
		}

		appBase->Input();
		appBase->Process();

		ClearDrawScreen();	
		appBase->Render();
		ScreenFlip();	
	}

	resource::ResourceServer::Release();
	appBase->Terminate();

	return 0;
}
