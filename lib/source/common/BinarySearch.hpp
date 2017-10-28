/**
 *	@file 	BinarySearch.h
 *	@brief	バイナリサーチ
 *	@author	yuto uchida
 *	@data   2011-07-29
 *	@note 	指定する配列はあらかじめ昇順にソートする。
 *
 */
#ifndef __BINARYSEARCH_H__
#define __BINARYSEARCH_H__

/*
	値が昇順された配列の２分探索の検索
	使用法
		コンストラクタで配列設定
		結果をgetHitByIndex()で受け取る。

	テンプレートクラスにしているので、
	使う側で検索データタイプを指定。
*/
template < class Type > class BinarySearch
{
public:
	//	定数
	enum
	{
		NOHIT	= -1,	//	検索失敗
	};

	//	コンストラクタ
	BinarySearch( const Type* in_p_array, const int in_array_num, const Type& in_r_search ) {
		m_hit_index	= _search( in_p_array, in_array_num, in_r_search );
	}
	~BinarySearch( void )	{}

	//	検索結果を返す
	const int getHitByIndex( void ) const { return m_hit_index; }

private:
	//	関数
	int		_search( const Type* in_p_array, const int in_array_num, const Type& in_r_search )
	{
		if( in_p_array == 0 ) {
			return	-1;
		}

		int	first	= 0;
		int	last	= in_array_num - 1;
		int	middle	= 0;
		while( first < last )
		{
			middle	= ( last + first ) >> 1;
			const Type& r_data	= in_p_array[ middle ];
			if( r_data > in_r_search ) {
				//	検索値が配列の前にある
				last	= middle - 1;
			}
			else if( r_data < in_r_search )
			{
				//	検索値が配列の後ろにある。
				first	= middle + 1;
			}
			else
			{
				//	見つかった
				return	middle;
			}
		}

		//	先頭が末尾を越える時、ループが終了する。
		//	先頭と末尾の間がないケースの場合先頭に検索値があるかもしれないので、
		//	ここで再チェック
		/*
			先頭			末尾
			0(中央値)		1(検索値)

			この結果次は先頭は末尾の値になる
			ここでループは終了
			先頭のデータを調べれば検索値になる。
		*/
		if( in_p_array[ first ] == in_r_search ) {
			return	first;
		}

		return	NOHIT;
	}

	//	変数
	int		m_hit_index;
};

#endif // __BINARYSEARCH_H__
