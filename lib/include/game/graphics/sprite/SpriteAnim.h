/**
 *	@file 	Sp.h
 *	@brief	スプライト画像制御
 *	@author	yuto uchida
 *	@data   2010-03-09
 *	@note	gpcファイルを扱うクラス
 *
 */
#ifndef __GAME_SPRITE_ANIM_IMP_H__
#define __GAME_SPRITE_ANIM_IMP_H__

#include "common/Man.h"
#include "game/graphics/Camera.h"

namespace GameLib
{
	class	SpriteInterface;
	class	Texture;
	class	File;

	class SpriteAnim
	{
	public:
		//	定義
		enum DRAW_TYPE
		{
			TYPE_2D	= 0,
			TYPE_3D,
		};

		//	コンストラクタ
		SpriteAnim( GameLib::File* file, const DRAW_TYPE in_Type );
		~SpriteAnim();

		// アニメ最大数
		unsigned GetMaxAnim() { return mp_Data->GetDatMax(); }

		// アニメIdx
		unsigned GetIdxAnim() const;

		// アニメ変更
		void ChgIdxAnim( unsigned idx );

		// アニメ変更(名前指定用)
		// まだ作ってない
		void ChgNameAnim( const char *const name );

		// アニメストップ
		void Stop() { mp_Anim->mb_Play = false; }
		// アニメ再生
		void Play( bool bInitFrame = false ) { mp_Anim->Play(bInitFrame); }
		//	アニメ再生ループ
		void PlayLoop( bool bInitFrame = false );

		bool IsPlay() { return mp_Anim->mb_Play; }
		// アニメスピード
		void SetAnimSpeed( float speed ) { mp_Anim->mf_AnimSpeed = speed; }
		// フレーム設定
		void SetAnimFrame( unsigned frame ) { mp_Anim->m_NowFrame = frame; }

		// 現在フレーム
		const unsigned GetAnimFrame() const { return mp_Anim->m_NowFrame; }
		// 最大フレーム数取得
		const unsigned GetAnimFrameMax() const { return mp_Data->GetFrameMax(mp_Anim->m_DatIdx); }

		// スプライト回転
		void SetRota( float sita );
		// スプライト拡大縮小
		void SetScale( float scale );

		// 矩形情報取得
		RECT_DATA_ST& GetRect();
		// 座標取得
		Vec3& GetPos();
		// 色 設定/取得
		unsigned GetAddRGB() const;
		void SetAddRGB( unsigned rgb );

		// 透明度指定
		void SetAlpha( const unsigned char a );
		unsigned char GetAlpha() const;

		// 描画ON/OFF
		void SetVisible( bool bFlg );
		// 座標設定
		void SetPos( const float x, const float y );
		void SetPos( const Vec3 &vec );
		void SetLeftPos( const float x, const float y );
		void SetLeftPos( const Vec3 &vec );

		// 更新
		void Update() { mp_Anim->Update(); }

		// 描画
		void Draw();
		void Draw( Camera& in_Cam );
	private:
		//	スプライトデータ
		class Data
		{
		public:
			//	定義
			//	ファイルヘッダー
			struct	_tag_head
			{
				unsigned	max;			//	スプライト数
				unsigned	transColor;		//	透過色
				unsigned	w, h;			//	スプライトの縦横サイズ
				unsigned	pixelSize;		//	スプライトの総ピクセルのサイズ
			} m_Head;

			struct	_tag_galeDat
			{
				unsigned	frameMax;		//	スプライトのフレーム数
				char	*pName;				//

				//	アニメデータ
				struct	_tag_frame
				{
					unsigned	time;		//	フレーム切り替えタイム
					unsigned	layerMax;	//	レイアウト数(１フレーム内に多数のレイアウト)
					unsigned	**p;
				} *pFrame;
			} *mp_Dat;

			//	コンストラクタ
			Data( GameLib::File* file );
			~Data();

			const unsigned w() const { return m_Head.w; }
			const unsigned h() const { return m_Head.h; }
			const unsigned GetDatMax() const { return m_Head.max; }
			const unsigned GetTransColor() const { return m_Head.transColor; }
			const unsigned GetFrameMax( unsigned datIdx ) const { return mp_Dat[datIdx].frameMax; }
			const unsigned GetLayerMax( unsigned datIdx, unsigned frameIdx ) const
				{ return mp_Dat[datIdx].pFrame[frameIdx].layerMax; }
			const unsigned GetAnimTime( unsigned datIdx, unsigned frameIdx ) const
				{ return mp_Dat[datIdx].pFrame[frameIdx].time; }
			unsigned **GetAddrPixel( unsigned datIdx, unsigned frameIdx )
				{ return mp_Dat[datIdx].pFrame[frameIdx].p; }
		};

		/*
			@brief	アニメ制御
		*/
		class Anim
		{
		public:
			//	コンストラクタ
			Anim( Data *pData );
			~Anim() {}

			//	アニメ変更
			void ChgAnim( unsigned idx );

			// 更新
			void Update();
			//	再生
			void Play( bool bInitFrame );

			// Spriteクラス内のみ限定のクラスなのでSpriteクラスでデータを直で使用できるようにする。
			// 関数のオーバーヘッドが怖い
			// 細かい設定をしているメソッドにする
			unsigned	m_AnimTime,  m_NowFrame, m_AnmTime, m_DatIdx;
			float	mf_NowFrame, mf_AnimSpeed;
			bool	mb_Play, mb_Loop;
			Data	*mp_Data;
		};

		SpriteInterface	*mp_Sp;
		Texture			*mp_Tex;
		Data			*mp_Data;
		Anim			*mp_Anim;

		unsigned char m_Alpha;
	};

}	//	GameLib

#endif // __GAME_SPRITE_ANIM_IMP_H__

