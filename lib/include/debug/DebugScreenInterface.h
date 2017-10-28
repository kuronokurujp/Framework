/**
 *	@file 	DebugScreenInterface.h
 *	@brief	アプリでデバッグ画面作成を扱いやすくした
 *	@author	yuto uchida
 *	@data   2011-04-22
 *	@note 
 *
 */
#ifndef __DEBUGSCREENINTERFACE_H__
#define __DEBUGSCREENINTERFACE_H__


#include "debug/DebugScreen.h"

#define DBG_SCENE_HANDLE_NON	( -1 )

// デバッグ画面作成
#define DBG_SCENE_CREATE( _STR_ )	\
		( DbgSceneManager::add( new DbgScreen( ( _STR_ ) ) ) )

#define DBG_SCENE_DELETE( _NO_ )	\
		( DbgSceneManager::del( ( _NO_ ) ) )

// デバッグ画面要素をマクロ化
#define DBG_SCENE_U32_ITEM_INPUT( _NO_, _STR_, _OUT_, _INIT_, _MIN_, _MAX_, _NUM_	)	\
		( DbgSceneManager::get( (_NO_) )->Add( \
			new DbgItemInputUInterger( ( _STR_ ), ( _OUT_ ), ( _INIT_ ), ( _MIN_ ), ( _MAX_ ), ( _NUM_ ) ) ) )

#define DBG_SCENE_U16_ITEM_INPUT( _NO_, _STR_, _OUT_, _INIT_, _MIN_, _MAX_, _NUM_	)	\
		( DbgSceneManager::get( (_NO_) )->Add( \
			new DbgItemInputUShort( ( _STR_ ), ( _OUT_ ), ( _INIT_ ), ( _MIN_ ), ( _MAX_ ), ( _NUM_ ) ) ) )


#define DBG_SCENE_U8_ITEM_INPUT( _NO_, _STR_, _OUT_, _INIT_, _MIN_, _MAX_, _NUM_	)	\
		( DbgSceneManager::get( (_NO_) )->Add( \
			new DbgItemInputUChar( ( _STR_ ), ( _OUT_ ), ( _INIT_ ), ( _MIN_ ), ( _MAX_ ), ( _NUM_ ) ) ) )


#define DBG_SCENE_I32_ITEM_INPUT( _NO_, _STR_, _OUT_, _INIT_, _MIN_, _MAX_, _NUM_	)	\
		( DbgSceneManager::get( (_NO_) )->Add( \
			new DbgItemInputInterger( ( _STR_ ), ( _OUT_ ), ( _INIT_ ), ( _MIN_ ), ( _MAX_ ), ( _NUM_ ) ) ) )


#define DBG_SCENE_I16_ITEM_INPUT( _NO_, _STR_, _OUT_, _INIT_, _MIN_, _MAX_, _NUM_	)	\
		( DbgSceneManager::get( (_NO_) )->Add( \
			new DbgItemInputShort( ( _STR_ ), ( _OUT_ ), ( _INIT_ ), ( _MIN_ ), ( _MAX_ ), ( _NUM_ ) ) ) )


#define DBG_SCENE_I8_ITEM_INPUT( _NO_, _STR_, _OUT_, _INIT_, _MIN_, _MAX_, _NUM_	)	\
		( DbgSceneManager::get( (_NO_) )->Add( \
			new DbgItemInputChar( ( _STR_ ), ( _OUT_ ), ( _INIT_ ), ( _MIN_ ), ( _MAX_ ), ( _NUM_ ) ) ) )


#define DBG_SCENE_FLOAT_ITEM_INPUT( _NO_, _STR_, _OUT_, _INIT_, _MIN_, _MAX_, _NUM_	)	\
		( DbgSceneManager::get( (_NO_) )->Add( \
			new DbgItemInputFloat( ( _STR_ ), ( _OUT_ ), ( _INIT_ ), ( _MIN_ ), ( _MAX_ ), ( _NUM_ ) ) ) )


#define DBG_SCENE_DOUBLE_ITEM_INPUT( _NO_, _STR_, _OUT_, _INIT_, _MIN_, _MAX_, _NUM_	)	\
		( DbgSceneManager::get( (_NO_) )->Add( \
			new DbgItemInputDouble( ( _STR_ ), ( _OUT_ ), ( _INIT_ ), ( _MIN_ ), ( _MAX_ ), ( _NUM_ ) ) ) )


#endif // __DEBUGSCREENINTERFACE_H__
