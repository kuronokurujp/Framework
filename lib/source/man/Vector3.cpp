/**
 *	@file 	Vector3.cpp
 *	@brief	
 *	@author	yuto uchida
 *	@data   2011-07-10
 *	@note 
 *
 */
#include "vector3.h"

Vector3::Vector3( int aX, int aY , int aZ) 
{
	x = static_cast<double>(aX);
	y = static_cast<double>(aY);
	z = static_cast<double>(aZ);
}

void Vector3::operator+=( const Vector3& a ) 
{
	x += a.x;	y += a.y;	z += a.z;
}

void Vector3::operator-=( const Vector3& a ) 
{
	x -= a.x;	y -= a.y;	z -= a.z;
}

void Vector3::operator=( const Vector3& a ) 
{
	x = a.x;	y = a.y;	z = a.z;
}

void Vector3::operator*=( const Vector3& a ) 
{
	x *= a.x;	y *= a.y;	z *= a.z;
}

// 割り算
void Vector3::operator/=( const Vector3& a )
{
	x /= a.x;	y /= a.y;	z /= a.z;
}

// 積和
// a 方向ベクトル
// b 方向ベクトルのスカラー
void Vector3::madd( const Vector3& a, double b ) 
{
	x += (a.x * b);
	y += (a.y * b);
	z += (a.z * b);
}

// 積和設定
// a 方向ベクトル
// b 方向ベクトルの長さスカラー
// c 視点ベクトル
void Vector3::setMadd( const Vector3& a, double b, const Vector3& c ) 
{
	x = a.x * b + c.x;
	y = a.y * b + c.y;	
	z = a.z * b + c.z;
}

// 加算
void Vector3::setAdd( const Vector3& a, const Vector3& b ) 
{
	x = a.x + b.x;
	y = a.y + b.y;
	z = a.z + b.z;
}

// 減算
void Vector3::setSub( const Vector3& a, const Vector3& b ) 
{
	x = a.x - b.x;
	y = a.y - b.y;
	z = a.z - b.z;
}

// 積算
void Vector3::setMul( const Vector3& a,	const Vector3& b ) 
{
	x = a.x * b.x;
	y = a.y * b.y;
	z = a.z * b.z;
}

// ２次元補間を行う
void Vector3::setInterporation(	
const Vector3& a,
const Vector3& ab,
const Vector3& ac,
double u,
double v ) 
{
	setMadd(ab, u, a);	// a + u(b - a)
	madd(ac, v);	// a + u(b - a) + v(c - a)
}

//	正規化
void	Vector3::normalize( void )
{
	float	mag_sq	= x * x + y * y + z * z;
	if( mag_sq > 0.f ) {
		float	onew_over_mag	= 1.f / sqrt( mag_sq );
		x	*=	onew_over_mag;
		y	*=	onew_over_mag;
		z	*=	onew_over_mag;
	}
}

//	非メンバー関数

//	大きさ取得
inline	double	GetVector3Mag( const Vector3&	in_v )
{
	return	sqrt( in_v.x * in_v.x + in_v.y * in_v.y + in_v.z * in_v.z );
}

//	距離取得
inline	double	GetVector3Distance( const Vector3&	in_v, const Vector3&	in_v2 )
{
	Vector3	size;
	size.setSub( in_v2, in_v );

	return	( GetVector3Mag( size ) );
}
