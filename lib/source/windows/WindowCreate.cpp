/**
 *	@file 	D:/ProgramStady/Game/2D/MiracleShot/Proj/src/fw/CWinApp.cpp
 *	@brief
 *	@author	yuto uchida
 *	@data   2009-08-21
 *	@note
 *
 */
#include "WindowCreate.h"

#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <crtdbg.h>
#include <mmsystem.h>

#include "directx/Manager.h"
#include "game/GameSystem.h"
#include "debug/DebugScreen.h"

#pragma once
#pragma comment(lib,"winmm.lib")

#ifdef _DEBUG
	#define _DEBUG_CONSOLE
#endif

// �Q�[���V�X�e���쐬
static DirectXWindowCreate	g_Window;

/*
	�E�B���h�E�v���V�[�W���[
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam)
{
    switch (mes) {
		case WM_CREATE: {
			// �E�B���h�E�쐬���ɍŏ��ɌĂ΂��

#ifdef _DEBUG_CONSOLE
			// �R���\�[���\���ݒ�
			int hConsle;
			AllocConsole();
			hConsle = _open_osfhandle(reinterpret_cast<long>(GetStdHandle(STD_OUTPUT_HANDLE)), _O_TEXT);
			*stdout = *_fdopen(hConsle, "w");
			setvbuf(stdout, NULL, _IONBF, 0);
#endif
			break;
		}
		case WM_DESTROY: {
			// �E�B���h�E�폜�ɌĂ΂��
#ifdef _DEBUG_CONSOLE
			FreeConsole();
#endif
			PostQuitMessage(0);
			return 0;
		}
		case WM_SETCURSOR: {
	 		return 0;
		}
		case WM_SYSCOMMAND: {
			switch (wParam&0xFFF0)
			{
				case SC_SCREENSAVE:
				//	�X�N���[���Z�C�o�[���N�������Ȃ�
				return (FALSE);
			}
			break;
		}
	}
	return DefWindowProc(hWnd, mes, wParam, lParam);
}

/*
	@brief	
*/
WindowCreate::WindowCreate() :
	mh_inst(0),
	mh_wnd(0),
	// �쐬���ɕK����ʂɏo���K�v������B
	// WinMain���̕\���w����擾����K�v�͂Ȃ�
	m_cmd_show(SW_SHOWNORMAL),
	m_w(0),
	m_h(0)	{}

/*
	@brief	
*/
WindowCreate::~WindowCreate() {}

/*
	@brief	������
	@param	i_title	:	�E�B���h�E�^�C�g��	
	@param	i_inst	:	���݂̃C���X�^���X�n���h��
	@return	����	:	true	/	���s	:	false
*/
bool WindowCreate::VInit( _TCHAR* i_title,	HINSTANCE i_inst, const unsigned in_WSize, const unsigned in_HSize )
{
	mh_inst = i_inst;
	unsigned width	= in_WSize;
	unsigned height = in_HSize;

    // �E�B���h�E�쐬
	WNDCLASSEX wcex ={
	    sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		mh_inst,
		NULL,
    	LoadCursor(NULL, IDC_ARROW),
	    NULL,
		NULL,
		_T("game"),
		NULL};
	if(!RegisterClassEx(&wcex)) { 
		return false;
	}
	mh_wnd = CreateWindow(	wcex.lpszClassName,		// �N���X��
							i_title,				// �E�B���h�E�^�C�g��
							WS_OVERLAPPEDWINDOW,

							// �E�B���h�E������W
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							// �E�B���h�E�̃T�C�Y
							width,
							height,
							NULL, NULL, mh_inst, NULL);
	if(!(mh_wnd) ) { return false; }
	m_w = width;
	m_h = height;

	// �E�B���h�E�̃N���C�A���g�̈�T�C�Y���c���T�C�Y�ɍ��킹��
   	// �N���C�A���g�̈�T�C�Y�擾
    RECT rect;
	GetClientRect( mh_wnd, &rect );
	unsigned cw = rect.right - rect.left;
	unsigned ch = rect.bottom - rect.top;
	unsigned w = width + ( width - cw );
	unsigned h = height + ( height - ch );
	// �E�B���h�E�T�C�Y�Đݒ�
	SetWindowPos(	mh_wnd, HWND_TOP, 
					CW_USEDEFAULT, CW_USEDEFAULT,
					w, h, SWP_NOMOVE );

	// �E�B���h�E�\��
	ShowWindow(mh_wnd, m_cmd_show);
	UpdateWindow(mh_wnd);

	// WM_PAINT����΂Ȃ�
	ValidateRect(mh_wnd,0);

	// ���Ԏ擾�̐��x���グ��
	timeBeginPeriod( 1 );

#ifdef _DEBUG
	//���������[�N���o
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	return true;
}
/*
	@brief	�Q�[������
*/
void WindowCreate::VUpdate()
{
    bool b_loop = true;

	// �E�B���h�E���b�Z�[�W
	MSG msg;
    // �又��
	// ���b�Z�[�W ���[�v
	do
	{
    	//���b�Z�[�W������Ȃ珈��
	    if ( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
		{
			if ( GetMessage( &msg, NULL, 0, 0 ) )
			{
			    TranslateMessage( &msg );
		    	DispatchMessage( &msg );
			}else
			{
		    	break; //WM_QUIT���܂����B���[�v�����܂��B
			}
	    }

		// �Q�[������

	} while( (msg.message != WM_QUIT) && (b_loop == true ) );
}

/*
	@brief	�I��
*/
void WindowCreate::VEnd()
{
}

/*
	@brief ������
*/
bool	DirectXWindowCreate::VInit( _TCHAR* i_title, HINSTANCE i_inst, const unsigned in_WSize, const unsigned in_HSize )
{
	WindowCreate::VInit( i_title, i_inst, in_WSize, in_HSize );
	// DirectX�V�X�e���쐬
	DirectX::Manager::Create( i_inst, mh_wnd, in_WSize, in_HSize, false );

	return true;
}
/*
	@brief �I��
*/
void	DirectXWindowCreate::VEnd()
{
	WindowCreate::VEnd();

	// DirectX�̏I��
	DirectX::Manager::Destroy();
}

/*
	@brief	�X�V����
*/
bool	DirectXWindowCreate::PreUpdate()
{
	MSG msg;

   	//���b�Z�[�W������Ȃ珈��
    if ( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
	{
		if ( GetMessage( &msg, NULL, 0, 0 ) )
		{
		    TranslateMessage( &msg );
	    	DispatchMessage( &msg );
		}else
		{
			// �E�B���h�E����ɂ����[
			return false;
		}
	}

	// ���͏���
	DirectX::Manager::Inst().InputUpdate();

	DirectX::Manager::Inst().DrawPreUpdate();

	return (msg.message != WM_QUIT);
}

bool	DirectXWindowCreate::PostUpdate()
{
	DirectX::Manager::Inst().DrawPostUpdate();

	// �T�E���h����
	DirectX::Manager::Inst().SoundUpdate();

	return true;
}


/*
	@brief	�G���g���[�|�C���g
*/
int APIENTRY _tWinMain(	HINSTANCE hInstance,	HINSTANCE hPrevInstance,	
						LPTSTR lpCmdLine,		int nCmdShow)
{
	UNUSE( hPrevInstance );
	UNUSE( lpCmdLine );
	UNUSE( nCmdShow );

	GameLib::GameSystem&	game = GameLib::GameSystem::Inst();

	//	�����ł̓R���t�B�O�ݒ肷��̂ŃL���X�g���ĕύX�ł���悤�ɂ���B(��������)
	GameLib::GameSystem::GameConfig&	ConfigData	= (GameLib::GameSystem::GameConfig&)game.GetConfig();
	game.Config( &ConfigData );

	// ������
	// �����ŃQ�[���E�B���h�E�̍쐬������
	if( g_Window.VInit(	_T( ConfigData.m_AppName ), hInstance,
							ConfigData.GetScreenSizeX(), ConfigData.GetScreenSizeY() ) == false ) {
		return FALSE;
	}

#ifdef _DEBUG
	// �f�o�b�O�V�X�e��������
	DbgSceneManager::Init();
#endif

	// �Q�[��������
	game.Start();

	// �又��
	// ���b�Z�[�W ���[�v
	bool b_pre_update	= true;
	bool b_post_update	= true;
	bool b_debug_flg	= false;
	do
	{
		// �E�B���h�E�̍X�V����
		// �Q�[���I������܂Ŗ��������Ŗ������[�v���Ă���
		b_pre_update = g_Window.PreUpdate();
		if( b_pre_update == true )
		{
#ifdef _DEBUG
			// q�{�^���Ńf�o�b�OON/OFF
			if( game.IsButtonTriggerOn( 'q' ) )
			{
				b_debug_flg	=	b_debug_flg == false ? true : false;
			}

			if( b_debug_flg == true )
			{
				// �f�o�b�O�V�X�e���X�V
				DbgSceneManager::Update();
			}
#endif

			b_pre_update	= game.Update();
			b_post_update	= g_Window.PostUpdate();
		}
	}while( b_pre_update && b_post_update );

	// �Q�[���I��
	game.Final();

#ifdef _DEBUG
	// �f�o�b�O�V�X�e���I��
	DbgSceneManager::End();
#endif

	// �E�B���h�E�I��
	g_Window.VEnd();

    return 0;
}
