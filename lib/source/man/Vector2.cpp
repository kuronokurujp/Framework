/**
 *	@file 	Vector2.cpp
 *	@brief	ベクトルクラス２次元
 *	@author	yuto uchida
 *	@data   2011-07-10
 *	@note 
 *
 */
#include "Vector2.h"

#include <math.h>

Vector2::Vector2( const int in_x, const int in_y ) 
{
	x = static_cast<double>( in_x );
	y = static_cast<double>( in_y );
}

void	Vector2::operator+=( const Vector2& a ) 
{
	x += a.x;	y += a.y;
}

void	Vector2::operator-=( const Vector2& a ) 
{
	x -= a.x;	y -= a.y;
}

void	Vector2::operator=( const Vector2& a ) 
{
	x = a.x;	y = a.y;
}

void	Vector2::operator*=( const Vector2& a ) 
{
	x *= a.x;	y *= a.y;
}

// 割り算
void	Vector2::operator/=( const Vector2& a )
{
	if( ( x != 0.f ) && ( a.x != 0.f ) ) {
		x	/=	a.x;
	}

	if( ( y != 0.f ) && ( a.y != 0.f ) ) {
		y	/=	a.y;
	}
}

// 積和
// a 方向ベクトル
// b 方向ベクトルのスカラー
void	Vector2::madd( const Vector2& a, double b ) 
{
	x += (a.x * b);
	y += (a.y * b);
}

// 積和設定
// a 方向ベクトル
// b 方向ベクトルの長さスカラー
// c 視点ベクトル
void	Vector2::setMadd( const Vector2& a, double b, const Vector2& c ) 
{
	x = a.x * b + c.x;
	y = a.y * b + c.y;	
}

// 加算
void	Vector2::setAdd( const Vector2& a, const Vector2& b ) 
{
	x = a.x + b.x;
	y = a.y + b.y;
}

// 減算
void	Vector2::setSub( const Vector2& a, const Vector2& b ) 
{
	x = a.x - b.x;
	y = a.y - b.y;
}

// 積算
void	Vector2::setMul( const Vector2& a,	const Vector2& b ) 
{
	x = a.x * b.x;
	y = a.y * b.y;
}


// ２次元補間を行う
void	Vector2::setInterporation(	
const	Vector2&	a,
const	Vector2&	ab,
const	Vector2&	ac,
double	u,
double	v ) 
{
	setMadd(ab, u, a);	// a + u(b - a)
	madd(ac, v);	// a + u(b - a) + v(c - a)
}

//	正規化
void	Vector2::normalize( void )
{
	float	mag_sq	= x * x + y * y;
	if( mag_sq > 0.f ) {
		float	onew_over_mag	= 1.f / sqrt( mag_sq );
		x	*=	onew_over_mag;
		y	*=	onew_over_mag;
	}
}

//	大きさ取得
inline	double	GetVector2Mag( const Vector2&	in_v )
{
	return	sqrt( in_v.x * in_v.x + in_v.y * in_v.y );
}

//	距離取得
inline	double	GetVector2Distance( const Vector2&	in_v, const Vector2&	in_v2 )
{
	Vector2	size;
	size.setSub( in_v2, in_v );

	return	GetVector2Mag( size );
}

