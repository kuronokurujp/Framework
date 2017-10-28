/**
 *	@file 	D:/work/dungeon/framework/directx/Manager.cpp
 *	@brief	
 *	@author	yuto uchida
 *	@data   2010-11-29
 *	@note 
 *
 */
#include "directx/Manager.h"
#include "directx/input/KeyManagerImpl.h"			// キーボード入力
#include "directx/input/JoyStatcManagerImpl.h"	// ジョイステック入力

#include "common/Common.h"

// ライブラリのリンク
#pragma once
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")

KeyInput::KeyManagerImpl*		gp_key_impl	= NULL;
JoyInput::JoystatcManagerImpl*	gp_pad_impl = NULL;


namespace DirectX {

	Manager* Manager::msp_inst = NULL;

	void Manager::Create(
		HINSTANCE ih_inst, HWND ih_wnd, 
		unsigned i_w, unsigned i_h, bool ib_full_screen )
	{
		if( msp_inst == NULL )
		{
			msp_inst = new Manager( ih_inst, ih_wnd, i_w, i_h, ib_full_screen );
		}
	}

	void Manager::Destroy()
	{
		if( msp_inst )
		{
			SAFE_DELETE(msp_inst);
		}
	}

	Manager::Manager(
		HINSTANCE ih_inst, HWND ih_wnd, unsigned i_w, unsigned i_h, bool ib_full_screen )	:
	mp_d3d(NULL),
	mp_d3d_device(NULL),
	mp_font(NULL),
	m_rgb(0xff282850)
	{
		// DirectXのデバイス作成
		mp_d3d = Direct3DCreate9( D3D_SDK_VERSION );
		ASSERT( mp_d3d );

		//現在のディスプレイモードを得る
	    D3DDISPLAYMODE dmode;
		//DEFAULT指定でプライマリアダプタを選択
		if( FAILED( IDirect3D9_GetAdapterDisplayMode( mp_d3d, D3DADAPTER_DEFAULT, &dmode ) ) )
		{
			ASSERT( 0 );
		}

		// スクリーン設定
		D3DPRESENT_PARAMETERS d3dpp;
		::memset(&d3dpp, 0, sizeof(D3DPRESENT_PARAMETERS));

		d3dpp.BackBufferCount = 1;
		d3dpp.BackBufferFormat = dmode.Format;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		d3dpp.Windowed = !ib_full_screen;
		d3dpp.BackBufferWidth = i_w;
		d3dpp.BackBufferHeight = i_h;
		d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

		if( d3dpp.Windowed == false )
		{
			// フルスクリーン時にはFPSの設定ができる
			d3dpp.FullScreen_RefreshRateInHz = 60;
			d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		}
		else
		{
			d3dpp.FullScreen_RefreshRateInHz = 0;
		}

		struct _tag_CreateDeviceData
		{
			D3DDEVTYPE	device_type;
			DWORD		behavior_flags;
			char*		message;
		};

		// DirectXデバイスを作成する方法が複数あったのでそれをテーブル化した。
		const struct _tag_CreateDeviceData	set_table[] = {
			{ D3DDEVTYPE_HAL,	D3DCREATE_HARDWARE_VERTEXPROCESSING,
			"描画/頂点の処理をHardware処理"},
			{ D3DDEVTYPE_HAL,	D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			"描画をHardware処理/頂点をCPU処理"},
			{ D3DDEVTYPE_REF,	D3DCREATE_HARDWARE_VERTEXPROCESSING,
			"描画/頂点をCPU処理"},
		};

		// テーブルで用意した分でデバイスを作成できるか試す。
		// テーブルで用意した設定でデバイス作成ができなければハングさせます。
		const unsigned set_table_max = sizeof(set_table) /sizeof(set_table[0]);
		for( unsigned i=0; i<set_table_max; ++i )
		{
			if( FAILED( mp_d3d->CreateDevice(	D3DADAPTER_DEFAULT,
												set_table[i].device_type,
												ih_wnd,
												set_table[i].behavior_flags,
												&d3dpp,
												&mp_d3d_device ) ) == false ) {
				// デバイス作成成功
				cprintf( "%s(%d) : %s\n", __FILE__, __LINE__, set_table[i].message );
				break;
			}
		}
		ASSERT( mp_d3d_device );

		// 文字列レンダリング初期化
		if( FAILED( D3DXCreateFont( mp_d3d_device, 0, 8,
			FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "tahoma", &mp_font ) ) )
		{
			STRING_ASSERT( false, "Error\n" );
		}

		// keyinput作成
		gp_key_impl = new KeyInput::KeyManagerImpl();
		gp_pad_impl = new JoyInput::JoystatcManagerImpl( ih_inst, ih_wnd );
	}

	Manager::~Manager()
	{
		SAFE_RELEASE(mp_font);
		SAFE_RELEASE(mp_d3d_device);
		SAFE_RELEASE(mp_d3d);

		SAFE_DELETE(gp_key_impl);
		SAFE_DELETE(gp_pad_impl);
	}

	/*
		@brief	3DZTestを指定
	*/
	void	Manager::EnableZTest( const bool in_Flg )
	{
		HRESULT hr = 0;

		//Zテスト
		hr	= mp_d3d_device->SetRenderState( D3DRS_ZENABLE, in_Flg );
		ASSERT( SUCCEEDED( hr ) );
		hr = mp_d3d_device->SetRenderState( D3DRS_ZWRITEENABLE, in_Flg );
		ASSERT( SUCCEEDED( hr ) );
	}

	/*
		@brief	アンビエント設定
	*/
	void	Manager::SetAmbientColor( const unsigned in_Color )
	{
		mp_d3d_device->SetRenderState( D3DRS_AMBIENT, in_Color );
	}

	/*
		@brief	カリング設定
	*/
	void	Manager::SetCullMode( eCullMode in_Mode )
	{
		HRESULT hr = 0;
		hr	= mp_d3d_device->SetRenderState( D3DRS_CULLMODE, in_Mode );
		ASSERT( SUCCEEDED( hr ) );
	}

	/*
		@brief	キー入力
		@param	i_key	:	指定したキーを押したかチェック
	*/
	bool Manager::IsKeyOn(unsigned char i_key)
	{
		return gp_key_impl->IsKeyOn(i_key);
	}

	bool Manager::IsKeyTriggerOn(unsigned char i_key)
	{
		return gp_key_impl->IsKeyTriggerOn(i_key);
	}

	bool Manager::IsKeyRepertOn(unsigned char i_key)
	{
		return gp_key_impl->IsKeyRepertOn(i_key);
	}

	/*
		@brief	パッド入力
		@param	i_pad	:	指定したボタンを押したかチェック
	*/
	bool Manager::IsPadOn( Input::ePadKey i_pad )
	{
		return gp_pad_impl->IsPad( i_pad );
	}

	bool Manager::IsPadTriggerOn( Input::ePadKey i_pad )
	{
		return gp_pad_impl->IsPadTrigger( i_pad );
	}

	bool Manager::IsPadRepertOn( Input::ePadKey i_pad )
	{
		return gp_pad_impl->IsPadRepert( i_pad );
	}

	/*
		@breif	デバッグテキスト描画
		@param	ip_str	:	テキスト
		@param	i_x		:	x座標
		@param	i_y		:	y座標
		@param	i_color	:	カラー設定
	*/
	void Manager::DrawDebugText( const _TCHAR* ip_str, int i_x, int i_y, const int i_color )
	{
		RECT	rect = { i_x, i_y, 0, 0 };
		mp_font->DrawText( NULL, ip_str, -1, &rect, DT_CALCRECT, NULL );
		mp_font->DrawText( NULL, ip_str, -1, &rect, DT_LEFT | DT_BOTTOM, i_color );
	}

	/*
		@brief	入力更新
		@note	入力結果を反映
	*/
	void Manager::InputUpdate()
	{
		gp_key_impl->Update();
		gp_pad_impl->Update();
	}

	/*
		@brief	音声更新
		@note	Sound結果を反映
	*/
	void Manager::SoundUpdate()
	{
	}

	/*
		@brief	描画準備処理
	*/
	void Manager::DrawPreUpdate()
	{
		HRESULT hr;
	    hr = mp_d3d_device->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, m_rgb, 1.0f, 0 );
    	ASSERT( hr != D3DERR_INVALIDCALL );

	    hr = mp_d3d_device->BeginScene();
    	ASSERT( SUCCEEDED(hr) );
	}

	/*
		@brief	描画終了処理
	*/
	void Manager::DrawPostUpdate()
	{
	    HRESULT hr = mp_d3d_device->EndScene();
    	ASSERT( SUCCEEDED(hr));
	    if( FAILED( mp_d3d_device->Present( NULL, NULL, NULL, NULL ) ) )
		{
			if ( hr == D3DERR_DEVICELOST )
			{
		    	// デバイス消失
			    hr = D3D_OK;
			}
		}
	}

	/*
		@brief	マテリアルデータ取得
		@param	rgb カラー値設定
		@return	マテリアルデータを返す
	*/
	D3DMATERIAL9 CreateMaterialData( float r, float g, float b )
	{
		D3DMATERIAL9	material;
		memset( &material, 0, sizeof( D3DMATERIAL9 ) );

		material.Diffuse.r = r;
		material.Diffuse.g = g;
		material.Diffuse.b = b;
		material.Ambient.r = r;
		material.Ambient.g = g;
		material.Ambient.b = b;
		material.Specular.r = 1.0f;
		material.Specular.g = 1.0f;
		material.Specular.b = 1.0f;
		material.Emissive.r = 0;
		material.Emissive.g = 0;
		material.Emissive.b = 0;
		material.Power = 10;

		return	material;
	}

} // namespace DirectX
