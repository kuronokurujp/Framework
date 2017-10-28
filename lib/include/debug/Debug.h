/**
 *	@file	debug.h
 *	@brief	�f�o�b�O�V�X�e��
 *	@author	yuto uchida
 *	@data   2009-03-19
 *	@note	�f�o�b�O���ɕK�v�ȃV�X�e���������ɋL�q
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

// �f�o�b�O�pprintf
#ifdef _DEBUG

// ���O�o��
#define cprintf printf

//	�t�@�C�����ƃ\�[�X�t�@�C���s�����ꏏ�ɏo���B
//@todo ���O���o�͂���悤�ɑΉ�
#define FILE_LINE_PRINT( _str_, ...)	\
{	\
	printf("%s: (%d)\n", __FILE__, __LINE__ );	\
}	\

//	�A�T�[�g
#define ASSERT( x ) ( assert( x ) )
//	�A�T�[�g���Ƀ��O�o�͂��o��
//@todo ���O���o�͂���悤�ɑΉ�
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
