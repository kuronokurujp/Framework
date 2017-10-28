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

//	Windows専用
static const unsigned	s_aScreenSize[ GameSystem::GameConfig::SIZE_NUM ][ 2 ]	=
{
	//	w,		h
	{
		640,	480,
	},
};

/*
	@brief	コンストラクタ	
*/
GameSystem::GameSystem( void )
{
	mp_Cam	= NULL;
}

/*
	@brief	インスタンス取得
*/
GameSystem&	GameSystem::Inst()
{
	static GameSystem	inst;
	return inst;
}

/*
	@brief	3Dアクティブカメラ取得
*/
Camera&	GameSystem::GetActiveCam()
{
	ASSERT( mp_Cam );
	return *mp_Cam;
}

/*
	@brief	スクリーンサイズを返す	
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
	@breif	ボタン入力
	@param	i_key	:	指定したボタンが押されたか
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
	@breif	ゲームパッド入力
	@param	i_pad	:	指定したボタンが押されたか
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
	@brief 背景色設定・取得
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
	@brief	点を描画	
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
	@breif	デバッグテキスト描画
	@param	ip_str	:	テキスト
	@param	i_x		:	x座標
	@param	i_y		:	y座標
	@param	i_color	:	カラー
*/
void GameSystem::DrawDebugText( const char* ip_str, int i_x, int i_y, const int i_color )
{
	// DirectX側ではマルチバイトかもしれないので変換してから使う
	_TCHAR buf[256];
	::memset( buf, NULL, sizeof(buf) * sizeof(_TCHAR) );
	#ifdef UNICODE
		// マルチバイト文字に変換
		MultiByteToWideChar( CP_OEMCP, MB_PRECOMPOSED, ip_str, ::strlen(ip_str), buf, (sizeof buf)/2 );
	#else
		::strcpy_s( buf, ip_str );
	#endif

	DirectX::Manager::Inst().DrawDebugText( buf, i_x, i_y, i_color );
}

/*
	@brief	コンフィグ取得
*/
const GameSystem::GameConfig&	GameSystem::GetConfig() const
{
	return	s_ConfigData;
}

/*
	@brief	変数クリア
*/
void	GameSystem::GameConfig::_Clear()
{
	m_ScreenSizeType = SIZE_640_480;
	sprintf_s( m_AppName, "Game" );
}

/*
	@brief	スクリーンサイズ取得
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

