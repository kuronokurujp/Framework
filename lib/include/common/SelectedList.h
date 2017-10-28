/**
 *	@file 	SelectedList.h
 *	@brief	選択リスト
 *	@author	yuto uchida
 *	@data   2011-04-23
 *	@note	縦方向の選択リスト制御
 *
 */
#ifndef __SELECTEDLIST_H__
#define __SELECTEDLIST_H__

#include <stdio.h>
#include "Env.h"

/*
	@brief	選択リスト
*/
class	SelectedList
{
public:
	/*
		コンストラクタ
	*/
	SelectedList()	{ _Clear(); }
	virtual ~SelectedList()	{}

	/*
		関数
	*/
	// リストデータ作成
	void	Create( const unsigned int	in_Num,	const unsigned int in_ViewNum, const unsigned int	in_Magin );
	// リスト破棄
	void	Destroy();

	// リスト追加
	// ここで実際のリスト数が増える
	void	Add( const char* in_pName,	const int	in_ID = 0,	void*	in_pArg = NULL );
	// 指定したリストクリア
	// しかしリスト数が減るわけではない
	void	ClearByIndex( const int in_Index );

	// 指定したリスト削除
	void	DelByIndex( const int	in_Index );

	void	Update()	{ _VUpdatePad(); }

	// 現在の指定カーソルのデータ取得
	const int		GetCursorByIndex( void )	const	{ return	m_CursorIndex;	}
	const char*		GetCursorByName( void )		{ return	GetName( GetCursorByIndex() );	}
	const int		GetCursorByDataID( void )	{ return	GetDataID( GetCursorByIndex() );	}
	void*			GetCursorByArg( void )		{ return	GetArg( GetCursorByIndex() );	}

	const char*		GetName( const int in_Index )	{ return	_GetData( in_Index )->Name;	}
	const int		GetDataID( const int in_Index )	{ return	_GetData( in_Index )->ID;	}
	void*			GetArg( const int in_Index )	{ return	_GetData( in_Index )->pArg;	}

	// リスト数取得
	// add()を使った分の数
	const int		GetNum()		const	{ return m_ListMax;	}
	// 作成項目数取得
	const int		GetDataNum()	const	{ return m_DataMax; }

	//	表示領域数取得
	const int		GetViewNum()	const	{ return m_ViewMax; }

	// カーソル設定
	void	SetCursorByIndex( const int in_Index );

	//デバッグ用
	void	DebugDraw();

protected:
	/*
		関数
	*/
	void			_Move( int in_Offset );

private:
	/*
		定義
	*/
	typedef struct {
		const char*		Name;
		int				ID;
		void*			pArg;
	} _DATA_ST;	

	/*
		変数
	*/
	_DATA_ST*	mp_Data;
	int			m_DataMax;
	int			m_ListMax;

	int			m_CursorIndex;

	int			m_ViewTop;
	int			m_ViewMax;

	int			m_Magin;

	/*
		関数
	*/
	void			_Clear();
	_DATA_ST*		_GetData( const int in_Index );

	/*
		仮想関数
	*/
	virtual		void	_VUpdatePad()	{}
// デバッグ用
	virtual		void	_VDebugText( const int in_ListIndex, const int	in_ViewIndex )	{ UNUSE( in_ListIndex ); UNUSE( in_ViewIndex );}
};

/*
	@brief	選択リスト入力制御
*/
class SelectedListInput :	public SelectedList
{
public:
	//	コンストラクタ
	SelectedListInput()	: SelectedList()	{}
	virtual ~SelectedListInput()	{}

private:
	//	関数
	virtual		void	_VUpdatePad( void );
	// デバッグ用
	virtual		void	_VDebugText( const int in_ListIndex, const int in_ViewIndex );
};

#endif // __SELECTEDLIST_H__
