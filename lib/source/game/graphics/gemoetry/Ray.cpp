/**
 *	@file 	D:/ProgramStady/Game/framework/source/game/graphics/gemoetry/Ray.cpp
 *	@brief	
 *	@author	yuto uchida
 *	@data   2010-12-15
 *	@note 
 *
 */
#include "game/graphics/gemoetry/Ray.h"

#include "common/Env.h"

namespace GameLib {
	/*
		@note	�����`��
	*/
	Ray::Ray()	:
	m_spos(0.f, 0.f, 0.f),
	m_epos(0.f, 0.f, 0.f),
	m_pos(0.f, 0.f, 0.f),
	m_color( 0xffffffff )
	{
	}

	Ray::~Ray() {}

	/*
		@brief	�n�_�ƏI�_�̎w��
		@param	i_spos	:	�n�_���W
		@param	i_epos	:	�I�_���W
	*/
	void	Ray::SetLinePos( Vec3& i_spos,	Vec3& i_epos )
	{
		m_spos = i_spos;
		m_epos = i_epos;
	}

	/*
		@brief	�`����W�ݒ�
		@param	i_pos	:	���W
	*/
	void Ray::SetPos( Vec3&	i_pos	)
	{
		m_pos = i_pos;
	}

	void Ray::Draw()
	{
		LPDIRECT3DDEVICE9	device = DirectX::Manager::Inst().GetDevice();

		struct _tag_RayVertex
		{
			D3DXVECTOR3	vec;
			DWORD		color;
		} vertex[2] = {
			{ m_spos, m_color },
			{ m_epos, m_color },
		};

		// ���C�g��OFF�ɂ��Ȃ��ƐF�����f���Ȃ�
		// ���C�g��ON�ɂȂ��Ă���ƃ��C�g�̐F�ƒ��_�F�����킳��̂�
		// ���߂��F���łȂ�
		device->SetRenderState( D3DRS_LIGHTING, false );

		// ���C���̌��_���ړ�
		D3DXMATRIX	mat_world;
		D3DXMatrixTranslation( &mat_world, m_pos.x,m_pos.y, m_pos.z );
		device->SetTransform( D3DTS_WORLD, &mat_world );
		// ���C�̃����_�����O
		device->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE );
		device->DrawPrimitiveUP( D3DPT_LINELIST, 1, vertex, sizeof(struct _tag_RayVertex) );

		// OFF�ɂ������C�g�����ɖ߂�
		device->SetRenderState( D3DRS_LIGHTING, true );
	}
}
