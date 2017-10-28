/**
 *	@file 	D:/ProgramStady/Game/2D/MiracleShot/Proj/src/fw/WinApp.h
 *	@brief	�E�B���h�E�쐬
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
			@brief	������
			@param	i_title	:	�E�B���h�E�^�C�g��	
			@param	i_inst	:	���݂̃C���X�^���X�n���h��
			@param	in_WSize	:	W�T�C�Y
			@param	in_HSize	:	H�T�C�Y
			@return	����	:	true	/	���s	:	false
		*/
		virtual bool	VInit( _TCHAR* i_title, HINSTANCE i_inst, const unsigned in_WSize, const unsigned in_HSize );

		/*
			@brief	����
		*/
		virtual	void	VUpdate();

		/*
			@brief	�I��
		*/
		virtual void	VEnd();

	protected:

		//	�ϐ�
		HINSTANCE	mh_inst;
		HWND		mh_wnd;
		int			m_cmd_show;
		unsigned	m_w,	m_h;
};

/*
	@brief	DirectX�E�B���h�E�쐬
*/
class DirectXWindowCreate : public WindowCreate {

public:
	//	�R���X�g���N�^
	DirectXWindowCreate()	: WindowCreate()	{}
	~DirectXWindowCreate()					{}

	/*
		@brief	������
		@param	i_title		:	�E�B���h�E�^�C�g��	
		@param	i_inst		:	���݂̃C���X�^���X�n���h��
		@param	in_WSize	:	W�T�C�Y
		@param	in_HSize	:	H�T�C�Y
		@return	����	:	true	/	���s	:	false
	*/
	bool	VInit( _TCHAR* i_title, HINSTANCE i_inst, const unsigned in_WSize, const unsigned in_HSize );

	/*
		@brief	�I��
	*/
	void	VEnd();

	/*
		@brief	�X�V����
	*/
	bool PreUpdate();
	bool PostUpdate();

private:
};

#endif // __WINDOW_CTRL_H__
