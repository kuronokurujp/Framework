/**
 *	@file 	Sprite.h
 *	@brief
 *	@author	yuto uchida
 *	@data   2010-02-22
 *	@note
 *
 */
#ifndef __GAME_SPRITE_H__
#define __GAME_SPRITE_H__

#include "game/graphics/sprite/SpriteInterface.h"

namespace DirectX
{
	class SpriteImpl;
}

namespace GameLib
{
	// スプライト単体クラス
	class Texture;
	class Sprite : public SpriteInterface
	{
	public:
		// スプライト作成
		Sprite() { _Clear(); }
		virtual ~Sprite();

		//	作成
		const bool	Create( class Texture* in_pTex );

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
		void SetImgRect( RECT_DATA_ST *pRect );
		void SetImgRect( unsigned x,	unsigned y,
						 unsigned x2,	unsigned y2 );
		// 画像範囲取得
		RECT_DATA_ST& GetImgRect();

		// スプライト回転
		void SetRota(float sita);
		// スプライト拡大縮小
		void SetScale(float scale);
		
		// 色 設定/取得
		const unsigned GetAddRGB() const;
		void SetAddRGB( unsigned rgb );
				
		// 描画ON/OFF
		void SetVisible( bool bFlg );
		// アルファON/OFF
		void EnableAlpha( bool flg );

	protected:
		DirectX::SpriteImpl *mp_Impl;

		Texture *mp_Tex;

	private:
		//	関数
		void	_Clear()	{ mp_Impl	= NULL; mp_Tex	= NULL; }

		bool mb_Alpha;
	};

} // namespace GameLib


#endif // __GAME_SPRITE_H__
