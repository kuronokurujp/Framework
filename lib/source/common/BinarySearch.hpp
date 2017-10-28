/**
 *	@file 	BinarySearch.h
 *	@brief	�o�C�i���T�[�`
 *	@author	yuto uchida
 *	@data   2011-07-29
 *	@note 	�w�肷��z��͂��炩���ߏ����Ƀ\�[�g����B
 *
 */
#ifndef __BINARYSEARCH_H__
#define __BINARYSEARCH_H__

/*
	�l���������ꂽ�z��̂Q���T���̌���
	�g�p�@
		�R���X�g���N�^�Ŕz��ݒ�
		���ʂ�getHitByIndex()�Ŏ󂯎��B

	�e���v���[�g�N���X�ɂ��Ă���̂ŁA
	�g�����Ō����f�[�^�^�C�v���w��B
*/
template < class Type > class BinarySearch
{
public:
	//	�萔
	enum
	{
		NOHIT	= -1,	//	�������s
	};

	//	�R���X�g���N�^
	BinarySearch( const Type* in_p_array, const int in_array_num, const Type& in_r_search ) {
		m_hit_index	= _search( in_p_array, in_array_num, in_r_search );
	}
	~BinarySearch( void )	{}

	//	�������ʂ�Ԃ�
	const int getHitByIndex( void ) const { return m_hit_index; }

private:
	//	�֐�
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
				//	�����l���z��̑O�ɂ���
				last	= middle - 1;
			}
			else if( r_data < in_r_search )
			{
				//	�����l���z��̌��ɂ���B
				first	= middle + 1;
			}
			else
			{
				//	��������
				return	middle;
			}
		}

		//	�擪���������z���鎞�A���[�v���I������B
		//	�擪�Ɩ����̊Ԃ��Ȃ��P�[�X�̏ꍇ�擪�Ɍ����l�����邩������Ȃ��̂ŁA
		//	�����ōă`�F�b�N
		/*
			�擪			����
			0(�����l)		1(�����l)

			���̌��ʎ��͐擪�͖����̒l�ɂȂ�
			�����Ń��[�v�͏I��
			�擪�̃f�[�^�𒲂ׂ�Ό����l�ɂȂ�B
		*/
		if( in_p_array[ first ] == in_r_search ) {
			return	first;
		}

		return	NOHIT;
	}

	//	�ϐ�
	int		m_hit_index;
};

#endif // __BINARYSEARCH_H__
