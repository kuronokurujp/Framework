/**
 *	@file 	SelectedList.h
 *	@brief	�I�����X�g
 *	@author	yuto uchida
 *	@data   2011-04-23
 *	@note	�c�����̑I�����X�g����
 *
 */
#ifndef __SELECTEDLIST_H__
#define __SELECTEDLIST_H__

#include <stdio.h>
#include "Env.h"

/*
	@brief	�I�����X�g
*/
class	SelectedList
{
public:
	/*
		�R���X�g���N�^
	*/
	SelectedList()	{ _Clear(); }
	virtual ~SelectedList()	{}

	/*
		�֐�
	*/
	// ���X�g�f�[�^�쐬
	void	Create( const unsigned int	in_Num,	const unsigned int in_ViewNum, const unsigned int	in_Magin );
	// ���X�g�j��
	void	Destroy();

	// ���X�g�ǉ�
	// �����Ŏ��ۂ̃��X�g����������
	void	Add( const char* in_pName,	const int	in_ID = 0,	void*	in_pArg = NULL );
	// �w�肵�����X�g�N���A
	// ���������X�g��������킯�ł͂Ȃ�
	void	ClearByIndex( const int in_Index );

	// �w�肵�����X�g�폜
	void	DelByIndex( const int	in_Index );

	void	Update()	{ _VUpdatePad(); }

	// ���݂̎w��J�[�\���̃f�[�^�擾
	const int		GetCursorByIndex( void )	const	{ return	m_CursorIndex;	}
	const char*		GetCursorByName( void )		{ return	GetName( GetCursorByIndex() );	}
	const int		GetCursorByDataID( void )	{ return	GetDataID( GetCursorByIndex() );	}
	void*			GetCursorByArg( void )		{ return	GetArg( GetCursorByIndex() );	}

	const char*		GetName( const int in_Index )	{ return	_GetData( in_Index )->Name;	}
	const int		GetDataID( const int in_Index )	{ return	_GetData( in_Index )->ID;	}
	void*			GetArg( const int in_Index )	{ return	_GetData( in_Index )->pArg;	}

	// ���X�g���擾
	// add()���g�������̐�
	const int		GetNum()		const	{ return m_ListMax;	}
	// �쐬���ڐ��擾
	const int		GetDataNum()	const	{ return m_DataMax; }

	//	�\���̈搔�擾
	const int		GetViewNum()	const	{ return m_ViewMax; }

	// �J�[�\���ݒ�
	void	SetCursorByIndex( const int in_Index );

	//�f�o�b�O�p
	void	DebugDraw();

protected:
	/*
		�֐�
	*/
	void			_Move( int in_Offset );

private:
	/*
		��`
	*/
	typedef struct {
		const char*		Name;
		int				ID;
		void*			pArg;
	} _DATA_ST;	

	/*
		�ϐ�
	*/
	_DATA_ST*	mp_Data;
	int			m_DataMax;
	int			m_ListMax;

	int			m_CursorIndex;

	int			m_ViewTop;
	int			m_ViewMax;

	int			m_Magin;

	/*
		�֐�
	*/
	void			_Clear();
	_DATA_ST*		_GetData( const int in_Index );

	/*
		���z�֐�
	*/
	virtual		void	_VUpdatePad()	{}
// �f�o�b�O�p
	virtual		void	_VDebugText( const int in_ListIndex, const int	in_ViewIndex )	{ UNUSE( in_ListIndex ); UNUSE( in_ViewIndex );}
};

/*
	@brief	�I�����X�g���͐���
*/
class SelectedListInput :	public SelectedList
{
public:
	//	�R���X�g���N�^
	SelectedListInput()	: SelectedList()	{}
	virtual ~SelectedListInput()	{}

private:
	//	�֐�
	virtual		void	_VUpdatePad( void );
	// �f�o�b�O�p
	virtual		void	_VDebugText( const int in_ListIndex, const int in_ViewIndex );
};

#endif // __SELECTEDLIST_H__
