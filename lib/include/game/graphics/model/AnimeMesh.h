/**
 *	@file 	AnimeMesh.h
 *	@brief	アニメーションを持っているメッシュの制御
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
			@brief メッシュ更新
		*/
		void Update();
		/*
			@brief メッシュ描画
		*/
		void Draw();

		/*
			@brief	座標設定・取得
		*/
		void	SetPos( const Vec3& i_pos );
		Vec3&	GetPos() { return m_pos; }

		/*
			@brief	衝突検地
			@param	ip_object	:	オブジェクト
			@note	各メッシュとのレイ衝突判定をしている
					メッシュの数が多いのほど判定処理数が増えるので重い
					処理を軽くする案
						オブジェクト単体でのボックス or スフィアでの判定
							一番軽い
						各メッシュとの判定にボックス or スフィアでの判定
							レイより処理が軽い。
							でもメッシュごとに衝突判定する。
		*/
		bool	IsImpact( AnimeMesh* const ip_object );

		/*
			@brief	アニメタイム設定
			@param	i_time	:	アニメタイム
		*/
		void SetAnimTime( float i_time );

		/*
			@brief	モデルの回転軸(Y軸)
			@param	i_mat	:	Y軸のマトリクス
		*/
		void SetMatYaw( D3DXMATRIX&	i_mat )
		{
			m_mat_yaw = i_mat;
		}

		D3DXMATRIX&	GetMatYaw() { return m_mat_yaw; }
			
	private:
		/*
			@brief	階層ごとに衝突判定
			@param	ip_frame_base		:	フレームメッシュ
			@param	ip_object			:	衝突検地オブジェクト
		*/
		bool	IsFrameImpact( LPD3DXFRAME ip_frame_base, AnimeMesh* const ip_object );

		/*
			@brief	階層を含めてすべてのメッシュ更新
			@param	ip_frame			:	フレームメッシュ
			@param	ip_mat_world		:	ワールドマトリックス
		*/
		void UpdateFrameMesh( LPD3DXFRAME ip_frame, D3DXMATRIX* const ip_mat_world );

		/*
			@brief	階層を含めてすべてのメッシュ描画
			@param	ip_mesh_frame	:	大本のメッシュフレーム
		*/
		void DrawFrameMesh( LPD3DXFRAME ip_mesh_frame );

		/*
			@brief	メッシュ描画
		*/
		void DrawMesh( LPD3DXMESHCONTAINER ip_mesh_ctrl_base, LPD3DXFRAME ip_mesh_frame );

		//	変数
		LPD3DXFRAME					mp_frame_root;
		LPD3DXANIMATIONCONTROLLER	mp_anim_ctrl;
		Vec3						m_pos;

		D3DXMATRIX					m_mat_world;
		D3DXMATRIX					m_mat_yaw;

		MeshLoadHierarchy*		mp_hierarchy;
	};

}
#endif // __ANIMEMESH_H__
