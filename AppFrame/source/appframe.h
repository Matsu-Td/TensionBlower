#pragma once

#pragma comment(lib,"AppFrame.lib")

// メモリリーク検出用
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define NEW new
#endif

#include "DxLib.h"
#include "Application/ApplicationBase.h"
#include "CFile/CFile.h"
#include "ResourceServer/ResourceServer.h"
#include "ObjectServer/ObjectServer.h"