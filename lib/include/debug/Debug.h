/**
 *	@file	debug.h
 *	@brief	デバッグシステム
 *	@author	yuto uchida
 *	@data   2009-03-19
 *	@note	デバッグ時に必要なシステムをここに記述
 *
 */
#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <assert.h>
#include <stdio.h>

#include "debug/DebugScreenInterface.h"

#ifdef __cplusplus
extern "C" {
#endif

// デバッグ用printf
#ifdef _DEBUG

// ログ出力
#define cprintf printf

//	ファイル名とソースファイル行数を一緒に出す。
//@todo ログを出力するように対応
#define FILE_LINE_PRINT( _str_, ...)	\
{	\
	printf("%s: (%d)\n", __FILE__, __LINE__ );	\
}	\

//	アサート
#define ASSERT( x ) ( assert( x ) )
//	アサート時にログ出力を出す
//@todo ログを出力するように対応
#define STRING_ASSERT( _x_, _str_, ...) \
	if( (_x_) == false ) {\
	}\

#else

#define cprintf {}
#define FILE_LINE_PRINT {}

#define ASSERT( _x_ ) ((_x_))
#define STRING_ASSERT( _x_, _str_, ...) ((_x_))

#endif

#ifdef __cplusplus
}
#endif

#endif // __DEBUG_H__
