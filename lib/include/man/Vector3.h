/**
 *	@file 	Vector3.h
 *	@brief	
 *	@author	yuto uchida
 *	@data   2011-07-10
 *	@note 
 *
 */
#ifndef __VECTOR3_H__
#define __VECTOR3_H__

class Vector3 {
public:
	explicit	Vector3()	: x(0.0f) , y(0.0f)  , z(0.0f)	{}
	explicit	Vector3( double aX, double aY, double aZ ) : x(aX), y(aY), z(aZ)	{}

	// �����ݒ�
	explicit	Vector3( int aX, int aY, int aZ );

	//	������
	void	zero( void )	{	x	= 0.f;	y	= 0.f;	z	= 0.f;	}

	// �Ϙa
	void madd( const Vector3& a, double b );

	// �Ϙa�ݒ�
	void setMadd( const Vector3& a, double b, const Vector3& c );

	// ���Z
	void setAdd( const Vector3& a, const Vector3& b );
	
	// ���Z
	void setSub( const Vector3& a, const Vector3& b );
	
	// �ώZ
	void setMul( const Vector3& a, const Vector3& b );	

	// �Q������Ԃ��s��
	void setInterporation(	const Vector3& a,
							const Vector3& ab,
							const Vector3& ac,
							double u,
							double v );

	//	���K��
	void	normalize( void );

	// ���Z��`
	void operator+=( const Vector3& a );	// �����Z
	void operator-=( const Vector3& a );	// �����Z
	void operator=( const Vector3& a );		// �R�s�[
	void operator*=( const Vector3& a );	// �|���Z
	void operator/=( const Vector3& a );	// ����Z

	// �p�ɂɃA�N�Z�X����ϐ��ɂ�private�w��ɂ͂��Ȃ�
	double x, y, z;
};

//	�񃁃��o�[�֐�

//	�傫���擾
inline	double	GetVector3Mag( const Vector3&	in_v );

//	�����擾
inline	double	GetVector3Distance( const Vector3&	in_v, const Vector3&	in_v2 );

#endif // __VECTOR3_H__
