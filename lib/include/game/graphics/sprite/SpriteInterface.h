/********************************************************************
	created:	2012/06/17
	created:	17:6:2012   9:08
	file base:	SpriteInterface
	
	purpose:	
*********************************************************************/
#ifndef __SPRITEINTERFACE_H__
#define __SPRITEINTERFACE_H__

#include "common/Common.h"
#include "common/Man.h"
#include "game/graphics/Camera.h"

namespace	GameLib
{
	class	Texture;

	/*
		@brief	スプライトアクセサのインターフェイス
	*/
	class SpriteInterface
	{
	public:
		SpriteInterface() {};
		virtual ~SpriteInterface()	{}

		//	作成
		virtual	const bool	Create( class Texture* in_pTex )	= 0;

		//	開放
		virtual	void	Destroy()	= 0;

		// 描画
		virtual	void Draw()	= 0;
		virtual void Draw( Camera& in_Cam ) = 0;

		// 座標設定
		virtual	void SetPos( const Vec3 &vec )	= 0;

		// 座標取得
		virtual	const Vec3&	GetPos() const	= 0;
		virtual	Vec3 &GetPos()	= 0;

		// 画像範囲設定
		virtual	void SetImgRect( RECT_DATA_ST *pRect )	= 0;
		virtual	void SetImgRect( unsigned x, unsigned y, unsigned x2, unsigned y2 )	= 0;
		// 画像範囲取得
		virtual	RECT_DATA_ST& GetImgRect()	= 0;

		// スプライト回転
		virtual	void SetRota(float sita)	= 0;
		// スプライト拡大縮小
		virtual	void SetScale(float scale)	= 0;

		// 色 設定/取得
		virtual	const unsigned GetAddRGB() const	= 0;
		virtual	void SetAddRGB( unsigned rgb )	= 0;

		// 描画ON/OFF
		virtual	void SetVisible( bool bFlg )	= 0;
		// アルファON/OFF
		virtual	void EnableAlpha( bool flg )	= 0;
	};
}

#endif // __SPRITEINTERFACE_H__