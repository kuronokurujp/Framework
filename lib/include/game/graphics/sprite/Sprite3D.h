/********************************************************************
	created:	2012/05/27
	created:	27:5:2012   23:17
	file base:	Sprite3D
	
	purpose:	3Dスプライト描画
*********************************************************************/
#ifndef __SPRITE3D_H__
#define __SPRITE3D_H__

#include "game/graphics/sprite/SpriteInterface.h"

namespace	DirectX
{
	class	Sprite3DImpl;
}

namespace	GameLib
{
	class	Texture;
	class	Sprite3D : public SpriteInterface
	{
	public:
		//	コンストラクト
		explicit Sprite3D()	{ _Clear(); }
		~Sprite3D()	{}

		//	関数
		const bool	Create( Texture* in_pTex );

		//	開放
		void	Destroy();

		// 描画
		void Draw();
		void Draw( Camera& in_Cam );

		// 座標設定
		void SetPos( const Vec3 &vec );

		// 座標取得
		const Vec3&	GetPos() const;
		Vec3 &GetPos();

		// 画像範囲設定
		void SetImgRect( RECT_DATA_ST *pRect )	{}
		void SetImgRect( unsigned x, unsigned y, unsigned x2, unsigned y2 )	{}
		// 画像範囲取得
		RECT_DATA_ST& GetImgRect();

		// スプライト回転
		void SetRota(float sita)	{}
		// スプライト拡大縮小
		void SetScale(float scale)	{}

		// 色 設定/取得
		const unsigned GetAddRGB() const	{ return	0; }
		void SetAddRGB( unsigned rgb )	{}

		// 描画ON/OFF
		void SetVisible( bool bFlg )	{}
		// アルファON/OFF
		void EnableAlpha( bool flg )	{}

	private:
		//	関数
		void	_Clear();

		//	変数
		DirectX::Sprite3DImpl*	mp_Impl;
	};
}

#endif // __SPRITE3D_H__
