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
    // �X�v���C�g�P�̃N���X
    class SpriteImpl
	{
	public:
        // �X�v���C�g�쐬
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

        // �e�N�X�`���[�ݒ�
        void SetTex( IDirect3DTexture9 **const ppTex, unsigned int w, unsigned int h )
		{
            ASSERT(ppTex);
            SetImgRect( 0, 0, w, h );

            // ���_�X�V
            _CalcVertexPos(m_Angle, m_Scale);
            _CalcVertexTexUv(m_ImgRect, w, h);

            mpp_Tex = ppTex;
            m_W = w;
            m_H = h;
        }

        // �摜�͈͐ݒ�
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

            // �S���_�̃I�t�Z�b�g�x�N�g���擾
            {
                float fw = static_cast<float>((x2 - x) >> 1);
                float fh = static_cast<float>((y2 - y) >> 1);
                // �E��
				m_VertexOffset[0].Set( fw, -fh, 0.0f );
                // �E��
                m_VertexOffset[1].Set( fw, fh, 0.0f);
                // ����
                m_VertexOffset[2].Set( -fw, -fh, 0.0f);
                // ����
                m_VertexOffset[3].Set( -fw, fh, 0.0f);
            }

			// ���_�ʒu���Đݒ�
            _CalcVertexPos(m_Angle, m_Scale);
			// �e�N�X�`���͈͎w�肪�ύX����邩��
            _CalcVertexTexUv(m_ImgRect, m_W, m_H);
        }

        RECT_DATA_ST &GetImgRect() { return m_ImgRect; }

        // ���W�ݒ�
		void SetPos( const float x, const float y ) { m_Vec.x = x; m_Vec.y = y; }
		void SetPos( const Vec3 &vec ) { SetPos( vec.x, vec.y ); }

        const unsigned GetAddRGB() const { return m_Color; }
        void SetAddRGB(unsigned rgb)
		{
			m_Color = rgb;
            _CalcVertexColor(m_Color);
        }

        // �X�v���C�g��]
        void Rota(float sita)
		{
            if( sita != m_Angle )
			{
                _CalcVertexPos(sita, m_Scale);
                m_Angle = sita;
            }
        }

        // �X�v���C�g�g��k��
        void Scale(float s)
		{
            if( s != m_Scale )
			{
                s = LOWER(s, 0.0f);
                _CalcVertexPos(m_Angle, s);
                m_Scale = s;
            }
        }

        // �`��
        void Draw()
		{
            if( mb_Visible == true )
			{
                ASSERT(mpp_Tex);

                // �`�悷��l�_�̒��_���쐬
                // 2D����3D�̃x�N�g���ύX
                // ���_��3�������W������
				Vec3 vec;
				vec.Set( m_Vec.x, m_Vec.y, 0.0f);
                for( unsigned int i = 0; i < mc_VertexMax; ++i )
				{
					m_Vertex[i].vec		= ( m_VertexPos[i] + vec );
                    m_Vertex[i].vec.z	= 1.0f;
                }

				LPDIRECT3DDEVICE9 p = Manager::Inst().GetDevice();
                ASSERT(p);

                // �e�N�X�`���[�ݒ�
                p->SetTexture(0, *mpp_Tex);
                // ��ԏ��
                p->SetFVF(_tag_Vertex::FVF);
                // �`��
                p->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_Vertex, sizeof(struct _tag_Vertex));
            }
        }

        // ���W�擾
		Vec3&	GetPos() { return m_Vec; }
        // �`��ON/OFF
        void	SetVisible( bool bFlg ) { mb_Visible = bFlg; }

	private:
		// ���_�J���ݒ�
		void _CalcVertexColor(unsigned int color)
		{
			for( unsigned int i = 0; i<mc_VertexMax; ++i )
			{
				m_Vertex[i].color = color;
			}
		}

		// ���_�f�[�^���W�v�Z
		// ��]/�g�k�̕ύX���s�����ɒ��_�ʒu��ύX����
		void _CalcVertexPos(float rota, float scale )
		{
			// ��]�E�X�P�[�����O�s��쐬
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

		// �e���_�ɓ\��t����e�N�X�`���[UV�v�Z
		void _CalcVertexTexUv( RECT_DATA_ST &rect, unsigned int w, unsigned int h)
		{
			Vec3 uv[mc_VertexMax];
			// rect�̓X�N���[�����W�n�Œ�`
			// �e�N�X�`���[��UV���W�쐬
			{
				// �E��
				uv[0].x = static_cast<float>(rect.right);
				uv[0].y = static_cast<float>(rect.top);
				// �E��
				uv[1].x = uv[0].x;
				uv[1].y = static_cast<float>(rect.bottom);
				// ����
				uv[2].x = static_cast<float>(rect.left);
				uv[2].y = uv[0].y;
				// ����
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

		//	�ϐ�
		RECT_DATA_ST	m_ImgRect;
		Vec3			m_Vec;
		IDirect3DTexture9 **mpp_Tex;

		bool mb_Visible;
		unsigned int m_W, m_H;
		unsigned int m_Color;
		float m_Scale, m_Angle;

		// �v���~�e�B�u���_
		static const unsigned int mc_VertexMax = 4;
		struct _tag_Vertex
		{
			Vec3		vec; 	// ���_���W
			float		rhw;	// �������W
			unsigned	color;	// ���_�J���[
			Vec3		uv;		// UV
			enum { FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 };
		} m_Vertex[mc_VertexMax];

		Vec3 m_VertexPos[mc_VertexMax];
		Vec3 m_VertexOffset[mc_VertexMax];
    };

} // namespace DirectX

#endif // __SPRITE_IMP_H__
