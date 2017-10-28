/**
 *	@file 	D:/ProgramStady/Game/framework/source/directx/input/JoyStatcManagerImpl.h
 *	@brief	�W���C�X�e�b�N����
 *	@author	yuto uchida
 *	@data   2011-02-12
 *	@note 	�r������Q�[���p�b�h��}���Ɣ������Ȃ��I
 *
 */
#ifndef __JOYSTATCMANAGERIMPL_H__
#define __JOYSTATCMANAGERIMPL_H__

#include <dinput.h>

// ���C�u�����̃����N
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
		// �W���C�X�e�b�N�̓��͌���
		struct _tag_State
		{
			unsigned char data[Input::PAD_KEY_MAX];
		};

	public:
		/*
			@brief	�R���X�g���N�g
			@param	i_inst	:	�A�v���̃C���X�^���X�n���h��
			@param	i_wnd	:	�E�B���h�E�̃n���h��
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
					//DirectInput�̃I�u�W�F�N�g���쐬����
					hres = DirectInput8Create(	i_inst, DIRECTINPUT_VERSION,
												IID_IDirectInput8,
												(VOID**)&mp_obj, NULL);
				}

				if( FAILED(hres) )
				{
					// �I�u�W�F�N�g�쐬�Ɏ��s
					STRING_ASSERT( false, "Error DirectInput8Create" );
				}
			}

			// �Q�[���p�b�h���ڑ�����Ď��ɌĂ΂��
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
			@brief	���͎擾
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
			@brief	�X�V
		*/
		void Update()
		{
			// 1�t���[���O�̃f�[�^��ۑ�
			m_state[ eINPUT_DATA_TYPE_OLD ] = m_state[ eINPUT_DATA_TYPE_NEW ];
			// �f�[�^�N���A
			::memset( &m_state[ eINPUT_DATA_TYPE_NEW ], 0, sizeof( m_state[ eINPUT_DATA_TYPE_NEW ] ) );
			::memset( m_input, 0, sizeof( m_input ) / sizeof( m_input[ 0 ] ) * sizeof( m_input[ 0 ] ) );
			if( mp_device == NULL )
			{
				return;
			}

			bool b_input = true;
			// �f�o�C�X��Ԏ擾
			HRESULT	res = mp_device->Poll();
			// �擾�����f�o�C�X���Ȃ��I
			if( FAILED(res) )
			{
				// �f�o�C�X��T��
				res = mp_device->Acquire();
				bool					bflag = false;
				unsigned				chk_cnt = 0;
				const		unsigned	chk_max = 30;
				// 60��̓`�F�b�N����B
				// ����ȏ�͂��Ȃ�
				while( ( bflag == true ) && ( res == DIERR_INPUTLOST ) && ( chk_cnt <= chk_max ))
				{
					res = mp_device->Acquire();
					++chk_cnt;
				}

				// �f�o�C�X���������I�I
				if( chk_cnt >= chk_max )
				{
					b_input = false;
				}
			}

			if( b_input == true ) 
			{
				// �W���C�X�e�b�N�擾
				GetargStatc( &m_state[ eINPUT_DATA_TYPE_NEW ], mp_device );
				::memcpy( &m_input[ PAD_TYPE_NORMAL ], &m_state[ eINPUT_DATA_TYPE_NEW ], sizeof( m_state[ 0 ] ) );
				// �Â��L�[�����킹�ĘA���œ��͂��Ă���ӏ������邩�`�F�b�N
				for( unsigned i = 0; i < Input::PAD_KEY_MAX; ++i )
				{
					m_input[ PAD_TYPE_TRIGGER ].data[ i ] = static_cast<unsigned char>( m_state[ eINPUT_DATA_TYPE_NEW ].data != m_state[ eINPUT_DATA_TYPE_OLD ].data );
				}
			}
		}

	private:
		/*
			@brief	�W���C�X�e�b�N
			@param	op_state	:	�W���C�X�e�b�N�̏��
			@param	ip_device	:	�W���C�X�e�b�N�̃f�o�C�X
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
					//�E�L�[��������Ă���
					op_state->data[ Input::PAD_KEY_RIGHT ] = 1;
				}
				else if( dijs.lX < -1000 / 2 )
				{
					//���L�[��������Ă���
					op_state->data[ Input::PAD_KEY_LEFT ] = 1;
				}

				if( dijs.lY > +1000 / 2 )
				{
					//���L�[��������Ă���
					op_state->data[ Input::PAD_KEY_DOWN ] = 1;
				}
				else if( dijs.lY < -1000 / 2 )
				{
					//��L�[��������Ă���
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
			@brief	�f�o�C�X�ڑ����ɌĂяo�����
			@param	ip_inst		:	�f�o�C�X�C���X�^���X�\���̂̃|�C���^
			@param	ip_context	:	�R�[���o�b�N�o�^���ɐݒ肵���f�[�^�|�C���^
		*/
		static BOOL CALLBACK EnumJoyCallback(const DIDEVICEINSTANCE* ip_inst, void* ip_context )
		{
			JoystatcManagerImpl* data = reinterpret_cast<JoystatcManagerImpl*>( ip_context );
			if( data == NULL )
			{
				FILE_LINE_PRINT( "�N���X�|�C���^���Ȃ�" );
				return DIENUM_CONTINUE;
			}

			if( data->mp_obj == NULL )
			{
				FILE_LINE_PRINT( "DirectInput��Obj���Ȃ�" );
				return DIENUM_CONTINUE;
			}

			if( ip_inst == NULL)
			{
				FILE_LINE_PRINT( "�f�o�C�X�C���X�^���X���Ȃ�" );
				return DIENUM_CONTINUE;
			}

			// �f�o�C�XData��\��
			printf( "%s : %s\n", ip_inst->tszInstanceName, ip_inst->tszProductName );
			//�ڑ����ꂽ�W���C�X�e�B�b�N�ւ̃C���^�t�F�[�X���擾����
			{
				HRESULT	hr = data->mp_obj->CreateDevice( ip_inst->guidInstance, &data->mp_device, NULL );
				if( FAILED( hr ) )
				{
					FILE_LINE_PRINT( "Error IDirectInput8_CreateDeivce" );
					return DIENUM_CONTINUE;
				}
			}

			// �f�o�C�X�f�[�^���擾
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

			// �f�o�C�X�t�H�[�}�b�g�̐ݒ�
			{
				HRESULT	hr = data->mp_device->SetDataFormat( &c_dfDIJoystick );
				if( FAILED( hr ) )
				{
					FILE_LINE_PRINT( "Error: SetDataFormat ");
					return DIENUM_CONTINUE;
				}
			}

			// �f�o�C�X�̋������x���̐ݒ�(�W���C�X�e�B�b�N)
			{
				HRESULT hr = data->mp_device->SetCooperativeLevel( 	data->m_wnd,  DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY );
				if( FAILED( hr ) )
				{
					FILE_LINE_PRINT( "Error SetCooperativeLevel ");
					return DIENUM_CONTINUE;	
				}
			}

			// �f�o�C�X�̃v���p�e�B�ݒ�
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
		
			// �g�p�\�ȃf�o�C�X���o�͓o�^
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

		//	�ϐ�
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

		// �W���C�X�e�b�N�̓��͌���
		struct _tag_State	m_state[ eINPUT_DATA_TYPE_MAX ];

		unsigned char m_repert_cnt[Input::PAD_KEY_MAX];

		struct _tag_State	m_input[ PAD_TYPE_MAX ];
		HWND				m_wnd;
	};

} // JoyInput

#endif // __JOYSTATCMANAGERIMPL_H__
