/********************************************************************
	created:	2012/05/11
	created:	11:5:2012   14:06
	file base:	Array2D
	
	purpose:	2次元配列制御クラス
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
	//	コンストラクタ
	//	空のデータ作成
	Array2D()
	{
		_Clear();
	}

	//	作成と同時に設定
	Array2D( T* in_pArray, unsigned in_W, unsigned in_H )
	{
		_Clear();

		_Create( in_pArray, in_W, in_H );
	}

	//	領域のみ作成
	Array2D( unsigned in_W, unsigned in_H )
	{
		_Clear();

		//	格納する配列を設定する
		mp_Array	= new T[ in_H * in_W ];
		::memset( mp_Array, 0, sizeof( T ) * ( in_W * in_H ) );

		m_W	= in_W;
		m_H	= in_H;
	}

	~Array2D()
	{
		_Destry();
	}

	//	配列の全体数
	const unsigned	GetTableNum()	const { return ( m_H * m_W ); }
	//	配列の横数
	const unsigned	GetTableW()		const { return m_W; }
	//	配列の縦数
	const unsigned	GetTableH()		const { return m_H; }

	//	代入専用
	T& operator()( int x, int y )
	{
		ASSERT( mp_Array != NULL );
		ASSERT( (unsigned)x < m_W );
		ASSERT( (unsigned)y < m_H );

		return	mp_Array[ y * m_W + x ];
	}

	//	取得専用
	const T& operator()( int x, int y ) const
	{
		ASSERT( mp_Array != NULL );
		ASSERT( (unsigned)x < m_W );
		ASSERT( (unsigned)y < m_H );

		return	mp_Array[ y * m_W + x ];
	}

	//	コピーする
	void	operator=( Array2D< T >& in_Data )
	{
		_Destry();
		_Create( in_Data.mp_Array, in_Data.m_W, in_Data.m_H );
	}

private:

	//	関数
	void _Clear()
	{
		m_W	= m_H	= 0;
		mp_Array	= NULL;
	}

	//	データ作成
	void _Create( T* in_pArray, unsigned in_W, unsigned in_H )
	{
		ASSERT( in_pArray != NULL );

		//	格納する配列を設定する
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

	//	開放
	void	_Destry()
	{
		SAFE_DELETE_ARRAY( mp_Array );
		m_W	= m_H	= 0;
	}

	//	変数
	T*		mp_Array;
	unsigned	m_W, m_H;
};

#endif // __ARRAY2D_H__