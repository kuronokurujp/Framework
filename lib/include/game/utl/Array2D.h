/********************************************************************
	created:	2012/05/11
	created:	11:5:2012   14:06
	file base:	Array2D
	
	purpose:	2�����z�񐧌�N���X
*********************************************************************/
#ifndef __ARRAY2D_H__
#define __ARRAY2D_H__

#include "common/Common.h"

/*
	@brief	
*/
template< class T > class Array2D
{
public:
	//	�R���X�g���N�^
	//	��̃f�[�^�쐬
	Array2D()
	{
		_Clear();
	}

	//	�쐬�Ɠ����ɐݒ�
	Array2D( T* in_pArray, unsigned in_W, unsigned in_H )
	{
		_Clear();

		_Create( in_pArray, in_W, in_H );
	}

	//	�̈�̂ݍ쐬
	Array2D( unsigned in_W, unsigned in_H )
	{
		_Clear();

		//	�i�[����z���ݒ肷��
		mp_Array	= new T[ in_H * in_W ];
		::memset( mp_Array, 0, sizeof( T ) * ( in_W * in_H ) );

		m_W	= in_W;
		m_H	= in_H;
	}

	~Array2D()
	{
		_Destry();
	}

	//	�z��̑S�̐�
	const unsigned	GetTableNum()	const { return ( m_H * m_W ); }
	//	�z��̉���
	const unsigned	GetTableW()		const { return m_W; }
	//	�z��̏c��
	const unsigned	GetTableH()		const { return m_H; }

	//	�����p
	T& operator()( int x, int y )
	{
		ASSERT( mp_Array != NULL );
		ASSERT( (unsigned)x < m_W );
		ASSERT( (unsigned)y < m_H );

		return	mp_Array[ y * m_W + x ];
	}

	//	�擾��p
	const T& operator()( int x, int y ) const
	{
		ASSERT( mp_Array != NULL );
		ASSERT( (unsigned)x < m_W );
		ASSERT( (unsigned)y < m_H );

		return	mp_Array[ y * m_W + x ];
	}

	//	�R�s�[����
	void	operator=( Array2D< T >& in_Data )
	{
		_Destry();
		_Create( in_Data.mp_Array, in_Data.m_W, in_Data.m_H );
	}

private:

	//	�֐�
	void _Clear()
	{
		m_W	= m_H	= 0;
		mp_Array	= NULL;
	}

	//	�f�[�^�쐬
	void _Create( T* in_pArray, unsigned in_W, unsigned in_H )
	{
		ASSERT( in_pArray != NULL );

		//	�i�[����z���ݒ肷��
		mp_Array	= new T[ in_H * in_W ];

		for( unsigned y = 0; y < in_H; ++y )
		{
			for( unsigned x = 0; x < in_W; ++x )
			{
				mp_Array[ y * in_W + x ]	= in_pArray[ y * in_W + x ];
			}
		}

		m_W	= in_W;
		m_H	= in_H;
	}

	//	�J��
	void	_Destry()
	{
		SAFE_DELETE_ARRAY( mp_Array );
		m_W	= m_H	= 0;
	}

	//	�ϐ�
	T*		mp_Array;
	unsigned	m_W, m_H;
};

#endif // __ARRAY2D_H__