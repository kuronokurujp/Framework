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

// ゲームシステム作成
static DirectXWindowCreate	g_Window;

/*
	ウィンドウプロシージャー
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam)
{
    switch (mes) {
		case WM_CREATE: {
			// ウィンドウ作成時に最初に呼ばれる

#ifdef _DEBUG_CONSOLE
			// コンソール表示設定
			int hConsle;
			AllocConsole();
			hConsle = _open_osfhandle(reinterpret_cast<long>(GetStdHandle(STD_OUTPUT_HANDLE)), _O_TEXT);
			*stdout = *_fdopen(hConsle, "w");
			setvbuf(stdout, NULL, _IONBF, 0);
#endif
			break;
		}
		case WM_DESTROY: {
			// ウィンドウ削除に呼ばれる
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
				//	スクリーンセイバーを起動させない
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
	// 作成時に必ず画面に出す必要がある。
	// WinMain側の表示指定を取得する必要はない
	m_cmd_show(SW_SHOWNORMAL),
	m_w(0),
	m_h(0)	{}

/*
	@brief	
*/
WindowCreate::~WindowCreate() {}

/*
	@brief	初期化
	@param	i_title	:	ウィンドウタイトル	
	@param	i_inst	:	現在のインスタンスハンドル
	@return	成功	:	true	/	失敗	:	false
*/
bool WindowCreate::VInit( _TCHAR* i_title,	HINSTANCE i_inst, const unsigned in_WSize, const unsigned in_HSize )
{
	mh_inst = i_inst;
	unsigned width	= in_WSize;
	unsigned height = in_HSize;

    // ウィンドウ作成
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
	mh_wnd = CreateWindow(	wcex.lpszClassName,		// クラス名
							i_title,				// ウィンドウタイトル
							WS_OVERLAPPEDWINDOW,

							// ウィンドウ左上座標
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							// ウィンドウのサイズ
							width,
							height,
							NULL, NULL, mh_inst, NULL);
	if(!(mh_wnd) ) { return false; }
	m_w = width;
	m_h = height;

	// ウィンドウのクライアント領域サイズを縦横サイズに合わせる
   	// クライアント領域サイズ取得
    RECT rect;
	GetClientRect( mh_wnd, &rect );
	unsigned cw = rect.right - rect.left;
	unsigned ch = rect.bottom - rect.top;
	unsigned w = width + ( width - cw );
	unsigned h = height + ( height - ch );
	// ウィンドウサイズ再設定
	SetWindowPos(	mh_wnd, HWND_TOP, 
					CW_USEDEFAULT, CW_USEDEFAULT,
					w, h, SWP_NOMOVE );

	// ウィンドウ表示
	ShowWindow(mh_wnd, m_cmd_show);
	UpdateWindow(mh_wnd);

	// WM_PAINTをよばない
	ValidateRect(mh_wnd,0);

	// 時間取得の制度を上げる
	timeBeginPeriod( 1 );

#ifdef _DEBUG
	//メモリリーク検出
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	return true;
}
/*
	@brief	ゲーム処理
*/
void WindowCreate::VUpdate()
{
    bool b_loop = true;

	// ウィンドウメッセージ
	MSG msg;
    // 主処理
	// メッセージ ループ
	do
	{
    	//メッセージがあるなら処理
	    if ( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
		{
			if ( GetMessage( &msg, NULL, 0, 0 ) )
			{
			    TranslateMessage( &msg );
		    	DispatchMessage( &msg );
			}else
			{
		    	break; //WM_QUITきました。ループ抜けます。
			}
	    }

		// ゲーム処理

	} while( (msg.message != WM_QUIT) && (b_loop == true ) );
}

/*
	@brief	終了
*/
void WindowCreate::VEnd()
{
}

/*
	@brief 初期化
*/
bool	DirectXWindowCreate::VInit( _TCHAR* i_title, HINSTANCE i_inst, const unsigned in_WSize, const unsigned in_HSize )
{
	WindowCreate::VInit( i_title, i_inst, in_WSize, in_HSize );
	// DirectXシステム作成
	DirectX::Manager::Create( i_inst, mh_wnd, in_WSize, in_HSize, false );

	return true;
}
/*
	@brief 終了
*/
void	DirectXWindowCreate::VEnd()
{
	WindowCreate::VEnd();

	// DirectXの終了
	DirectX::Manager::Destroy();
}

/*
	@brief	更新処理
*/
bool	DirectXWindowCreate::PreUpdate()
{
	MSG msg;

   	//メッセージがあるなら処理
    if ( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
	{
		if ( GetMessage( &msg, NULL, 0, 0 ) )
		{
		    TranslateMessage( &msg );
	    	DispatchMessage( &msg );
		}else
		{
			// ウィンドウ閉じるにきたー
			return false;
		}
	}

	// 入力処理
	DirectX::Manager::Inst().InputUpdate();

	DirectX::Manager::Inst().DrawPreUpdate();

	return (msg.message != WM_QUIT);
}

bool	DirectXWindowCreate::PostUpdate()
{
	DirectX::Manager::Inst().DrawPostUpdate();

	// サウンド処理
	DirectX::Manager::Inst().SoundUpdate();

	return true;
}


/*
	@brief	エントリーポイント
*/
int APIENTRY _tWinMain(	HINSTANCE hInstance,	HINSTANCE hPrevInstance,	
						LPTSTR lpCmdLine,		int nCmdShow)
{
	UNUSE( hPrevInstance );
	UNUSE( lpCmdLine );
	UNUSE( nCmdShow );

	GameLib::GameSystem&	game = GameLib::GameSystem::Inst();

	//	ここではコンフィグ設定するのでキャストして変更できるようにする。(ここだけ)
	GameLib::GameSystem::GameConfig&	ConfigData	= (GameLib::GameSystem::GameConfig&)game.GetConfig();
	game.Config( &ConfigData );

	// 初期化
	// ここでゲームウィンドウの作成をする
	if( g_Window.VInit(	_T( ConfigData.m_AppName ), hInstance,
							ConfigData.GetScreenSizeX(), ConfigData.GetScreenSizeY() ) == false ) {
		return FALSE;
	}

#ifdef _DEBUG
	// デバッグシステム初期化
	DbgSceneManager::Init();
#endif

	// ゲーム初期化
	game.Start();

	// 主処理
	// メッセージ ループ
	bool b_pre_update	= true;
	bool b_post_update	= true;
	bool b_debug_flg	= false;
	do
	{
		// ウィンドウの更新処理
		// ゲーム終了するまで無限内部で無限ループしている
		b_pre_update = g_Window.PreUpdate();
		if( b_pre_update == true )
		{
#ifdef _DEBUG
			// qボタンでデバッグON/OFF
			if( game.IsButtonTriggerOn( 'q' ) )
			{
				b_debug_flg	=	b_debug_flg == false ? true : false;
			}

			if( b_debug_flg == true )
			{
				// デバッグシステム更新
				DbgSceneManager::Update();
			}
#endif

			b_pre_update	= game.Update();
			b_post_update	= g_Window.PostUpdate();
		}
	}while( b_pre_update && b_post_update );

	// ゲーム終了
	game.Final();

#ifdef _DEBUG
	// デバッグシステム終了
	DbgSceneManager::End();
#endif

	// ウィンドウ終了
	g_Window.VEnd();

    return 0;
}
