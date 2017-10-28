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
			@brief	リソースのクリア
		*/
		void Clear();
		/*
			@brief	更新
		*/
		void Update();
		/*
			@brief	描画
		*/
		void Draw();
		/*
			@brief	座標設定
		*/
		void	SetPos( const Vec3&	i_pos );
		Vec3&	GetPos() { return m_pos; }
		/*
			@brief	回転軸設定
		*/
		void	SetRot( const Vec3&	i_rot );
		Vec3&	GetRot() { return m_pos; }
		/*
			@brief	スケール設定
		*/
		void	SetScale( const Vec3&	i_scale );
		Vec3&	GetScale() { return m_pos; }

		/*
			@brief	ビルボード設定
		*/
		void EnableBillboard( bool i_flg ) { mb_billboard = i_flg; }

		/*
			@brief	メッシュの外接円の中心と半径を取得
			@param	中心座標取得アドレス
			@param	半径取得アドレス
		*/
		void GetSphereData( Vec3* const op_center, float* const op_radius );

		// メッシュ取得
		LPD3DXMESH		GetMesh() const { return mp_mesh; }

		//	ワールド行列取得
		D3DXMATRIXA16	GetWorldMat() const { return m_world_max; }

		//	テクスチャデータ取得
		LPDIRECT3DTEXTURE9	GetTextureData( const unsigned in_Index );

		//	マテリアルデータ取得
		D3DMATERIAL9*		GetMaterial( const unsigned in_Index );

		//	マテリアル数
		const DWORD	GetMaterialNum() const { return m_materials_num; }

	protected:

		//	変数
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
