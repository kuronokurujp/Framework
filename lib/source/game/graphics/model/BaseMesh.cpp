/**
 *	@file 	D:/work/dungeon/framework/game/graphics/model/BaseMesh.cpp
 *	@brief	
 *	@author	yuto uchida
 *	@data   2010-12-02
 *	@note 
 *
 */
#include "game/graphics/model/BaseMesh.h"

#include "common/Common.h"

namespace GameLib {

	BaseMesh::BaseMesh()	:	
	mp_mesh(NULL),
	mp_materials(NULL),
	mp_texture(NULL),
	m_pos(0,0,0),
	m_rot(0,0,0),
	m_scale(1.f,1.f,1.f),
	m_materials_num(0),
	mb_billboard(false)
	{
	}

	BaseMesh::~BaseMesh() {}

	/*
		@brief	リソースのクリア
	*/
	void BaseMesh::Clear()
	{
		SAFE_RELEASE(mp_mesh);
		SAFE_DELETE( mp_materials );
		SAFE_DELETE( mp_texture );
	}

	/*
		@brief	更新
	*/
	void BaseMesh::Update()
	{
		LPDIRECT3DDEVICE9	device = DirectX::Manager::Inst().GetDevice();

		// 絶対座標変換
		// モデルは配置
		D3DXMATRIXA16 mat_world,  mat_position, mat_scaling, mat_rotation, mat_rotation_2;
		D3DXMatrixIdentity( &mat_world );
		D3DXMatrixIdentity( &mat_rotation );
		D3DXMatrixIdentity( &mat_rotation_2 );
		// 回転行列計算
		// ピッチ回転
		D3DXMatrixRotationX( &mat_rotation_2, m_rot.x);
		D3DXMatrixMultiply( &mat_rotation, &mat_rotation, &mat_rotation_2 );
		// ヨー回転
		D3DXMatrixRotationY( &mat_rotation_2, m_rot.y);
		D3DXMatrixMultiply( &mat_rotation, &mat_rotation, &mat_rotation_2 );

		// ロール回転
		D3DXMatrixRotationZ( &mat_rotation_2, m_rot.z);
		D3DXMatrixMultiply( &mat_rotation, &mat_rotation, &mat_rotation_2 );

		// 拡大・縮小
		D3DXMatrixScaling( &mat_scaling, m_scale.x, m_scale.y, m_scale.z );
		// 平行行列計算
		D3DXMatrixTranslation( &mat_position, m_pos.x, m_pos.y, m_pos.z );

		D3DXMatrixMultiply( &mat_world, &mat_world, &mat_scaling );
		D3DXMatrixMultiply( &mat_world, &mat_world, &mat_rotation );
		D3DXMatrixMultiply( &mat_world, &mat_world, &mat_position );
		// ビルボード設定
		if( mb_billboard == true )
		{
			D3DXMATRIXA16	mat_current_view;
			// カメラ行列を取得
			device->GetTransform( D3DTS_VIEW, &mat_current_view );
			// カメラ行列を逆行列にする
			D3DXMatrixInverse( &mat_current_view, NULL, &mat_current_view );
			// ワールド行列に掛けて、レンダリングでのカメラ行列計算を打ち消す
			D3DXMatrixMultiply( &mat_world, &mat_world, &mat_current_view );
		}

		m_world_max	= mat_world;
	}

	/*
		@brief	描画
	*/
	void BaseMesh::Draw()
	{
		LPDIRECT3DDEVICE9	device = DirectX::Manager::Inst().GetDevice();

		device->SetTransform( D3DTS_WORLD, &m_world_max );

		for( unsigned i=0; i < m_materials_num; ++i )
		{
			if( mp_materials )
			{
				device->SetMaterial( &mp_materials[i] );
			}

			if( mp_texture )
			{
				device->SetTexture( 0, mp_texture[i] );
			}

			mp_mesh->DrawSubset(i);
		}
	}

	/*
		@brief	座標設定
	*/
	void BaseMesh::SetPos( const Vec3&	i_pos )
	{
		::memcpy( &m_pos, &i_pos, sizeof(m_pos));
	}

	/*
		@brief	回転軸設定
	*/
	void BaseMesh::SetRot( const Vec3&	i_rot )
	{
		::memcpy( &m_rot, &i_rot, sizeof(m_rot));
	}

	/*
		@brief	スケール設定
	*/
	void BaseMesh::SetScale( const Vec3&	i_scale )
	{
		::memcpy( &m_scale, &i_scale, sizeof(m_scale));
	}

	/*
		@brief	メッシュの外接円の中心と半径を取得
		@param	中心座標取得アドレス
		@param	半径取得アドレス
	*/
	void BaseMesh::GetSphereData( Vec3* const op_center, float* const op_radius )
	{
		if( op_center && op_radius )
		{
			LPDIRECT3DVERTEXBUFFER9	p_vb = NULL;
			if( FAILED( mp_mesh->GetVertexBuffer( &p_vb ) ) )
			{
				cprintf("%s %d : Vertex Error getSphereData", __FILE__, __LINE__ );
				return;
			}

			void*	p_vertices = NULL;
			if( FAILED( p_vb->Lock( 0, 0, &p_vertices, 0 ) ) )
			{
				cprintf("%s %d : Vertex Lock Error getSphereData", __FILE__, __LINE__ );
				SAFE_RELEASE( p_vb );
				return;
			}

			// メッシュの外接円の中心と半径が取得できる
			D3DXComputeBoundingSphere(	(D3DXVECTOR3*)p_vertices, mp_mesh->GetNumVertices(), 
										D3DXGetFVFVertexSize( mp_mesh->GetFVF()), op_center, op_radius );
		}
		else
		{
			cprintf("%s %d : Error getSphereData", __FILE__, __LINE__ );
		}
	}

	/*
		@brief	テクスチャデータ取得
		@param	[in] : in_Index データインデックス指定
	*/
	LPDIRECT3DTEXTURE9	BaseMesh::GetTextureData( const unsigned in_Index )
	{
		if( in_Index < m_materials_num )
		{
			return mp_texture[ in_Index ];
		}

		return	NULL;
	}

	/*
		@brief	マテリアルデータ取得
		@param	[in] : in_Index データインデックス指定
	*/
	//	マテリアルデータ取得
	D3DMATERIAL9*		BaseMesh::GetMaterial( const unsigned in_Index )
	{
		if( in_Index < m_materials_num )
		{
			return	&mp_materials[ in_Index ];
		}

		return	NULL;
	}
}
