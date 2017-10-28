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
	@brief	���X�g�f�[�^�쐬
	@param	in_Num		:	���X�g�I�𑍐�
	@param	in_ViewNum	:	���X�g�I��͈͐�
	@param	in_Magin	:	���X�g�I���}�[�W����
*/
void	SelectedList::Create( const unsigned int	in_Num,	const unsigned int in_ViewNum, const unsigned int	in_Magin )
{
	_Clear();

	mp_Data		= new _DATA_ST[ in_Num ];
	m_DataMax	= in_Num;
	m_ViewMax	= in_ViewNum;

	//	�\���̈�̔����𒴂���l�͕s�\
	if( in_Magin <= ( in_ViewNum >> 1 ) )
	{
		m_Magin		= in_Magin;
	}
}

/*
	@brief	���X�g�f�[�^�j��
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
	@brief	���X�g�I�����ڂ�ǉ�
	@param	in_pName	:	�I��
	@param	in_ID		:	�I��ID
	@param	in_pArg		:	�֘A�t����f�[�^�A�h���X
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
	@brief	�w�肵�����X�g���ڂ��폜
	@param	in_Index	: ���X�g����Index
*/
void	SelectedList::ClearByIndex( int in_Index )
{
	_DATA_ST*	pData	= _GetData( in_Index );

	pData->Name	= NULL;
	pData->ID	= -1;
	pData->pArg	= NULL;
}

/*
	@brief	�w�肵���I�����ڂ��̂��̂��폜
	@param	in_Index	:	���X�g����Index
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
	@brief	�I���J�[�\�����w��
	@param	in_Index	:	���X�g����Index
*/
void	SelectedList::SetCursorByIndex( const int in_Index )
{
	if( in_Index < m_ListMax )
	{
		//	���������ړ�������
		_Move( in_Index - m_CursorIndex );
	}
	else
	{
		//	�G���[�F���X�g�͈͊O�̈ʒu���w��
	}
}

/*
	@brief	�I�����X�g�\��
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
	@brief	�f�[�^������
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
	@brief	���X�g���ڂ̎w��Index�̃f�[�^�擾
	@param	in_Index	:	���X�g����Index
	@return	�f�[�^
*/
SelectedList::_DATA_ST*	SelectedList::_GetData( const int in_Index )
{
	return	&mp_Data[ in_Index ];
}

/*
	@brief	�I���J�[�\���ړ�
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
			//	�\�����郊�X�g��艺�ɃJ�[�\�����ړ������B
			m_ViewTop	+= ( ( cursorIndex - BottomViewIndex ) + 1 );
			if( m_ViewTop >= ( m_ListMax - ViewMax ) )
			{
				m_ViewTop	= m_ListMax - ViewMax;
			}
		}
		else if( ( m_ViewTop > 0 ) && ( TopViewIndex > cursorIndex ) )
		{
			//	�\�����郊�X�g����ɃJ�[�\�����ړ������B
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
	@brief	���͏���
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
	@brief	�f�o�b�O�\��
	@note	�o�^�����V�[���ꗗ��\��
*/
void	SelectedListInput::_VDebugText( const int in_ListIndex, const int in_ViewIndex )
{
	// �e�L�X�g����
	int	Color	= 0xffffffff;
	if( GetCursorByIndex() == in_ListIndex )
	{
		Color	= 0xffff0000;
	}

	GameLib::GameSystem::Inst().DrawDebugText( GetName( in_ListIndex ), 32, 16 * in_ViewIndex, Color );
}
