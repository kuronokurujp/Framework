/**
 *	@file 	DebugScreen.h
 *	@brief	
 *	@author	yuto uchida
 *	@data   2011-04-22
 *	@note 
 *
 */
#ifndef __DEBUGSCREEN_H__
#define __DEBUGSCREEN_H__

#include "debug/DebugScreenItemNumber.hpp"
#include "common/SelectedList.h"

// STLを使うとwarningが出る可能性があるので、それを出さないようにする
#pragma warning (disable:4786)
#include<string>

// 前方宣言
class	DbgScreen;
class	SelectedListInput;

// デバッグ画面管理
class DbgSceneManager
{
public:
	static	void 	Init( void );
	static	void	End( void );
	static	void	Update( void );
	static	int		Add( DbgScreen*	in_pClass );
	static	void	Del( int	in_Index	);
	static	DbgScreen*	Get( int in_Index );
private:

	enum {
		PHASE_SCENE_SELECT,
		PHASE_SCENE_CTRL,
	};

	//	コンストラクタ
	DbgSceneManager()		{}
	~DbgSceneManager()	{}

	//	選択制御
	static SelectedListInput*	mp_List;
	static int	m_Phase;
};

/*
	@brief	デバッグシーン用
*/
class DbgScreen	:	public SelectedList
{
public:
	DbgScreen( const char* in_pName );
	virtual	~DbgScreen( void );

	void	Add( I_DbgItem* in_pItem );

	const char*	GetName( void )	const {	return m_String.c_str(); }
private:
	enum {
		eLIST_MAX	= 30,
	};

	std::string	m_String;

	//	関数
	virtual		void	_VUpdatePad( void );
// デバッグ用
	virtual		void	_VDebugText( const int in_ListIndex, const int in_ViewIndex );
};

#endif // __DEBUGSCREEN_H__
