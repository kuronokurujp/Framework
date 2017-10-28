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
	//	コントラクト
	explicit	Vector2( void ) : x( 0.0f ) , y( 0.0f ) {}
	explicit	Vector2( const int in_x, const int in_y );
	explicit	Vector2( const double in_x, const double in_y ) : x( in_x ), y( in_y )	{}

	~Vector2( void )	{}

	//	初期化
	void	zero( void )	{	x	= 0.f;	y	= 0.f;	}

	//	積和
	void	madd( const Vector2& a, double b );

	// 積和設定
	void	setMadd( const Vector2& a, double b, const Vector2& c );

	// 加算
	void	setAdd( const Vector2& a, const Vector2& b );

	// 減算
	void	setSub( const Vector2& a, const Vector2& b );
	
	// 積算
	void	setMul( const Vector2& a, const Vector2& b );	

	// ２次元補間を行う
	void	setInterporation(	const Vector2& a,
								const Vector2& ab,
								const Vector2& ac,
								double u,
								double v );

	//	正規化
	void	normalize( void );

	// 演算定義
	void	operator+=( const Vector2& a );	// 足し算
	void	operator-=( const Vector2& a );	// 引き算
	void	operator=( const Vector2& a );	// コピー
	void	operator*=( const Vector2& a );	// 掛け算
	void	operator/=( const Vector2& a );	// 割り算

	// 頻繁にアクセスする変数にはprivate指定にはしない
	// またm_のプリフェックスも必要ない
	double x, y;
};

//	非メンバー関数

//	大きさ取得
inline	double	GetVector2Mag( const Vector2&	in_v );

//	距離取得
inline	double	GetVector2Distance( const Vector2&	in_v, const Vector2&	in_v2 );

#endif // __VECTOR2_H__
