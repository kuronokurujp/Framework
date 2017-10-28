/**
 *	@file 	SpriteImpl.h
 *	@brief
 *	@author	yuto uchida
 *	@data   2009-08-01
 *	@note
 *
 */
#ifndef __DIRECTX_SPRITEIMP_H__
#define __DIRECTX_SPRITEIMP_H__

#include "directx/Manager.h"
#include "common/Common.h"
#include "common/Man.h"

namespace DirectX
{
    // スプライト単体クラス
    class SpriteImpl
	{
	public:
        // スプライト作成
        explicit SpriteImpl( IDirect3DTexture9 **const ppTex, unsigned int w, unsigned int h ) 
		:	mb_Visible( true )
		,	m_Scale(1.0f), m_Angle(0.0f)
		,	m_Color(0xffffffff)
		{
            _CalcVertexColor(m_Color);
            SetTex(ppTex, w, h);
            SetPos( 0, 0 );
        }

        ~SpriteImpl() {	mpp_Tex = NULL;	}

        // テクスチャー設定
        void SetTex( IDirect3DTexture9 **const ppTex, unsigned int w, unsigned int h )
		{
            ASSERT(ppTex);
            SetImgRect( 0, 0, w, h );

            // 頂点更新
            _CalcVertexPos(m_Angle, m_Scale);
            _CalcVertexTexUv(m_ImgRect, w, h);

            mpp_Tex = ppTex;
            m_W = w;
            m_H = h;
        }

        // 画像範囲設定
        void SetImgRect( RECT_DATA_ST *pRect )
		{
            SetImgRect( (unsigned)pRect->left, 
						(unsigned)pRect->top, 
						(unsigned)pRect->right, 
						(unsigned)pRect->bottom );
        }

        void SetImgRect( unsigned x, unsigned y, unsigned x2, unsigned y2 )
		{
            m_ImgRect.left		= (float)x;
            m_ImgRect.top		= (float)y;
            m_ImgRect.right		= (float)x2;
            m_ImgRect.bottom	= (float)y2;

            // ４頂点のオフセットベクトル取得
            {
                float fw = static_cast<float>((x2 - x) >> 1);
                float fh = static_cast<float>((y2 - y) >> 1);
                // 右下
				m_VertexOffset[0].Set( fw, -fh, 0.0f );
                // 右下
                m_VertexOffset[1].Set( fw, fh, 0.0f);
                // 左下
                m_VertexOffset[2].Set( -fw, -fh, 0.0f);
                // 左上
                m_VertexOffset[3].Set( -fw, fh, 0.0f);
            }

			// 頂点位置を再設定
            _CalcVertexPos(m_Angle, m_Scale);
			// テクスチャ範囲指定が変更されるかも
            _CalcVertexTexUv(m_ImgRect, m_W, m_H);
        }

        RECT_DATA_ST &GetImgRect() { return m_ImgRect; }

        // 座標設定
		void SetPos( const float x, const float y ) { m_Vec.x = x; m_Vec.y = y; }
		void SetPos( const Vec3 &vec ) { SetPos( vec.x, vec.y ); }

        const unsigned GetAddRGB() const { return m_Color; }
        void SetAddRGB(unsigned rgb)
		{
			m_Color = rgb;
            _CalcVertexColor(m_Color);
        }

        // スプライト回転
        void Rota(float sita)
		{
            if( sita != m_Angle )
			{
                _CalcVertexPos(sita, m_Scale);
                m_Angle = sita;
            }
        }

        // スプライト拡大縮小
        void Scale(float s)
		{
            if( s != m_Scale )
			{
                s = LOWER(s, 0.0f);
                _CalcVertexPos(m_Angle, s);
                m_Scale = s;
            }
        }

        // 描画
        void Draw()
		{
            if( mb_Visible == true )
			{
                ASSERT(mpp_Tex);

                // 描画する四点の頂点を作成
                // 2Dから3Dのベクトル変更
                // 頂点は3次元座標だから
				Vec3 vec;
				vec.Set( m_Vec.x, m_Vec.y, 0.0f);
                for( unsigned int i = 0; i < mc_VertexMax; ++i )
				{
					m_Vertex[i].vec		= ( m_VertexPos[i] + vec );
                    m_Vertex[i].vec.z	= 1.0f;
                }

				LPDIRECT3DDEVICE9 p = Manager::Inst().GetDevice();
                ASSERT(p);

                // テクスチャー設定
                p->SetTexture(0, *mpp_Tex);
                // 状態状態
                p->SetFVF(_tag_Vertex::FVF);
                // 描画
                p->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_Vertex, sizeof(struct _tag_Vertex));
            }
        }

        // 座標取得
		Vec3&	GetPos() { return m_Vec; }
        // 描画ON/OFF
        void	SetVisible( bool bFlg ) { mb_Visible = bFlg; }

	private:
		// 頂点カラ設定
		void _CalcVertexColor(unsigned int color)
		{
			for( unsigned int i = 0; i<mc_VertexMax; ++i )
			{
				m_Vertex[i].color = color;
			}
		}

		// 頂点データ座標計算
		// 回転/拡縮の変更を行う時に頂点位置を変更する
		void _CalcVertexPos(float rota, float scale )
		{
			// 回転・スケーリング行列作成
			Marixt4x4	mat;
			mat.Identity();
			mat.RotaY( rota );
			mat.Scale( scale, scale, scale );

			int max = ARRAY_NUM(m_VertexOffset);
			for( int i = 0; i < max; ++i )
			{
				m_VertexPos[i]	= mat.Transform( m_VertexOffset[i] );
			}
		}

		// 各頂点に貼り付けるテクスチャーUV計算
		void _CalcVertexTexUv( RECT_DATA_ST &rect, unsigned int w, unsigned int h)
		{
			Vec3 uv[mc_VertexMax];
			// rectはスクリーン座標系で定義
			// テクスチャーのUV座標作成
			{
				// 右上
				uv[0].x = static_cast<float>(rect.right);
				uv[0].y = static_cast<float>(rect.top);
				// 右下
				uv[1].x = uv[0].x;
				uv[1].y = static_cast<float>(rect.bottom);
				// 左上
				uv[2].x = static_cast<float>(rect.left);
				uv[2].y = uv[0].y;
				// 左下
				uv[3].x = uv[2].x;
				uv[3].y = uv[1].y;

				float rcpW = 1.0f / (static_cast<float>(w));
				float rcpH = 1.0f / (static_cast<float>(h));
				for( unsigned i = 0; i < mc_VertexMax; ++i )
				{
					m_Vertex[i].uv.x = uv[i].x * rcpW;
					m_Vertex[i].uv.y = uv[i].y * rcpH;
					m_Vertex[i].rhw = 1.0f;
				}
			}
		}

		//	変数
		RECT_DATA_ST	m_ImgRect;
		Vec3			m_Vec;
		IDirect3DTexture9 **mpp_Tex;

		bool mb_Visible;
		unsigned int m_W, m_H;
		unsigned int m_Color;
		float m_Scale, m_Angle;

		// プリミティブ頂点
		static const unsigned int mc_VertexMax = 4;
		struct _tag_Vertex
		{
			Vec3		vec; 	// 頂点座標
			float		rhw;	// 同時座標
			unsigned	color;	// 頂点カラー
			Vec3		uv;		// UV
			enum { FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 };
		} m_Vertex[mc_VertexMax];

		Vec3 m_VertexPos[mc_VertexMax];
		Vec3 m_VertexOffset[mc_VertexMax];
    };

} // namespace DirectX

#endif // __SPRITE_IMP_H__
