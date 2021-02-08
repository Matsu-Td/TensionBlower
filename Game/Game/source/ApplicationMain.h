
/**
 * @file  ApplicationMain.h
 * @brief アプリケーションメイン
 *
 * @date 2021-02-08
 */

#include "appframe.h"

class ApplicationMain : public ApplicationBase{

	typedef ApplicationBase base;

public:
	virtual bool Initialize(HINSTANCE hInstance);
	virtual bool Terminate();
	virtual bool Input();
	virtual bool Process();
	virtual bool Render();

	virtual bool AppWindowed() { return true; }
	virtual int DispSizeW() { return 1920; }
	virtual int DispSizeH() { return 1080; }

protected:

}; 
