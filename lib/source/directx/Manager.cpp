/**
 *	@file 	D:/work/dungeon/framework/directx/Manager.cpp
 *	@brief	
 *	@author	yuto uchida
 *	@data   2010-11-29
 *	@note 
 *
 */
#include "directx/Manager.h"
#include "directx/input/KeyManagerImpl.h"			// �L�[�{�[�h����
#include "directx/input/JoyStatcManagerImpl.h"	// �W���C�X�e�b�N����

#include "common/Common.h"

// ���C�u�����̃����N
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
		// DirectX�̃f�o�C�X�쐬
		mp_d3d = Direct3DCreate9( D3D_SDK_VERSION );
		ASSERT( mp_d3d );

		//���݂̃f�B�X�v���C���[�h�𓾂�
	    D3DDISPLAYMODE dmode;
		//DEFAULT�w��Ńv���C�}���A�_�v�^��I��
		if( FAILED( IDirect3D9_GetAdapterDisplayMode( mp_d3d, D3DADAPTER_DEFAULT, &dmode ) ) )
		{
			ASSERT( 0 );
		}

		// �X�N���[���ݒ�
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
			// �t���X�N���[�����ɂ�FPS�̐ݒ肪�ł���
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

		// DirectX�f�o�C�X���쐬������@�������������̂ł�����e�[�u���������B
		const struct _tag_CreateDeviceData	set_table[] = {
			{ D3DDEVTYPE_HAL,	D3DCREATE_HARDWARE_VERTEXPROCESSING,
			"�`��/���_�̏�����Hardware����"},
			{ D3DDEVTYPE_HAL,	D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			"�`���Hardware����/���_��CPU����"},
			{ D3DDEVTYPE_REF,	D3DCREATE_HARDWARE_VERTEXPROCESSING,
			"�`��/���_��CPU����"},
		};

		// �e�[�u���ŗp�ӂ������Ńf�o�C�X���쐬�ł��邩�����B
		// �e�[�u���ŗp�ӂ����ݒ�Ńf�o�C�X�쐬���ł��Ȃ���΃n���O�����܂��B
		const unsigned set_table_max = sizeof(set_table) /sizeof(set_table[0]);
		for( unsigned i=0; i<set_table_max; ++i )
		{
			if( FAILED( mp_d3d->CreateDevice(	D3DADAPTER_DEFAULT,
												set_table[i].device_type,
												ih_wnd,
												set_table[i].behavior_flags,
												&d3dpp,
												&mp_d3d_device ) ) == false ) {
				// �f�o�C�X�쐬����
				cprintf( "%s(%d) : %s\n", __FILE__, __LINE__, set_table[i].message );
				break;
			}
		}
		ASSERT( mp_d3d_device );

		// �����񃌃��_�����O������
		if( FAILED( D3DXCreateFont( mp_d3d_device, 0, 8,
			FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "tahoma", &mp_font ) ) )
		{
			STRING_ASSERT( false, "Error\n" );
		}

		// keyinput�쐬
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
		@brief	3DZTest���w��
	*/
	void	Manager::EnableZTest( const bool in_Flg )
	{
		HRESULT hr = 0;

		//Z�e�X�g
		hr	= mp_d3d_device->SetRenderState( D3DRS_ZENABLE, in_Flg );
		ASSERT( SUCCEEDED( hr ) );
		hr = mp_d3d_device->SetRenderState( D3DRS_ZWRITEENABLE, in_Flg );
		ASSERT( SUCCEEDED( hr ) );
	}

	/*
		@brief	�A���r�G���g�ݒ�
	*/
	void	Manager::SetAmbientColor( const unsigned in_Color )
	{
		mp_d3d_device->SetRenderState( D3DRS_AMBIENT, in_Color );
	}

	/*
		@brief	�J�����O�ݒ�
	*/
	void	Manager::SetCullMode( eCullMode in_Mode )
	{
		HRESULT hr = 0;
		hr	= mp_d3d_device->SetRenderState( D3DRS_CULLMODE, in_Mode );
		ASSERT( SUCCEEDED( hr ) );
	}

	/*
		@brief	�L�[����
		@param	i_key	:	�w�肵���L�[�����������`�F�b�N
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
		@brief	�p�b�h����
		@param	i_pad	:	�w�肵���{�^�������������`�F�b�N
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
		@breif	�f�o�b�O�e�L�X�g�`��
		@param	ip_str	:	�e�L�X�g
		@param	i_x		:	x���W
		@param	i_y		:	y���W
		@param	i_color	:	�J���[�ݒ�
	*/
	void Manager::DrawDebugText( const _TCHAR* ip_str, int i_x, int i_y, const int i_color )
	{
		RECT	rect = { i_x, i_y, 0, 0 };
		mp_font->DrawText( NULL, ip_str, -1, &rect, DT_CALCRECT, NULL );
		mp_font->DrawText( NULL, ip_str, -1, &rect, DT_LEFT | DT_BOTTOM, i_color );
	}

	/*
		@brief	���͍X�V
		@note	���͌��ʂ𔽉f
	*/
	void Manager::InputUpdate()
	{
		gp_key_impl->Update();
		gp_pad_impl->Update();
	}

	/*
		@brief	�����X�V
		@note	Sound���ʂ𔽉f
	*/
	void Manager::SoundUpdate()
	{
	}

	/*
		@brief	�`�揀������
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
		@brief	�`��I������
	*/
	void Manager::DrawPostUpdate()
	{
	    HRESULT hr = mp_d3d_device->EndScene();
    	ASSERT( SUCCEEDED(hr));
	    if( FAILED( mp_d3d_device->Present( NULL, NULL, NULL, NULL ) ) )
		{
			if ( hr == D3DERR_DEVICELOST )
			{
		    	// �f�o�C�X����
			    hr = D3D_OK;
			}
		}
	}

	/*
		@brief	�}�e���A���f�[�^�擾
		@param	rgb �J���[�l�ݒ�
		@return	�}�e���A���f�[�^��Ԃ�
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
