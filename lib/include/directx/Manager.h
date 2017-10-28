/**
 *	@file 	manager.h
 *	@brief	DirectXシステム
 *	@author	yuto uchida
 *	@data   2010-11-29
 *	@note	この管理システムをルートにしてグラフィックス・入力・音声を葉とする。
 *
 */
#ifndef __DIRECTX_MANAGER_H__
#define __DIRECTX_MANAGER_H__

#include <windows.h>
#include <d3d9.h>
#include <tchar.h>

 //@todo 下記のインクルードファイルは使う側で参照できないようにしたい
#include <d3dx9.h>

#include "directx/input/KeyTable.h"

namespace DirectX
{
	// リリース解放
	#define SAFE_RELEASE(_p_) { if( (_p_) ) { (_p_)->Release(); (_p_) = NULL; } }

	//	定義

	//	頂点情報
	struct VERTEX {
		float x, y, z;
		float nx, ny, nz;
		float u, v;

		VERTEX() {}
		VERTEX( float _x, float _y, float _z,
			float _nx, float _ny, float _nz,
			float in_u, float in_v ) :
		x(_x), y(_y), z(_z),
			nx(_nx), ny(_ny), nz(_nz),
			u( in_u ), v( in_v ) {}

		void Set(	float _x, float _y, float _z,
			float _nx, float _ny, float _nz,
			float in_u, float in_v )
		{
			x = _x;
			y = _y;
			z = _z;
			nx = _nx;
			ny = _ny;
			nz = _nz;
			u	= in_u;
			v	= in_v;
		}

		enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 } ;
	};

	struct TLVERTEX {
		float x, y, z;
		float rhw;
		DWORD color;
		float tu0, tv0;

		enum { FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 } ;
	} ;

	//	マテリアルデータ取得
	//	RGB値からマテリアルデータを作成
	D3DMATERIAL9 CreateMaterialData( float r, float g, float b );

	class Manager
	{
	public:
		//	定数
		typedef enum
		{
			eNONE	= D3DCULL_NONE,		//	カリングしない
			eCW		= D3DCULL_CW,		//	右周りでカリング
			eCCW	= D3DCULL_CCW,		//	左周りでカリング
		}eCullMode;

		/*
			@brief	インスタンス作成
			@param	スクリーンの横幅
			@param	スクリーンの縦幅
			@param	フルスクリーンかどうか
		*/
		static void Create( HINSTANCE ih_inst, HWND ih_wnd,
							unsigned i_w, unsigned i_h, bool ib_full_screen );

		/*
			@brief	インスタンス取得
		*/
		static Manager&	Inst() { return *msp_inst; }

		/*
			@brief	インスタンス破棄
		*/
		static void Destroy();

		/*
			@brief	DirectXのデバイス取得
		*/
		IDirect3DDevice9*	GetDevice() const { return mp_d3d_device; }

		/*
			@brief	Zテスト設定
			@param	: in_Flg 有効 = true / 無効 = false
		*/
		void	EnableZTest( const bool in_Flg );

		/*
			@brief	アンビエント設定
			@param	: in_Color カラー値( ARGB )
		*/
		void	SetAmbientColor( const unsigned in_Color );

		/*
			@brief	カリング設定
		*/
		void	SetCullMode( eCullMode in_Mode );

		/*
			@brief	キー入力
			@param	i_key	:	指定したキーを押したかチェック
		*/
		bool IsKeyOn(unsigned char i_key);
		bool IsKeyTriggerOn(unsigned char i_key);
		bool IsKeyRepertOn(unsigned char i_key);

		/*
			@brief	パッド入力
			@param	i_pad	:	指定したボタンを押したかチェック
		*/
		bool IsPadOn( Input::ePadKey i_pad);
		bool IsPadTriggerOn( Input::ePadKey i_pad);
		bool IsPadRepertOn( Input::ePadKey i_pad);

		//	背景色設定・取得
		void SetScreenColor( const unsigned in_rgb )	{ m_rgb = in_rgb; }
		const unsigned	GetScreenColor()	const { return m_rgb; }

		/*
			@breif	デバッグテキスト描画
			@param	ip_str	:	テキスト
			@param	i_x		:	x座標
			@param	i_y		:	y座標
			@param	i_color	:	カラー設定
		*/
		void DrawDebugText( const _TCHAR* ip_str, int i_x, int i_y, const int i_color );

		// 下記の処理はシステム側で使用するので使わない
		/*
			@brief	入力更新
			@note	入力結果を反映
		*/
		void InputUpdate();
		/*
			@brief	音声更新
			@note	Sound結果を反映
		*/
		void SoundUpdate();

		/*
			@note	DirectXの描画は準備と後始末を常に行う必要がある
					描画処理は準備と後始末の処理の間に書かないと反映されない。
		*/
		/*
			@brief	描画前更新
		*/
		void DrawPreUpdate();
		/*
			@brief	描画後更新
		*/
		void DrawPostUpdate();

	private:
		Manager( HINSTANCE ih_inst, HWND ih_wnd, unsigned i_w, unsigned i_h, bool ib_full_screen );
		~Manager();

		//	変数
		IDirect3D9*			mp_d3d;
		IDirect3DDevice9*	mp_d3d_device;

		LPD3DXFONT			mp_font;
		unsigned int		m_rgb;

		static Manager*	msp_inst;
	};
} // namespace DirectX

#endif // __DIRECTX_MANAGER_H__
