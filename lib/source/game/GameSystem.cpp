/**
 *	@file 	D:/work/dungeon/framework/game/GameSystem.cpp
 *	@brief	
 *	@author	yuto uchida
 *	@data   2010-11-30
 *	@note 
 *
 */
#include "game/GameSystem.h"

#include "directx/Manager.h"

#include <stdio.h>

namespace GameLib {

static GameSystem::GameConfig	s_ConfigData;

//	Windows��p
static const unsigned	s_aScreenSize[ GameSystem::GameConfig::SIZE_NUM ][ 2 ]	=
{
	//	w,		h
	{
		640,	480,
	},
};

/*
	@brief	�R���X�g���N�^	
*/
GameSystem::GameSystem( void )
{
	mp_Cam	= NULL;
}

/*
	@brief	�C���X�^���X�擾
*/
GameSystem&	GameSystem::Inst()
{
	static GameSystem	inst;
	return inst;
}

/*
	@brief	3D�A�N�e�B�u�J�����擾
*/
Camera&	GameSystem::GetActiveCam()
{
	ASSERT( mp_Cam );
	return *mp_Cam;
}

/*
	@brief	�X�N���[���T�C�Y��Ԃ�	
*/
const unsigned GameSystem::GetScreenWidth() const
{
	return	s_ConfigData.GetScreenSizeX();
}

const unsigned GameSystem::GetScreenHeight() const
{
	return	s_ConfigData.GetScreenSizeY();
}

/*
	@breif	�{�^������
	@param	i_key	:	�w�肵���{�^���������ꂽ��
*/
bool GameSystem::IsButtonOn( unsigned char i_key )
{
	return DirectX::Manager::Inst().IsKeyOn( i_key );
}

bool GameSystem::IsButtonTriggerOn( unsigned char i_key )
{
	return DirectX::Manager::Inst().IsKeyTriggerOn( i_key );
}

bool GameSystem::IsButtonRepertOn( unsigned char i_key )
{
	return DirectX::Manager::Inst().IsKeyRepertOn( i_key );
}

/*
	@breif	�Q�[���p�b�h����
	@param	i_pad	:	�w�肵���{�^���������ꂽ��
*/
bool GameSystem::IsPadOn( Input::ePadKey i_pad )
{
	return DirectX::Manager::Inst().IsPadOn( i_pad );
}

bool GameSystem::IsPadTriggerOn( Input::ePadKey i_pad )
{
	return DirectX::Manager::Inst().IsPadTriggerOn( i_pad );
}

bool GameSystem::IsPadRepertOn( Input::ePadKey i_pad )
{
	return DirectX::Manager::Inst().IsPadRepertOn( i_pad );
}

/*
	@brief �w�i�F�ݒ�E�擾
*/
void GameSystem::SetScreenColor( const unsigned in_rgb )
{
	DirectX::Manager::Inst().SetScreenColor( in_rgb );
}

const unsigned	GameSystem::GetScreenColor()	const
{
	return DirectX::Manager::Inst().GetScreenColor();
}

/*
	@brief	�_��`��	
*/
void	GameSystem::DrawPoint( const Vec2& in_Pos )
{
	IDirect3DDevice9*	pDevice	= DirectX::Manager::Inst().GetDevice();

	typedef struct  
	{
		Vec3	pos;
		float	rhw;
	} _DRAW_POINT_POS_ST;
	_DRAW_POINT_POS_ST	aVecPoint[ 2 ];
	aVecPoint[ 0 ].pos.Set( 0.f + in_Pos.x, 0.5f + in_Pos.y, 0.f );
	aVecPoint[ 0 ].rhw	= 1.f;
	aVecPoint[ 1 ].pos.Set( 0.5f + in_Pos.x, 0.5f + in_Pos.y, 0.f );
	aVecPoint[ 1 ].rhw	= 1.f;

	pDevice->SetFVF( D3DFVF_XYZRHW );
	pDevice->DrawPrimitiveUP( D3DPT_POINTLIST, 2, aVecPoint, sizeof(aVecPoint[ 0 ]) );
}

/*
	@breif	�f�o�b�O�e�L�X�g�`��
	@param	ip_str	:	�e�L�X�g
	@param	i_x		:	x���W
	@param	i_y		:	y���W
	@param	i_color	:	�J���[
*/
void GameSystem::DrawDebugText( const char* ip_str, int i_x, int i_y, const int i_color )
{
	// DirectX���ł̓}���`�o�C�g��������Ȃ��̂ŕϊ����Ă���g��
	_TCHAR buf[256];
	::memset( buf, NULL, sizeof(buf) * sizeof(_TCHAR) );
	#ifdef UNICODE
		// �}���`�o�C�g�����ɕϊ�
		MultiByteToWideChar( CP_OEMCP, MB_PRECOMPOSED, ip_str, ::strlen(ip_str), buf, (sizeof buf)/2 );
	#else
		::strcpy_s( buf, ip_str );
	#endif

	DirectX::Manager::Inst().DrawDebugText( buf, i_x, i_y, i_color );
}

/*
	@brief	�R���t�B�O�擾
*/
const GameSystem::GameConfig&	GameSystem::GetConfig() const
{
	return	s_ConfigData;
}

/*
	@brief	�ϐ��N���A
*/
void	GameSystem::GameConfig::_Clear()
{
	m_ScreenSizeType = SIZE_640_480;
	sprintf_s( m_AppName, "Game" );
}

/*
	@brief	�X�N���[���T�C�Y�擾
*/
const unsigned	GameSystem::GameConfig::GetScreenSizeX() const
{
	return	s_aScreenSize[ m_ScreenSizeType ][ 0 ];
}

const unsigned	GameSystem::GameConfig::GetScreenSizeY() const
{
	return	s_aScreenSize[ m_ScreenSizeType ][ 1 ];
}

} // namespace GameLib

