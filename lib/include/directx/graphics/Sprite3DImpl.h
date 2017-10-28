/********************************************************************
	created:	2012/05/27
	created:	27:5:2012   23:16
	file base:	Sprite3DImpl
	
	purpose:	3Dスプライト描画(本体)
*********************************************************************/
#ifndef __DIRECTX_SPRITE3DIMPL_H__
#define __DIRECTX_SPRITE3DIMPL_H__

#include "common/Common.h"
#include "directx/Manager.h"
#include "directx/graphics/TextureImpl.h"

namespace DirectX
{
	class TextureImpl;

	class Sprite3DImpl
	{
	public:
		Sprite3DImpl() { _Clear(); }
		~Sprite3DImpl()	{}

		/*
			@brief	作成
			@param	テクスチャー設定
			@return	作成成功 : true / 失敗 : false
		*/
		const bool	Create( TextureImpl* in_pTex )
		{
			mp_Tex	= in_pTex;
			return	true;
		}

		/*
			@brief	作成
			@return	作成成功 : true / 失敗 : false
		*/
		const bool	Create() { return true; }

		void	Destroy() {}

		/*
			@brief	座標取得	
		*/
		Vec3*	GetPos()			{ return &m_Pos; }

		/*
			@brief	座標設定	
		*/
		void	SetPos( const Vec3& in_Pos )
		{
			m_Pos	= in_Pos;
		}

		/*
			@brief	描画
		*/
		void	Draw(	const bool in_CamFlg,
						const float in_Yaw, const float in_Pitch, const Vec3& in_DistVec,
						const Marixt4x4& in_ViewMat, const Marixt4x4& in_ProjMat )
		{
			DirectX::Manager&	inst	= DirectX::Manager::Inst();
			IDirect3DDevice9*	pDevice	= inst.GetDevice();
			ASSERT( pDevice );

			D3DVIEWPORT9	viewPort;
			pDevice->GetViewport( &viewPort );

			//	テクスチャー貼り付け
			if( mp_Tex && mp_Tex->GetTex() )
			{
				pDevice->SetTexture( 0, *( mp_Tex->GetTex() ) );
			}
			else
			{
				pDevice->SetTexture( 0, NULL );
			}

			D3DMATERIAL9	material	= DirectX::CreateMaterialData( 1.f, 1.f, 1.f );
			pDevice->SetMaterial( &material );

			if( in_CamFlg == false )
			{
				//	頂点
				static	DirectX::VERTEX	aV[]	=
				{
					VERTEX( 0.5f, 2.0f, 0.0f, 0, 0, -1, 1, 0 ),	//	右上
					VERTEX( 0.5f, 0.0f, 0.0f, 0, 0, -1, 1, 1 ),	//	右下
					VERTEX(-0.5f, 0.0f, 0.0f, 0, 0, -1, 0, 1 ),	//	左下
					VERTEX(-0.5f, 2.0f, 0.0f, 0, 0, -1, 0, 0 ),	//	左上
				};

				//	ビルボート処理
				Marixt4x4	matView;
				pDevice->GetTransform( D3DTS_VIEW, &matView );

				//	逆行列作成
				Marixt4x4	matBillboard	= matView.GetTranspose();
				matBillboard._14	= 0.f;
				matBillboard._24	= 0.f;
				matBillboard._34	= 0.f;

				//	座標設定
				matBillboard._41	= m_Pos.x;
				matBillboard._42	= m_Pos.y;
				matBillboard._43	= m_Pos.z;

				//	描画
				pDevice->SetTransform( D3DTS_WORLD, &matBillboard );

				pDevice->SetFVF( DirectX::VERTEX::FVF );
				pDevice->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, 2, aV, sizeof( DirectX::VERTEX ) );
			}
			else
			{
				D3DXMATRIX	m, rot;
				D3DXMatrixRotationYawPitchRoll( &rot, in_Yaw, 0.f, 0.f );
				D3DXMatrixScaling( &m, 1.f, 1.f / (float)cos( in_Pitch ), 1.f );
				D3DXMatrixMultiply( &rot, &m, &rot );

				float	vx	= 0.25f * in_DistVec.x / in_DistVec.y;
				float	vz	= 0.25f * in_DistVec.z / in_DistVec.y;
				float	vy	= 0.f;

				//	座標設定
				D3DXMatrixTranslation( &m, vx + m_Pos.x, vy + m_Pos.y, vz + m_Pos.z );
				D3DXMatrixMultiply( &m, &rot, &m );

				Vec3	v1( 0.5f, 0.f, 0.f );
				Vec3	v2( -0.5f, 0.f, 0.f );
				Vec3	v3( 0.f, 2.f, 0.f );

				D3DXVec3Project( &v1, &v1, &viewPort, &in_ProjMat, &in_ViewMat, &m );
				D3DXVec3Project( &v2, &v2, &viewPort, &in_ProjMat, &in_ViewMat, &m );
				D3DXVec3Project( &v3, &v3, &viewPort, &in_ProjMat, &in_ViewMat, &m );

				v3.y	= v1.y + ( v1.y - v3.y );

				DirectX::TLVERTEX	aV[]	=
				{
					{ v1.x, v3.y, v1.z, 1, 0xffffffff, 1, 0 },	// 右上
					{ v1.x, v1.y, v2.z, 1, 0xffffffff, 1, 1 },	// 右下
					{ v2.x, v3.y, v1.z, 1, 0xffffffff, 0, 0 },	// 左上
					{ v2.x, v2.y, v2.z, 1, 0xffffffff, 0, 1 },	// 左下
				};

				pDevice->SetFVF( DirectX::TLVERTEX::FVF );
				pDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, aV, sizeof( DirectX::TLVERTEX ) );
			}
		}

	private:
		//	関数
		void	_Clear()
		{
			m_Pos.Set( 0.f, 0.f, 0.f );
			mp_Tex	= NULL;
		}

		//	変数
		Vec3	m_Pos;

		TextureImpl*	mp_Tex;
	};
}

#endif // __DIRECTX_SPRITE3DIMPL_H__
