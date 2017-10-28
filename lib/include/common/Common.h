/**
 *	@file 	D:/ProgramStady/Game/2D/MiracleShot/Proj/src/sys/common.h
 *	@brief
 *	@author	yuto uchida
 *	@data   2009-08-02
 *	@note
 *
 */
#ifndef __COMMON_H__
#define __COMMON_H__

// ウィンドウズで共通で使用するのはここに
#include <windows.h>

//@todo 下記のインクルードファイルは使う側で参照できないようにしたい
#include <d3dx9.h>

#include <tchar.h>

#include "debug/Debug.h"
#include "common/Env.h"

#define SAFE_DELETE( x ) { if( (x) ) { delete (x); (x) = NULL; } }
#define SAFE_DELETE_ARRAY( x ) { if( (x)) { delete[] (x); (x) = NULL; } }

#endif // __COMMON_H__
