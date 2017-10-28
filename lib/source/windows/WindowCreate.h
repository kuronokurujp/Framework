/**
 *	@file 	D:/ProgramStady/Game/2D/MiracleShot/Proj/src/fw/WinApp.h
 *	@brief	ウィンドウ作成
 *	@author	yuto uchida
 *	@data   2009-08-21
 *	@note
 *
 */
#ifndef __WINDOW_CTRL_H__
#define __WINDOW_CTRL_H__

#include <windows.h>
#include <tchar.h>

class WindowCreate {
	public:
		WindowCreate();
		virtual ~WindowCreate();

		/*
			@brief	初期化
			@param	i_title	:	ウィンドウタイトル	
			@param	i_inst	:	現在のインスタンスハンドル
			@param	in_WSize	:	Wサイズ
			@param	in_HSize	:	Hサイズ
			@return	成功	:	true	/	失敗	:	false
		*/
		virtual bool	VInit( _TCHAR* i_title, HINSTANCE i_inst, const unsigned in_WSize, const unsigned in_HSize );

		/*
			@brief	処理
		*/
		virtual	void	VUpdate();

		/*
			@brief	終了
		*/
		virtual void	VEnd();

	protected:

		//	変数
		HINSTANCE	mh_inst;
		HWND		mh_wnd;
		int			m_cmd_show;
		unsigned	m_w,	m_h;
};

/*
	@brief	DirectXウィンドウ作成
*/
class DirectXWindowCreate : public WindowCreate {

public:
	//	コンストラクタ
	DirectXWindowCreate()	: WindowCreate()	{}
	~DirectXWindowCreate()					{}

	/*
		@brief	初期化
		@param	i_title		:	ウィンドウタイトル	
		@param	i_inst		:	現在のインスタンスハンドル
		@param	in_WSize	:	Wサイズ
		@param	in_HSize	:	Hサイズ
		@return	成功	:	true	/	失敗	:	false
	*/
	bool	VInit( _TCHAR* i_title, HINSTANCE i_inst, const unsigned in_WSize, const unsigned in_HSize );

	/*
		@brief	終了
	*/
	void	VEnd();

	/*
		@brief	更新処理
	*/
	bool PreUpdate();
	bool PostUpdate();

private:
};

#endif // __WINDOW_CTRL_H__
