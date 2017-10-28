/**
 *	@file 	SelectedList.cpp
 *	@brief	
 *	@author	yuto uchida
 *	@data   2011-04-23
 *	@note 
 *
 */
#include "common/SelectedList.h"
#include "game/GameSystem.h"

#include <string.h>

/*
	@brief	リストデータ作成
	@param	in_Num		:	リスト選択総数
	@param	in_ViewNum	:	リスト選択範囲数
	@param	in_Magin	:	リスト選択マージン数
*/
void	SelectedList::Create( const unsigned int	in_Num,	const unsigned int in_ViewNum, const unsigned int	in_Magin )
{
	_Clear();

	mp_Data		= new _DATA_ST[ in_Num ];
	m_DataMax	= in_Num;
	m_ViewMax	= in_ViewNum;

	//	表示領域の半分を超える値は不可能
	if( in_Magin <= ( in_ViewNum >> 1 ) )
	{
		m_Magin		= in_Magin;
	}
}

/*
	@brief	リストデータ破棄
*/
void	SelectedList::Destroy( void )
{
	if( mp_Data != NULL )
	{
		delete[]	mp_Data;
	}

	_Clear();
}

/*
	@brief	リスト選択項目を追加
	@param	in_pName	:	選択名
	@param	in_ID		:	選択ID
	@param	in_pArg		:	関連付けるデータアドレス
*/
void	SelectedList::Add( const char* in_pName,	const int	in_ID,	void*	in_pArg )
{
//	ASSERT( m_ListMax < m_DataMax );
	_DATA_ST*	pData	= _GetData( m_ListMax );
	++m_ListMax;

	pData->Name	= in_pName;
	pData->ID	= in_ID;
	pData->pArg	= in_pArg;
}

/*
	@brief	指定したリスト項目を削除
	@param	in_Index	: リスト項目Index
*/
void	SelectedList::ClearByIndex( int in_Index )
{
	_DATA_ST*	pData	= _GetData( in_Index );

	pData->Name	= NULL;
	pData->ID	= -1;
	pData->pArg	= NULL;
}

/*
	@brief	指定した選択項目そのものを削除
	@param	in_Index	:	リスト項目Index
*/
void	SelectedList::DelByIndex( int	in_Index )
{
	if( m_ListMax <= 0 ) { return; }

	int	copyIndex	= in_Index + 1;
	if( ( copyIndex < m_ListMax ) && ( m_ListMax > 1 ) ) {
		::memcpy( &mp_Data[ in_Index ], &mp_Data[ copyIndex ], sizeof( mp_Data[ 0 ] ) * ( m_DataMax - copyIndex ) );
	}

	--m_ListMax;
}

/*
	@brief	選択カーソルを指定
	@param	in_Index	:	リスト項目Index
*/
void	SelectedList::SetCursorByIndex( const int in_Index )
{
	if( in_Index < m_ListMax )
	{
		//	差分だけ移動させる
		_Move( in_Index - m_CursorIndex );
	}
	else
	{
		//	エラー：リスト範囲外の位置を指定
	}
}

/*
	@brief	選択リスト表示
*/
void	SelectedList::DebugDraw()
{
	int	max	= m_ViewMax;
	for( int listNo = m_ViewTop, i = 0; i < max; ++listNo, ++i ) {
		if( listNo < m_ListMax ) {
			_VDebugText( listNo, i );
		}
	}
}

/*
	@brief	データ初期化
*/
void		SelectedList::_Clear()
{
	mp_Data			= NULL;
	m_DataMax		= 0;
	m_ListMax		= 0;

	m_CursorIndex	= 0;

	m_ViewTop		= 0;
	m_ViewMax		= 0;
}

/*
	@brief	リスト項目の指定Indexのデータ取得
	@param	in_Index	:	リスト項目Index
	@return	データ
*/
SelectedList::_DATA_ST*	SelectedList::_GetData( const int in_Index )
{
	return	&mp_Data[ in_Index ];
}

/*
	@brief	選択カーソル移動
*/
void		SelectedList::_Move( int in_Offset )
{
	if( m_ListMax <= 0 ) {
		return;
	}

	if( in_Offset == 0 ) {
		return;
	}

	if( m_ViewMax <= 0 ) {
		return;
	}

	int	ViewMax	= m_ViewMax;
	if( m_ListMax < m_ViewMax ) {
		ViewMax	= m_ListMax;
	}

	int	cursorIndex	= m_CursorIndex + in_Offset;

	if( cursorIndex >= m_ListMax )
	{
		m_ViewTop	= m_ListMax - ViewMax;
		cursorIndex	= m_ListMax - 1;
	}
	else if( cursorIndex < 0 )
	{
		m_ViewTop	= 0;
		cursorIndex	= 0;
	}
	else
	{
		const int	TopViewIndex	= m_ViewTop	+ m_Magin;
		const int	BottomViewIndex	= m_ViewTop + ViewMax - m_Magin; 
		if( BottomViewIndex <= cursorIndex )
		{
			//	表示するリストより下にカーソルが移動した。
			m_ViewTop	+= ( ( cursorIndex - BottomViewIndex ) + 1 );
			if( m_ViewTop >= ( m_ListMax - ViewMax ) )
			{
				m_ViewTop	= m_ListMax - ViewMax;
			}
		}
		else if( ( m_ViewTop > 0 ) && ( TopViewIndex > cursorIndex ) )
		{
			//	表示するリストより上にカーソルが移動した。
			m_ViewTop	+= ( cursorIndex - TopViewIndex );
			if( m_ViewTop < 0 )
			{
				m_ViewTop	= 0;
			}
		}
	}

	m_CursorIndex	= cursorIndex;
}

/*
	@brief	入力処理
*/
void	SelectedListInput::_VUpdatePad( void )
{
	GameLib::GameSystem&	inst	= GameLib::GameSystem::Inst();

	if( inst.IsButtonTriggerOn( Input::KEY_UP ) )
	{
		_Move( -1 );
	}
	else if( inst.IsButtonTriggerOn( Input::KEY_DOWN ) )
	{
		_Move( 1 );
	}
}

/*
	@brief	デバッグ表示
	@note	登録したシーン一覧を表示
*/
void	SelectedListInput::_VDebugText( const int in_ListIndex, const int in_ViewIndex )
{
	// テキスト生成
	int	Color	= 0xffffffff;
	if( GetCursorByIndex() == in_ListIndex )
	{
		Color	= 0xffff0000;
	}

	GameLib::GameSystem::Inst().DrawDebugText( GetName( in_ListIndex ), 32, 16 * in_ViewIndex, Color );
}
