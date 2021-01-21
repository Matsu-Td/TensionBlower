/*
** WinMain
*/

//
// include 部
//

#include "../appframe.h"

// メモリリーク検出用
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define NEW new
#endif

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ApplicationBase *appBase = ApplicationBase::GetInstance();
	if (!appBase) { return 0; }

	if (!appBase->Initialize(hInstance)) {
		return 0;
	}
	
	// 1フレームループを組む ----------------------------------------------------------
	while (ProcessMessage() == 0)		// プログラムが終了するまでループ
	{
		appBase->Input();
		appBase->Process();

		ClearDrawScreen();		// 画面を初期化する
		appBase->Render();
		ScreenFlip();			// 裏画面の内容を表画面に反映させる
	}

	appBase->Terminate();

	return 0;
}
