/**
 *	@file 	D:/work/dungeon/framework/game/graphics/model/BaseMesh.h
 *	@brief	
 *	@author	yuto uchida
 *	@data   2010-12-02
 *	@note 
 *
 */
#ifndef __BASEMESH_H__
#define __BASEMESH_H__

#include "directx/Manager.h"
#include "common/Man.h"

namespace GameLib
{
	class BaseMesh
	{
	public:

		BaseMesh();
		virtual ~BaseMesh();
		/*
			@brief	���\�[�X�̃N���A
		*/
		void Clear();
		/*
			@brief	�X�V
		*/
		void Update();
		/*
			@brief	�`��
		*/
		void Draw();
		/*
			@brief	���W�ݒ�
		*/
		void	SetPos( const Vec3&	i_pos );
		Vec3&	GetPos() { return m_pos; }
		/*
			@brief	��]���ݒ�
		*/
		void	SetRot( const Vec3&	i_rot );
		Vec3&	GetRot() { return m_pos; }
		/*
			@brief	�X�P�[���ݒ�
		*/
		void	SetScale( const Vec3&	i_scale );
		Vec3&	GetScale() { return m_pos; }

		/*
			@brief	�r���{�[�h�ݒ�
		*/
		void EnableBillboard( bool i_flg ) { mb_billboard = i_flg; }

		/*
			@brief	���b�V���̊O�ډ~�̒��S�Ɣ��a���擾
			@param	���S���W�擾�A�h���X
			@param	���a�擾�A�h���X
		*/
		void GetSphereData( Vec3* const op_center, float* const op_radius );

		// ���b�V���擾
		LPD3DXMESH		GetMesh() const { return mp_mesh; }

		//	���[���h�s��擾
		D3DXMATRIXA16	GetWorldMat() const { return m_world_max; }

		//	�e�N�X�`���f�[�^�擾
		LPDIRECT3DTEXTURE9	GetTextureData( const unsigned in_Index );

		//	�}�e���A���f�[�^�擾
		D3DMATERIAL9*		GetMaterial( const unsigned in_Index );

		//	�}�e���A����
		const DWORD	GetMaterialNum() const { return m_materials_num; }

	protected:

		//	�ϐ�
		LPD3DXMESH			mp_mesh;
		D3DMATERIAL9*		mp_materials;
		LPDIRECT3DTEXTURE9*	mp_texture;

		Vec3	m_pos;
		Vec3	m_rot;
		Vec3	m_scale;
		DWORD	m_materials_num;

		D3DXMATRIXA16		m_world_max;		

		bool				mb_billboard;
	};
}
#endif // __BASEMESH_H__
