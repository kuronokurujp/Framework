/**
 *	@file 	Ray.h
 *	@brief	
 *	@author	yuto uchida
 *	@data   2010-12-15
 *	@note 
 *
 */
#ifndef __GEMOETRY_RAY_H__
#define __GEMOETRY_RAY_H__

#include "directx/Manager.h"
#include "common/Man.h"

namespace GameLib
{
	/*
		@note	線分描画
	*/
	class Ray
	{
	public:
		Ray();
		~Ray();

		/*
			@brief	始点と終点の指定
			@param	i_spos	:	始点座標
			@param	i_epos	:	終点座標
		*/
		void	SetLinePos( Vec3&	i_spos,	Vec3&	i_epos );

		/*
			@brief	描画座標設定
			@param	i_pos	:	座標
		*/
		void	SetPos( Vec3&	i_pos	);

		/*
			@brief	色
		*/
		void	SetColor( const unsigned i_rgb ) { m_color = i_rgb; }

		//	描画
		void	Draw();
	private:
		//	変数
		Vec3		m_spos, m_epos,	m_pos;
		unsigned	m_color;		// カラー
	};
}

#endif // __GEMOETRY_RAY_H__
