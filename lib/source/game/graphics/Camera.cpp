/**
 *	@file 	D:/work/dungeon/framework/game/graphics/Camera.cpp
 *	@brief	
 *	@author	yuto uchida
 *	@data   2010-12-02
 *	@note 	�J��������
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
		@brief	�X�V
	*/
	void Camera::Update()
	{
		LPDIRECT3DDEVICE9	device = DirectX::Manager::Inst().GetDevice();

		// ���_���W�ϊ�
		// �z�u�������f���͎��_�ʒu�Ɉړ�������
		D3DXMATRIXA16 mat_view, mat_pos, mat_yaw, mat_pitch;
		D3DXMatrixIdentity(&mat_view);
		D3DXMatrixIdentity(&mat_pos);
		D3DXMatrixIdentity(&mat_yaw);
		D3DXMatrixIdentity(&mat_pitch);

		// �J�����̈ʒu�擾
		D3DXMatrixLookAtLH( &mat_pos, &m_pos, &m_target, &m_up );
		D3DXMatrixMultiply( &mat_view, &mat_view, &mat_pos );

		device->SetTransform( D3DTS_VIEW, &mat_view);

		// �ˉe�ϊ�
		// ���_�̃p�[�c�⋗������ݒ�
		D3DXMATRIXA16 mat_proj;
		D3DXMatrixPerspectiveFovLH( &mat_proj, D3DX_PI / m_zoom, 1.f, 1.f, 100.f );
		device->SetTransform( D3DTS_PROJECTION, &mat_proj);

		//	�e�r���[/�ˉe�s��擾
		device->GetTransform( D3DTS_VIEW, &m_ViewMat );
		device->GetTransform( D3DTS_PROJECTION, &m_ProjMat );

		m_Dist	= m_pos;
		m_Dist	-= m_target;
	}

	/*
		@brief	�ʒu�ݒ�
	*/
	void	Camera::SetPos( const Vec3& i_pos )
	{
		::memcpy( &m_pos, &i_pos, sizeof(i_pos) );
	}

	/*
		@brief	�����ʒu�ݒ�
	*/
	void	Camera::SetTarget( const Vec3& i_target )
	{
		::memcpy( &m_target, &i_target, sizeof(i_target) );
	}

	/*
		@brief	�Y�[���W���ݒ�
	*/
	void	Camera::SetZoom( const float& i_zoom )
	{
		m_zoom = i_zoom;
	}

	/*
		@brief	�J�����̈ʒu�Ǝ��_����̊p�x�擾
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
		@brief	�J�����̃f�o�b�O������ʂɏo��
		@param	in_BaseXPos	: �\���o�͊�_X���W
		@param	in_BaseYPos	: �\���o�͊�_Y���W
	*/
	void	Camera::DebugPrint( const int in_BaseXPos, const int in_BaseYPos )
	{
#ifdef _DEBUG
		GameSystem&	inst	= GameSystem::Inst();

		std::string	str	= "";

		char	aTmpStr[ 256 ]	= { NULL };
		sprintf_s( aTmpStr, sizeof( aTmpStr ), "Camera Debug\n" );
		str	+= aTmpStr;

		//	�J�������W
		{
			sprintf_s( aTmpStr, sizeof( aTmpStr ), 
				"Pos X[%lf] Y[%lf] Z[%lf]\n", m_pos.x, m_pos.y, m_pos.z );
			str	+= aTmpStr;
		}

		//	�J���������_
		{
			sprintf_s( aTmpStr, sizeof( aTmpStr ),
				"Target X[%lf] Y[%lf] Z[%lf]\n", m_target.x, m_target.y, m_target.z );
			str	+= aTmpStr;
		}

		//	�J������p
		{
			sprintf_s( aTmpStr, sizeof( aTmpStr ), "Zoom[%lf]\n", m_zoom );
			str	+= aTmpStr;
		}

		inst.DrawDebugText( str.c_str(), in_BaseXPos, in_BaseYPos );
#endif
	}
}
