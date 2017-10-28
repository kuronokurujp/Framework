/**
 *	@file 	D:/work/dungeon/framework/game/graphics/Camera.cpp
 *	@brief	
 *	@author	yuto uchida
 *	@data   2010-12-02
 *	@note 	カメラ制御
 *
 */
#include "game/graphics/Camera.h"
#include "directx/Manager.h"

#include "common/Common.h"

#ifdef _DEBUG

#include "game/GameSystem.h"
#include <string>

#endif

namespace GameLib
{
	Camera::Camera()	:
	m_pos(0.f, 0.f, 0.f),
	m_target(0.f, 0.f, 3.f),
	m_up(0.f, 1.f, 0.f),
	m_zoom(4.f)
	{
	}

	Camera::~Camera() {}

	/*
		@brief	更新
	*/
	void Camera::Update()
	{
		LPDIRECT3DDEVICE9	device = DirectX::Manager::Inst().GetDevice();

		// 視点座標変換
		// 配置したモデルは視点位置に移動させる
		D3DXMATRIXA16 mat_view, mat_pos, mat_yaw, mat_pitch;
		D3DXMatrixIdentity(&mat_view);
		D3DXMatrixIdentity(&mat_pos);
		D3DXMatrixIdentity(&mat_yaw);
		D3DXMatrixIdentity(&mat_pitch);

		// カメラの位置取得
		D3DXMatrixLookAtLH( &mat_pos, &m_pos, &m_target, &m_up );
		D3DXMatrixMultiply( &mat_view, &mat_view, &mat_pos );

		device->SetTransform( D3DTS_VIEW, &mat_view);

		// 射影変換
		// 視点のパーツや距離感を設定
		D3DXMATRIXA16 mat_proj;
		D3DXMatrixPerspectiveFovLH( &mat_proj, D3DX_PI / m_zoom, 1.f, 1.f, 100.f );
		device->SetTransform( D3DTS_PROJECTION, &mat_proj);

		//	各ビュー/射影行列取得
		device->GetTransform( D3DTS_VIEW, &m_ViewMat );
		device->GetTransform( D3DTS_PROJECTION, &m_ProjMat );

		m_Dist	= m_pos;
		m_Dist	-= m_target;
	}

	/*
		@brief	位置設定
	*/
	void	Camera::SetPos( const Vec3& i_pos )
	{
		::memcpy( &m_pos, &i_pos, sizeof(i_pos) );
	}

	/*
		@brief	注視位置設定
	*/
	void	Camera::SetTarget( const Vec3& i_target )
	{
		::memcpy( &m_target, &i_target, sizeof(i_target) );
	}

	/*
		@brief	ズーム係数設定
	*/
	void	Camera::SetZoom( const float& i_zoom )
	{
		m_zoom = i_zoom;
	}

	/*
		@brief	カメラの位置と視点からの角度取得
	*/
	const float Camera::GetYaw()
	{
		Vec3	v	= m_pos;
		v -= m_target;

		float	yaw	= 0.f;
		if( v.x >= 0.f )
		{
			yaw	= -atanf( v.z / v.x ) - D3DX_PI / 2 ;
		}
		else
		{
			yaw	= -atanf( v.z / v.x ) + D3DX_PI / 2 ;
		}

		return	yaw;
	}

	const float Camera::GetPitch()
	{
		Vec3	v	= m_pos;
		v -= m_target;

		float	pitch	= 0.f;
		float	dist	= (float)sqrt( v.z * v.z + v.x * v.x );
		if( v.y >= 0.f )
		{
			pitch	= -atanf( dist / v.y ) - D3DX_PI / 2 ;
		}
		else
		{
			pitch	= -atanf( dist / v.y ) + D3DX_PI / 2 ;
		}

		return	pitch;
	}

	const float Camera::GetRoll()
	{
		float	roll	= 0.f;
		return	roll;
	}

	/*
		@brief	カメラのデバッグ情報を画面に出力
		@param	in_BaseXPos	: 表示出力基点X座標
		@param	in_BaseYPos	: 表示出力基点Y座標
	*/
	void	Camera::DebugPrint( const int in_BaseXPos, const int in_BaseYPos )
	{
#ifdef _DEBUG
		GameSystem&	inst	= GameSystem::Inst();

		std::string	str	= "";

		char	aTmpStr[ 256 ]	= { NULL };
		sprintf_s( aTmpStr, sizeof( aTmpStr ), "Camera Debug\n" );
		str	+= aTmpStr;

		//	カメラ座標
		{
			sprintf_s( aTmpStr, sizeof( aTmpStr ), 
				"Pos X[%lf] Y[%lf] Z[%lf]\n", m_pos.x, m_pos.y, m_pos.z );
			str	+= aTmpStr;
		}

		//	カメラ注視点
		{
			sprintf_s( aTmpStr, sizeof( aTmpStr ),
				"Target X[%lf] Y[%lf] Z[%lf]\n", m_target.x, m_target.y, m_target.z );
			str	+= aTmpStr;
		}

		//	カメラ画角
		{
			sprintf_s( aTmpStr, sizeof( aTmpStr ), "Zoom[%lf]\n", m_zoom );
			str	+= aTmpStr;
		}

		inst.DrawDebugText( str.c_str(), in_BaseXPos, in_BaseYPos );
#endif
	}
}
