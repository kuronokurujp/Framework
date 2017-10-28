/**
 *	@file 	DebugScreen.cpp
 *	@brief	
 *	@author	yuto uchida
 *	@data   2011-04-22
 *	@note 
 *
 */
#include "debug/DebugScreen.h"

#include "common/Common.h"

SelectedListInput*	DbgSceneManager::mp_List	= NULL;
int	DbgSceneManager::m_Phase	= 0;

void DbgSceneManager::Init( void )
{
	// �󂩃`�F�b�N
	if( mp_List != NULL ) {
		End();
	}

	m_Phase			= PHASE_SCENE_SELECT;
	mp_List			= new SelectedListInput();
	mp_List->Create( 30, 10, 0 );
}

void DbgSceneManager::End( void )
{
	DbgScreen*	pScreen	= NULL;
	for( int i = 0; i < mp_List->GetNum(); ++i ) {
		pScreen = reinterpret_cast< DbgScreen* >( mp_List->GetArg( i ) );
		SAFE_DELETE( pScreen );
	}

	mp_List->Destroy();
	SAFE_DELETE( mp_List );
}

void DbgSceneManager::Update( void )
{
	GameLib::GameSystem&	inst	= GameLib::GameSystem::Inst();

	// �I�����
	if( m_Phase == PHASE_SCENE_SELECT )
	{	
		mp_List->Update();
		mp_List->DebugDraw();

		if( inst.IsButtonTriggerOn( 'e' ) )
		{
			m_Phase	= PHASE_SCENE_CTRL;
		} 
	}
	else
	{
		// �I������������X�V
		if( inst.IsButtonTriggerOn( 'e' ) )
		{
			m_Phase	= PHASE_SCENE_SELECT;
		}
		else
		{
			DbgScreen*	pScreen	= reinterpret_cast< DbgScreen* >( mp_List->GetCursorByArg() );
			pScreen->Update();

			I_DbgItem*	pItem	= reinterpret_cast< I_DbgItem*>( pScreen->GetCursorByArg() );
			if( pItem != NULL )
			{
				pItem->Update();
			}

			pScreen->DebugDraw();
		}
	}
}

// �f�o�b�O��ʒǉ�
int	DbgSceneManager::Add( DbgScreen*	in_pClass )
{
	int	Num	= mp_List->GetNum();
	mp_List->Add( in_pClass->GetName(), Num, reinterpret_cast< void* >( in_pClass ) );

	return Num;
}

// �f�o�b�O��ʍ폜
void	DbgSceneManager::Del( int	in_Index )
{
	// �o�^�����N���X�폜
	DbgScreen*	pScreen	= reinterpret_cast< DbgScreen* >( mp_List->GetArg( in_Index ) );
	if( pScreen != NULL )
	{
		SAFE_DELETE( pScreen );
		// ���X�g�������
		mp_List->ClearByIndex( in_Index );
	}
}

DbgScreen*	DbgSceneManager::Get( int	in_Index )
{
	return	reinterpret_cast< DbgScreen* >( mp_List->GetArg( in_Index ) );
}

DbgScreen::DbgScreen(  const char* in_pName )	:
SelectedList(),
m_String( in_pName )
{
	Create( eLIST_MAX, 6, 0 );
}

DbgScreen::~DbgScreen( void )
{
	I_DbgItem*	pItem	= NULL;
	for( int i = 0; i < GetNum(); ++i ) {
		pItem = reinterpret_cast< I_DbgItem* >( GetArg( i ) );
		SAFE_DELETE( pItem );
	}

	Destroy();
}

void	DbgScreen::Add( I_DbgItem* in_pItem )
{
	SelectedList::Add( "", 0, reinterpret_cast< void* >( in_pItem ) );
}

/*
	@brief	���͏���
*/
void	DbgScreen::_VUpdatePad( void )
{
	GameLib::GameSystem&	inst	= GameLib::GameSystem::Inst();

	//	�o�^�����A�C�e���̃J�[�\���ʒu�ύX
	if( inst.IsButtonTriggerOn( Input::KEY_UP ) )
	{
		_Move( -1 );
	}
	else if( inst.IsButtonTriggerOn( Input::KEY_DOWN ) )
	{
		_Move( 1 );
	}
}

void	DbgScreen::_VDebugText( const int in_ListIndex, const int in_ViewIndex )
{
	I_DbgItem*	pItem	= reinterpret_cast< I_DbgItem*>( GetArg( in_ListIndex ) );

	bool bActive	= false;
	if( GetCursorByIndex() == in_ListIndex )
	{
		bActive	= true;
	}

	pItem->Draw( bActive, 32, 16 * in_ViewIndex );
}
