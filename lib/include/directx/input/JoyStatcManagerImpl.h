/**
 *	@file 	D:/ProgramStady/Game/framework/source/directx/input/JoyStatcManagerImpl.h
 *	@brief	ジョイステック制御
 *	@author	yuto uchida
 *	@data   2011-02-12
 *	@note 	途中からゲームパッドを挿すと反応しない！
 *
 */
#ifndef __JOYSTATCMANAGERIMPL_H__
#define __JOYSTATCMANAGERIMPL_H__

#include <dinput.h>

// ライブラリのリンク
#pragma once
#pragma comment(lib,"dinput8.lib")

#include "directx/input/KeyTable.h"
#include "directx/manager.h"

#include "common/Common.h"

namespace JoyInput
{
	class JoystatcManagerImpl
	{
	private:
		// ジョイステックの入力結果
		struct _tag_State
		{
			unsigned char data[Input::PAD_KEY_MAX];
		};

	public:
		/*
			@brief	コンストラクト
			@param	i_inst	:	アプリのインスタンスハンドル
			@param	i_wnd	:	ウィンドウのハンドル
		*/
		JoystatcManagerImpl( HINSTANCE i_inst, HWND i_wnd )	:
		mp_obj( NULL ),
		mp_device( NULL ),
		m_wnd( i_wnd )
		{
			::memset( &m_state, 0, ARRAY_SIZE( m_state ) );
			::memset( &m_input, 0, ARRAY_SIZE( m_input ) );
			::memset( &m_repert_cnt, 0, ARRAY_SIZE( m_repert_cnt ) );

			{
				HRESULT	hres = 0;
				if( mp_obj == NULL )
				{
					//DirectInputのオブジェクトを作成する
					hres = DirectInput8Create(	i_inst, DIRECTINPUT_VERSION,
												IID_IDirectInput8,
												(VOID**)&mp_obj, NULL);
				}

				if( FAILED(hres) )
				{
					// オブジェクト作成に失敗
					STRING_ASSERT( false, "Error DirectInput8Create" );
				}
			}

			// ゲームパッドが接続されて時に呼ばれる
			{
				mp_obj->EnumDevices(	
									DI8DEVCLASS_GAMECTRL,
									&EnumJoyCallback,
									this,
									DIEDFL_ATTACHEDONLY );
			}
		}

		~JoystatcManagerImpl()
		{
			if( mp_device != NULL )
			{
				mp_device->Unacquire();
			}

			SAFE_RELEASE( mp_device );
			SAFE_RELEASE( mp_obj );
		}

		/*
			@brief	入力取得
		*/
		const bool	IsPad( Input::ePadKey i_pad )
		{
			return ( m_input[ PAD_TYPE_NORMAL ].data[ i_pad ] == 1);
		}

		const bool	IsPadTrigger( Input::ePadKey i_pad )
		{
			return ( m_input[ PAD_TYPE_TRIGGER ].data[ i_pad ] == 1 );
		}

		const bool	IsPadRepert( Input::ePadKey i_pad )
		{
			if( m_input[ PAD_TYPE_NORMAL ].data[ i_pad ] == 1 )
			{
				++m_repert_cnt[ i_pad ];
				if( m_repert_cnt[ i_pad ] > eREPERT_OK_CNT ) { return	true; }
			}
			else
			{
				m_repert_cnt[ i_pad ]	= 0;
			}

			return	false;
		}

		/*
			@brief	更新
		*/
		void Update()
		{
			// 1フレーム前のデータを保存
			m_state[ eINPUT_DATA_TYPE_OLD ] = m_state[ eINPUT_DATA_TYPE_NEW ];
			// データクリア
			::memset( &m_state[ eINPUT_DATA_TYPE_NEW ], 0, sizeof( m_state[ eINPUT_DATA_TYPE_NEW ] ) );
			::memset( m_input, 0, sizeof( m_input ) / sizeof( m_input[ 0 ] ) * sizeof( m_input[ 0 ] ) );
			if( mp_device == NULL )
			{
				return;
			}

			bool b_input = true;
			// デバイス状態取得
			HRESULT	res = mp_device->Poll();
			// 取得したデバイスがない！
			if( FAILED(res) )
			{
				// デバイスを探す
				res = mp_device->Acquire();
				bool					bflag = false;
				unsigned				chk_cnt = 0;
				const		unsigned	chk_max = 30;
				// 60回はチェックする。
				// それ以上はやらない
				while( ( bflag == true ) && ( res == DIERR_INPUTLOST ) && ( chk_cnt <= chk_max ))
				{
					res = mp_device->Acquire();
					++chk_cnt;
				}

				// デバイスがあった！！
				if( chk_cnt >= chk_max )
				{
					b_input = false;
				}
			}

			if( b_input == true ) 
			{
				// ジョイステック取得
				GetargStatc( &m_state[ eINPUT_DATA_TYPE_NEW ], mp_device );
				::memcpy( &m_input[ PAD_TYPE_NORMAL ], &m_state[ eINPUT_DATA_TYPE_NEW ], sizeof( m_state[ 0 ] ) );
				// 古いキーを合わせて連続で入力している箇所があるかチェック
				for( unsigned i = 0; i < Input::PAD_KEY_MAX; ++i )
				{
					m_input[ PAD_TYPE_TRIGGER ].data[ i ] = static_cast<unsigned char>( m_state[ eINPUT_DATA_TYPE_NEW ].data != m_state[ eINPUT_DATA_TYPE_OLD ].data );
				}
			}
		}

	private:
		/*
			@brief	ジョイステック
			@param	op_state	:	ジョイステックの状態
			@param	ip_device	:	ジョイステックのデバイス
		*/
		void	GetargStatc( struct _tag_State* op_state, LPDIRECTINPUTDEVICE8 ip_device )
		{
			if( ( op_state == NULL ) || ( ip_device == NULL ) ) { return; }

			DIJOYSTATE	dijs;
			HRESULT res = ip_device->GetDeviceState( sizeof(DIJOYSTATE), &dijs );
			if( SUCCEEDED( res ) )
			{
				if( dijs.lX > +1000 / 2 )
				{
					//右キーが押されている
					op_state->data[ Input::PAD_KEY_RIGHT ] = 1;
				}
				else if( dijs.lX < -1000 / 2 )
				{
					//左キーが押されている
					op_state->data[ Input::PAD_KEY_LEFT ] = 1;
				}

				if( dijs.lY > +1000 / 2 )
				{
					//下キーが押されている
					op_state->data[ Input::PAD_KEY_DOWN ] = 1;
				}
				else if( dijs.lY < -1000 / 2 )
				{
					//上キーが押されている
					op_state->data[ Input::PAD_KEY_UP ] = 1;
				}

				{
					for( unsigned i = 0; i < Input::PAD_KEY_BTN_MAX - Input::PAD_KEY_BTN; ++i )
					{
						if(dijs.rgbButtons[ i ] & 0x80)
						{
							op_state->data[ Input::PAD_KEY_BTN + i ] = 1;
						}
					}
				}
			}
		}

		/*
			@brief	デバイス接続時に呼び出される
			@param	ip_inst		:	デバイスインスタンス構造体のポインタ
			@param	ip_context	:	コールバック登録時に設定したデータポインタ
		*/
		static BOOL CALLBACK EnumJoyCallback(const DIDEVICEINSTANCE* ip_inst, void* ip_context )
		{
			JoystatcManagerImpl* data = reinterpret_cast<JoystatcManagerImpl*>( ip_context );
			if( data == NULL )
			{
				FILE_LINE_PRINT( "クラスポインタがない" );
				return DIENUM_CONTINUE;
			}

			if( data->mp_obj == NULL )
			{
				FILE_LINE_PRINT( "DirectInputのObjがない" );
				return DIENUM_CONTINUE;
			}

			if( ip_inst == NULL)
			{
				FILE_LINE_PRINT( "デバイスインスタンスがない" );
				return DIENUM_CONTINUE;
			}

			// デバイスDataを表示
			printf( "%s : %s\n", ip_inst->tszInstanceName, ip_inst->tszProductName );
			//接続されたジョイスティックへのインタフェースを取得する
			{
				HRESULT	hr = data->mp_obj->CreateDevice( ip_inst->guidInstance, &data->mp_device, NULL );
				if( FAILED( hr ) )
				{
					FILE_LINE_PRINT( "Error IDirectInput8_CreateDeivce" );
					return DIENUM_CONTINUE;
				}
			}

			// デバイスデータを取得
			{
				::memset( &data->m_didevcaps, 0, sizeof( data->m_didevcaps ) );
				data->m_didevcaps.dwSize = sizeof( data->m_didevcaps );
				HRESULT	hr = IDirectInputDevice8_GetCapabilities( data->mp_device, &data->m_didevcaps );
				if(FAILED(hr))
				{
					FILE_LINE_PRINT( "Error GetCapablities" );
					data->mp_device = NULL;
					return DIENUM_CONTINUE;
				}	
			}

			// デバイスフォーマットの設定
			{
				HRESULT	hr = data->mp_device->SetDataFormat( &c_dfDIJoystick );
				if( FAILED( hr ) )
				{
					FILE_LINE_PRINT( "Error: SetDataFormat ");
					return DIENUM_CONTINUE;
				}
			}

			// デバイスの協調レベルの設定(ジョイスティック)
			{
				HRESULT hr = data->mp_device->SetCooperativeLevel( 	data->m_wnd,  DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY );
				if( FAILED( hr ) )
				{
					FILE_LINE_PRINT( "Error SetCooperativeLevel ");
					return DIENUM_CONTINUE;	
				}
			}

			// デバイスのプロパティ設定
			{
				DIPROPDWORD diprop;
				::memset( &diprop, 0, sizeof( DIPROPDWORD ) );
				diprop.diph.dwSize = sizeof(DIPROPDWORD);
				diprop.diph.dwHeaderSize = sizeof(diprop.diph);
				diprop.diph.dwObj = 0;
				diprop.diph.dwHow = DIPH_DEVICE;
				diprop.dwData = DIPROPAXISMODE_ABS;

				HRESULT hr = data->mp_device->SetProperty( DIPROP_AXISMODE, &diprop.diph );
				if( FAILED( hr ) )
				{
					FILE_LINE_PRINT( "Error : SetProperty" );
					return DIENUM_CONTINUE;	
				}
			}
		
			// 使用可能なデバイス入出力登録
			{
				HRESULT hr = data->mp_device->EnumObjects( JoystatcManagerImpl::EnumAxesCallback, data, DIDFT_AXIS );
				if( FAILED( hr ) )
				{
					FILE_LINE_PRINT( "Error : EnumObjects" );
					return DIENUM_CONTINUE;	
				}
			}

			return DIENUM_STOP;
		}

		static BOOL CALLBACK EnumAxesCallback( LPCDIDEVICEOBJECTINSTANCE ip_ddoi, LPVOID ip_ref )
		{
			if( ip_ddoi == NULL )
			{
				FILE_LINE_PRINT( "Error ip_ddoi == NULL\n" );
				return DIENUM_STOP;
			}

			JoystatcManagerImpl* data = reinterpret_cast<JoystatcManagerImpl*>( ip_ref );
			if( ( data == NULL ) && ( data->mp_device == NULL ) )
			{
				FILE_LINE_PRINT( "Error ip_ref == NULL\n" );
				return DIENUM_STOP;
			}

			DIPROPRANGE diprg;
			::memset( &diprg, 0, sizeof(diprg) );
			diprg.diph.dwSize = sizeof( DIPROPRANGE );
			diprg.diph.dwHeaderSize = sizeof(diprg.diph);
			diprg.diph.dwObj = ip_ddoi->dwType;
			diprg.diph.dwHow = DIPH_BYID;
			diprg.lMin =-1000;
			diprg.lMax =+1000;

			HRESULT hr = data->mp_device->SetProperty( DIPROP_RANGE, &diprg.diph );
			if( FAILED( hr ) )
			{
				FILE_LINE_PRINT( "Error SetProperty\n" );
				return DIENUM_STOP;	
			}

			return DIENUM_CONTINUE;
		}

		//	変数
		LPDIRECTINPUT8			mp_obj;
		LPDIRECTINPUTDEVICE8	mp_device;
		DIDEVCAPS				m_didevcaps;

		enum
		{
			PAD_TYPE_NORMAL,
			PAD_TYPE_TRIGGER,
			PAD_TYPE_MAX,
		};

		enum
		{
			eINPUT_DATA_TYPE_NEW = 0,
			eINPUT_DATA_TYPE_OLD,
			eINPUT_DATA_TYPE_MAX
		};

		enum
		{
			eREPERT_OK_CNT	= 30,
		};

		// ジョイステックの入力結果
		struct _tag_State	m_state[ eINPUT_DATA_TYPE_MAX ];

		unsigned char m_repert_cnt[Input::PAD_KEY_MAX];

		struct _tag_State	m_input[ PAD_TYPE_MAX ];
		HWND				m_wnd;
	};

} // JoyInput

#endif // __JOYSTATCMANAGERIMPL_H__
