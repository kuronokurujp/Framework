/**
 *	@file 	D:/work/dungeon/framework/game/grapchis/model/Mesh.h
 *	@brief	���b�V���N���X
 *	@author	yuto uchida
 *	@data   2010-12-01
 *	@note 	X�t�@�C���œǂݍ��񂾃��f������
 *
 */
#ifndef __MESH_H__
#define __MESH_H__

#include "./../../../directx/Manager.h"

#include "./BaseMesh.h"

namespace GameLib {

	// X�t�@�C���̃��b�V��
	class Mesh : public BaseMesh {
	public:
		/*
			@brief	�w�肵��X�t�@�C�����烁�b�V���쐬
			@note	X�t�@�C���ƎQ�Ƃ��Ă���e�N�X�`���t�@�C���͓����f�B���N�g���ɔz�u����B
		*/
		Mesh( const _TCHAR* ip_filename );
		~Mesh();

		/*
			@brief	�����쐬�������b�V�����ēx�쐬
		*/
		void Reset();
	private:
		/*
			@brief	���\�[�X�쐬
		*/
		void Create( const _TCHAR* ip_filename );

		_TCHAR*				mp_filename;
	};

	/*
		@note	���̃��b�V�����f��
	*/
	class	SphereMesh : public BaseMesh
	{
	public:
		SphereMesh( float i_radius );
		~SphereMesh();

		/*
			@brief	���b�V���č쐬
		*/
		void Reset();

	private:
		/*
			@brief	���b�V���쐬
		*/
		void Create( float i_radius );
		
		float	m_radius;
	};

}

#endif // __MESH_H__
