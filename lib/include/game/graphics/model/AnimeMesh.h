/**
 *	@file 	AnimeMesh.h
 *	@brief	�A�j���[�V�����������Ă��郁�b�V���̐���
 *	@author	yuto uchida
 *	@data   2010-12-03
 *	@note 
 *
 */
#ifndef __ANIMEMESH_H__
#define __ANIMEMESH_H__

#include "directx/Manager.h"
#include "common/Man.h"

namespace GameLib
{
	class MeshLoadHierarchy;
	class AnimeMesh
	{
	public:
		AnimeMesh( const _TCHAR*	ip_filename );
		~AnimeMesh();
		/*
			@brief ���b�V���X�V
		*/
		void Update();
		/*
			@brief ���b�V���`��
		*/
		void Draw();

		/*
			@brief	���W�ݒ�E�擾
		*/
		void	SetPos( const Vec3& i_pos );
		Vec3&	GetPos() { return m_pos; }

		/*
			@brief	�Փˌ��n
			@param	ip_object	:	�I�u�W�F�N�g
			@note	�e���b�V���Ƃ̃��C�Փ˔�������Ă���
					���b�V���̐��������̂قǔ��菈������������̂ŏd��
					�������y�������
						�I�u�W�F�N�g�P�̂ł̃{�b�N�X or �X�t�B�A�ł̔���
							��Ԍy��
						�e���b�V���Ƃ̔���Ƀ{�b�N�X or �X�t�B�A�ł̔���
							���C��菈�����y���B
							�ł����b�V�����ƂɏՓ˔��肷��B
		*/
		bool	IsImpact( AnimeMesh* const ip_object );

		/*
			@brief	�A�j���^�C���ݒ�
			@param	i_time	:	�A�j���^�C��
		*/
		void SetAnimTime( float i_time );

		/*
			@brief	���f���̉�]��(Y��)
			@param	i_mat	:	Y���̃}�g���N�X
		*/
		void SetMatYaw( D3DXMATRIX&	i_mat )
		{
			m_mat_yaw = i_mat;
		}

		D3DXMATRIX&	GetMatYaw() { return m_mat_yaw; }
			
	private:
		/*
			@brief	�K�w���ƂɏՓ˔���
			@param	ip_frame_base		:	�t���[�����b�V��
			@param	ip_object			:	�Փˌ��n�I�u�W�F�N�g
		*/
		bool	IsFrameImpact( LPD3DXFRAME ip_frame_base, AnimeMesh* const ip_object );

		/*
			@brief	�K�w���܂߂Ă��ׂẴ��b�V���X�V
			@param	ip_frame			:	�t���[�����b�V��
			@param	ip_mat_world		:	���[���h�}�g���b�N�X
		*/
		void UpdateFrameMesh( LPD3DXFRAME ip_frame, D3DXMATRIX* const ip_mat_world );

		/*
			@brief	�K�w���܂߂Ă��ׂẴ��b�V���`��
			@param	ip_mesh_frame	:	��{�̃��b�V���t���[��
		*/
		void DrawFrameMesh( LPD3DXFRAME ip_mesh_frame );

		/*
			@brief	���b�V���`��
		*/
		void DrawMesh( LPD3DXMESHCONTAINER ip_mesh_ctrl_base, LPD3DXFRAME ip_mesh_frame );

		//	�ϐ�
		LPD3DXFRAME					mp_frame_root;
		LPD3DXANIMATIONCONTROLLER	mp_anim_ctrl;
		Vec3						m_pos;

		D3DXMATRIX					m_mat_world;
		D3DXMATRIX					m_mat_yaw;

		MeshLoadHierarchy*		mp_hierarchy;
	};

}
#endif // __ANIMEMESH_H__
