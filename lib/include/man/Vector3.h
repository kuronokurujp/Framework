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

	// 整数設定
	explicit	Vector3( int aX, int aY, int aZ );

	//	初期化
	void	zero( void )	{	x	= 0.f;	y	= 0.f;	z	= 0.f;	}

	// 積和
	void madd( const Vector3& a, double b );

	// 積和設定
	void setMadd( const Vector3& a, double b, const Vector3& c );

	// 加算
	void setAdd( const Vector3& a, const Vector3& b );
	
	// 減算
	void setSub( const Vector3& a, const Vector3& b );
	
	// 積算
	void setMul( const Vector3& a, const Vector3& b );	

	// ２次元補間を行う
	void setInterporation(	const Vector3& a,
							const Vector3& ab,
							const Vector3& ac,
							double u,
							double v );

	//	正規化
	void	normalize( void );

	// 演算定義
	void operator+=( const Vector3& a );	// 足し算
	void operator-=( const Vector3& a );	// 引き算
	void operator=( const Vector3& a );		// コピー
	void operator*=( const Vector3& a );	// 掛け算
	void operator/=( const Vector3& a );	// 割り算

	// 頻繁にアクセスする変数にはprivate指定にはしない
	double x, y, z;
};

//	非メンバー関数

//	大きさ取得
inline	double	GetVector3Mag( const Vector3&	in_v );

//	距離取得
inline	double	GetVector3Distance( const Vector3&	in_v, const Vector3&	in_v2 );

#endif // __VECTOR3_H__
