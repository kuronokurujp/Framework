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
		@note	線分描画
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
		@brief	始点と終点の指定
		@param	i_spos	:	始点座標
		@param	i_epos	:	終点座標
	*/
	void	Ray::SetLinePos( Vec3& i_spos,	Vec3& i_epos )
	{
		m_spos = i_spos;
		m_epos = i_epos;
	}

	/*
		@brief	描画座標設定
		@param	i_pos	:	座標
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

		// ライトをOFFにしないと色が反映しない
		// ライトがONになっているとライトの色と頂点色が合わさるので
		// 決めた色がでない
		device->SetRenderState( D3DRS_LIGHTING, false );

		// ラインの原点を移動
		D3DXMATRIX	mat_world;
		D3DXMatrixTranslation( &mat_world, m_pos.x,m_pos.y, m_pos.z );
		device->SetTransform( D3DTS_WORLD, &mat_world );
		// レイのレンダリング
		device->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE );
		device->DrawPrimitiveUP( D3DPT_LINELIST, 1, vertex, sizeof(struct _tag_RayVertex) );

		// OFFにしたライトを元に戻す
		device->SetRenderState( D3DRS_LIGHTING, true );
	}
}
