/**
 *	@file 	Vector2.h
 *	@brief	
 *	@author	yuto uchida
 *	@data   2011-07-10
 *	@note 
 *
 */
#ifndef __VECTOR2_H__
#define __VECTOR2_H__

class Vector2 {
public:
	//	�R���g���N�g
	explicit	Vector2( void ) : x( 0.0f ) , y( 0.0f ) {}
	explicit	Vector2( const int in_x, const int in_y );
	explicit	Vector2( const double in_x, const double in_y ) : x( in_x ), y( in_y )	{}

	~Vector2( void )	{}

	//	������
	void	zero( void )	{	x	= 0.f;	y	= 0.f;	}

	//	�Ϙa
	void	madd( const Vector2& a, double b );

	// �Ϙa�ݒ�
	void	setMadd( const Vector2& a, double b, const Vector2& c );

	// ���Z
	void	setAdd( const Vector2& a, const Vector2& b );

	// ���Z
	void	setSub( const Vector2& a, const Vector2& b );
	
	// �ώZ
	void	setMul( const Vector2& a, const Vector2& b );	

	// �Q������Ԃ��s��
	void	setInterporation(	const Vector2& a,
								const Vector2& ab,
								const Vector2& ac,
								double u,
								double v );

	//	���K��
	void	normalize( void );

	// ���Z��`
	void	operator+=( const Vector2& a );	// �����Z
	void	operator-=( const Vector2& a );	// �����Z
	void	operator=( const Vector2& a );	// �R�s�[
	void	operator*=( const Vector2& a );	// �|���Z
	void	operator/=( const Vector2& a );	// ����Z

	// �p�ɂɃA�N�Z�X����ϐ��ɂ�private�w��ɂ͂��Ȃ�
	// �܂�m_�̃v���t�F�b�N�X���K�v�Ȃ�
	double x, y;
};

//	�񃁃��o�[�֐�

//	�傫���擾
inline	double	GetVector2Mag( const Vector2&	in_v );

//	�����擾
inline	double	GetVector2Distance( const Vector2&	in_v, const Vector2&	in_v2 );

#endif // __VECTOR2_H__
