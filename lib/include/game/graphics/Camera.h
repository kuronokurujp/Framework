/**
 *	@file 	/game/graphics/Camera.h
 *	@brief	カメラ制御
 *	@author	yuto uchida
 *	@data   2010-12-02
 *	@note	カメラの中心軸を動かす場合は注視点を
 *			位置を動かす時は座標を変更する。
 *
 */
#ifndef __GAME_SYSTEM_CAMERA_H__
#define __GAME_SYSTEM_CAMERA_H__

#include "common/Man.h"

namespace GameLib
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		/*
			@brief	更新
		*/
		void Update();

		/*
			@brief	位置設定
		*/
		void	SetPos( const Vec3& i_pos );
		/*
			@brief	注視位置設定
		*/
		void	SetTarget( const Vec3& i_target );
		/*
			@brief	ズーム係数設定
		*/
		void	SetZoom( const float& i_zoom );

		//	ビュー行列取得
		const Marixt4x4&	GetViewMat()	{ return m_ViewMat; }
		//	射影行列取得
		const Marixt4x4&	GetProjMat()	{ return m_ProjMat; }

		/*
			取得関連
		*/
		const Vec3&	GetPos() const { return m_pos; }
		const Vec3& GetTarget() const { return m_target; }
		const float GetYaw();
		const float GetPitch();
		const float GetRoll();
		//	視点と位置の方向ベクトル
		const Vec3&	GetDist()	{ return m_Dist; }

		/*
			@brief	カメラのデバッグ情報を画面に出力
			@param	in_BaseXPos	: 表示出力基点X座標
			@param	in_BaseYPos	: 表示出力基点Y座標
		*/
		void	DebugPrint( const int in_BaseXPos, const int in_BaseYPos );

	private:
		Vec3	m_pos;			// カメラ位置
		Vec3	m_target;		// 見ている箇所の座標
		Vec3	m_up;			// カメラ上方向(姿勢制御に使う)
		float	m_zoom;			// ズーム係数
		Vec3	m_Dist;

		Marixt4x4	m_ProjMat;
		Marixt4x4	m_ViewMat;
	};
}

#endif // __GAME_SYSTEM_CAMERA_H__
