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
		@brief	���\�[�X�̃N���A
	*/
	void BaseMesh::Clear()
	{
		SAFE_RELEASE(mp_mesh);
		SAFE_DELETE( mp_materials );
		SAFE_DELETE( mp_texture );
	}

	/*
		@brief	�X�V
	*/
	void BaseMesh::Update()
	{
		LPDIRECT3DDEVICE9	device = DirectX::Manager::Inst().GetDevice();

		// ��΍��W�ϊ�
		// ���f���͔z�u
		D3DXMATRIXA16 mat_world,  mat_position, mat_scaling, mat_rotation, mat_rotation_2;
		D3DXMatrixIdentity( &mat_world );
		D3DXMatrixIdentity( &mat_rotation );
		D3DXMatrixIdentity( &mat_rotation_2 );
		// ��]�s��v�Z
		// �s�b�`��]
		D3DXMatrixRotationX( &mat_rotation_2, m_rot.x);
		D3DXMatrixMultiply( &mat_rotation, &mat_rotation, &mat_rotation_2 );
		// ���[��]
		D3DXMatrixRotationY( &mat_rotation_2, m_rot.y);
		D3DXMatrixMultiply( &mat_rotation, &mat_rotation, &mat_rotation_2 );

		// ���[����]
		D3DXMatrixRotationZ( &mat_rotation_2, m_rot.z);
		D3DXMatrixMultiply( &mat_rotation, &mat_rotation, &mat_rotation_2 );

		// �g��E�k��
		D3DXMatrixScaling( &mat_scaling, m_scale.x, m_scale.y, m_scale.z );
		// ���s�s��v�Z
		D3DXMatrixTranslation( &mat_position, m_pos.x, m_pos.y, m_pos.z );

		D3DXMatrixMultiply( &mat_world, &mat_world, &mat_scaling );
		D3DXMatrixMultiply( &mat_world, &mat_world, &mat_rotation );
		D3DXMatrixMultiply( &mat_world, &mat_world, &mat_position );
		// �r���{�[�h�ݒ�
		if( mb_billboard == true )
		{
			D3DXMATRIXA16	mat_current_view;
			// �J�����s����擾
			device->GetTransform( D3DTS_VIEW, &mat_current_view );
			// �J�����s����t�s��ɂ���
			D3DXMatrixInverse( &mat_current_view, NULL, &mat_current_view );
			// ���[���h�s��Ɋ|���āA�����_�����O�ł̃J�����s��v�Z��ł�����
			D3DXMatrixMultiply( &mat_world, &mat_world, &mat_current_view );
		}

		m_world_max	= mat_world;
	}

	/*
		@brief	�`��
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
		@brief	���W�ݒ�
	*/
	void BaseMesh::SetPos( const Vec3&	i_pos )
	{
		::memcpy( &m_pos, &i_pos, sizeof(m_pos));
	}

	/*
		@brief	��]���ݒ�
	*/
	void BaseMesh::SetRot( const Vec3&	i_rot )
	{
		::memcpy( &m_rot, &i_rot, sizeof(m_rot));
	}

	/*
		@brief	�X�P�[���ݒ�
	*/
	void BaseMesh::SetScale( const Vec3&	i_scale )
	{
		::memcpy( &m_scale, &i_scale, sizeof(m_scale));
	}

	/*
		@brief	���b�V���̊O�ډ~�̒��S�Ɣ��a���擾
		@param	���S���W�擾�A�h���X
		@param	���a�擾�A�h���X
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

			// ���b�V���̊O�ډ~�̒��S�Ɣ��a���擾�ł���
			D3DXComputeBoundingSphere(	(D3DXVECTOR3*)p_vertices, mp_mesh->GetNumVertices(), 
										D3DXGetFVFVertexSize( mp_mesh->GetFVF()), op_center, op_radius );
		}
		else
		{
			cprintf("%s %d : Error getSphereData", __FILE__, __LINE__ );
		}
	}

	/*
		@brief	�e�N�X�`���f�[�^�擾
		@param	[in] : in_Index �f�[�^�C���f�b�N�X�w��
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
		@brief	�}�e���A���f�[�^�擾
		@param	[in] : in_Index �f�[�^�C���f�b�N�X�w��
	*/
	//	�}�e���A���f�[�^�擾
	D3DMATERIAL9*		BaseMesh::GetMaterial( const unsigned in_Index )
	{
		if( in_Index < m_materials_num )
		{
			return	&mp_materials[ in_Index ];
		}

		return	NULL;
	}
}
