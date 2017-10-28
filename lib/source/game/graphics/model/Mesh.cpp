/**
 *	@file 	Mesh.cpp
 *	@brief	
 *	@author	yuto uchida
 *	@data   2010-12-01
 *	@note 
 *
 */
#include "game/graphics/model/Mesh.h"
#include "common/Common.h"

namespace GameLib
{
	/*
		@brief	�w�肵��X�t�@�C�����烁�b�V���쐬
		@note	X�t�@�C���ƎQ�Ƃ��Ă���e�N�X�`���t�@�C���͓����f�B���N�g���ɔz�u����B
	*/
	Mesh::Mesh( const _TCHAR* ip_filename )
	{
		Create( ip_filename );
		size_t	len = ::_tcslen(ip_filename);
		mp_filename = new _TCHAR[len+1];
		::memset( mp_filename, NULL, sizeof(_TCHAR) * (len+1));
		::_tcscpy_s(mp_filename, sizeof(_TCHAR) * (len+1),ip_filename);
	}
	Mesh::~Mesh()
	{
		Clear();
		SAFE_DELETE_ARRAY(mp_filename);
	}

	/*
		@note	�N���X�����ł����Ă���t�@�C�������烊�\�[�X�쐬
				�f�o�C�X���X�g�̎��Ɏg��
	*/
	void Mesh::Reset()
	{
		Clear();
		if( mp_filename ) {
			Create( mp_filename );
		}
	}

	/*
		@brief	���\�[�X�쐬
	*/
	void Mesh::Create( const _TCHAR* ip_filename )
	{
		LPDIRECT3DDEVICE9	device = DirectX::Manager::Inst().GetDevice();

		LPD3DXBUFFER	p_d3dx_material_buffer = NULL;
		if( FAILED( D3DXLoadMeshFromX(	ip_filename, D3DXMESH_SYSTEMMEM,
										device, NULL,
										&p_d3dx_material_buffer,
										NULL,
										&m_materials_num,
										&mp_mesh) ) ) {
			STRING_ASSERT(false, "Error Create Mesh\n");
		}

		D3DXMATERIAL*	p_d3dx_materials = (D3DXMATERIAL*)(p_d3dx_material_buffer->GetBufferPointer());
		mp_materials = new D3DMATERIAL9[m_materials_num];
		mp_texture = new LPDIRECT3DTEXTURE9[m_materials_num];

		for( unsigned i=0; i<m_materials_num; i++ )
		{
			mp_materials[i] = p_d3dx_materials[i].MatD3D;
			mp_texture[i] = NULL;
			if( (p_d3dx_materials[i].pTextureFilename != NULL) &&
				(lstrlen(p_d3dx_materials[i].pTextureFilename) > 0) )
			{
				if( FAILED( D3DXCreateTextureFromFile(	device,
														p_d3dx_materials[i].pTextureFilename,
														&mp_texture[i])) )
				{
					STRING_ASSERT(false, "Error Open File Texture\n");
				}
			}
		}

		p_d3dx_material_buffer->Release();
	}


	/*
		@note	���̃��b�V�����f��
	*/
	SphereMesh::SphereMesh( float i_radius )	:
	m_radius(i_radius)
	{
		Create( i_radius );
	}

	SphereMesh::~SphereMesh()
	{
		Clear();
	}

	/*
		@brief	���b�V���č쐬
	*/
	void SphereMesh::Reset()
	{
		Create( m_radius );
	}

	/*
		@brief	���b�V���쐬
	*/
	void SphereMesh::Create( float i_radius )
	{
		m_radius = i_radius;

		LPDIRECT3DDEVICE9	device = DirectX::Manager::Inst().GetDevice();

		if( FAILED( D3DXCreateSphere( device, m_radius, 24, 24, &mp_mesh, NULL) ) )
		{
			STRING_ASSERT(false, "���̃��b�V���쐬���s\n");
		}

		m_materials_num = 1;
		mp_materials = new D3DMATERIAL9;
		mp_materials->Diffuse.r = 1.0f;
		mp_materials->Diffuse.g = 1.0f;
		mp_materials->Diffuse.b = 1.0f;
		mp_materials->Diffuse.a = 0.5f;

		mp_materials->Ambient = mp_materials->Diffuse;

		mp_materials->Specular.r = 1.0f;
		mp_materials->Specular.g = 1.0f;
		mp_materials->Specular.b = 1.0f;

		mp_materials->Emissive.r = 1.0f;
		mp_materials->Emissive.g = 1.0f;
		mp_materials->Emissive.b = 1.0f;

		mp_materials->Power = 120.0f;
	}

} // namespace GameLib
