/**
 *	@file 	D:/work/dungeon/framework/game/grapchis/model/Mesh.h
 *	@brief	メッシュクラス
 *	@author	yuto uchida
 *	@data   2010-12-01
 *	@note 	Xファイルで読み込んだモデル制御
 *
 */
#ifndef __MESH_H__
#define __MESH_H__

#include "./../../../directx/Manager.h"

#include "./BaseMesh.h"

namespace GameLib {

	// Xファイルのメッシュ
	class Mesh : public BaseMesh {
	public:
		/*
			@brief	指定したXファイルからメッシュ作成
			@note	Xファイルと参照しているテクスチャファイルは同じディレクトリに配置する。
		*/
		Mesh( const _TCHAR* ip_filename );
		~Mesh();

		/*
			@brief	初期作成したメッシュを再度作成
		*/
		void Reset();
	private:
		/*
			@brief	リソース作成
		*/
		void Create( const _TCHAR* ip_filename );

		_TCHAR*				mp_filename;
	};

	/*
		@note	球のメッシュモデル
	*/
	class	SphereMesh : public BaseMesh
	{
	public:
		SphereMesh( float i_radius );
		~SphereMesh();

		/*
			@brief	メッシュ再作成
		*/
		void Reset();

	private:
		/*
			@brief	メッシュ作成
		*/
		void Create( float i_radius );
		
		float	m_radius;
	};

}

#endif // __MESH_H__
