/**
 *	@file 	common/Man.h
 *	@brief	
 *	@author	yuto uchida
 *	@data   2010-12-02
 *	@note 	便利な計算方法を関数で提供
 *
 */
#ifndef __MAN_H__
#define __MAN_H__

#include "./../directx/Manager.h"

#define RADIAN_TO_ANGLE	( 180.0f / 3.14f )
#define ANGLE_TO_RADIAN	( 3.14f	/180.0f )

//	矩形情報
typedef struct  
{
	float	left;
	float	top;
	float	right;
	float	bottom;
} RECT_DATA_ST;

/*
	@brief	2Dベクトル<BR>
	@note	DirectX側で用意したのをラップしたもの<BR>
*/
class Vec2	: public D3DXVECTOR2
{
public:
	//	コンストラクタ
	Vec2() : D3DXVECTOR2( 0.f, 0.f )	{};
	Vec2( const float in_X, const float in_Y ) : D3DXVECTOR2( in_X, in_Y )	{}
	~Vec2()	{}

	void	Set( const float in_X, const float in_Y ) { x = in_X; y = in_Y; }
};

/*
	@brief	3Dベクトル<BR>
	@note	DirectX側で用意したのをラップしたもの<BR>
*/
class Vec3	: public D3DXVECTOR3
{
public:
	Vec3() : D3DXVECTOR3( 0.f, 0.f, 0.f ) {}

	Vec3( const float in_X, const float in_Y, const float in_Z ) :
	D3DXVECTOR3( in_X, in_Y, in_Z ) {}

	Vec3( const Vec3& in_Vec ) : D3DXVECTOR3( in_Vec.x, in_Vec.y, in_Vec.z ) {}

	/*
		@brief	値設定
	*/
	void Set( const float in_X, const float in_Y, const float in_Z )
	{ x = in_X; y = in_Y; z = in_Z; }

	/*
		@brief	自身を加算して返す<BR>
	*/
	Vec3&	operator +=( const Vec3& a )
	{
		x	+= a.x;
		y	+= a.y;
		z	+= a.z;

		return	*this;
	}

	/*
		@brief	自身を減算して返す<BR>
	*/
	Vec3&	operator -=( const Vec3& a )
	{
		x	-= a.x;
		y	-= a.y;
		z	-= a.z;

		return	*this;
	}

	Vec3	operator +( const Vec3& a ) const
	{
		return	Vec3( x + a.x, y + a.y, z + a.z );
	}

	Vec3	operator -( const Vec3& a ) const
	{
		return	Vec3( x - a.x, y - a.y, z - a.z );
	}

	/*
		@brief	スケール
	*/
	Vec3	operator *( const float a ) const
	{
		return	Vec3( x * a, y * a, z * a );
	}

	float	operator *( const Vec3& a ) const
	{
		return	x * a.x + y * a.y + z * a.z;
	}

	inline	Vec3&	Normalize()
	{
		Vec3*	pVec	=	(Vec3*)D3DXVec3Normalize( this, this );
		return	*pVec;
	}
};

inline Vec3	CrossProduct( const Vec3& a, const Vec3& b )
{
	return	Vec3( a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x );
}

/*
	@brief	マトリックス<BR>
	@note	DirectX側のをラップ<BR>
*/
class Marixt4x4	: public D3DXMATRIX
{
public:

	//	関数
	//	単位行列
	void	Identity()	{ D3DXMatrixIdentity( this ); }

	//	回転
	//	X軸
	void	RotaX( const float in_Angle )
	{
		Marixt4x4	m	= *this;
		D3DXMatrixRotationX( &m, in_Angle );
		D3DXMatrixMultiply( this, this, &m );
	}

	//	Y軸
	void	RotaY( const float in_Angle )
	{
		Marixt4x4	m	= *this;
		D3DXMatrixRotationY( &m, in_Angle );
		D3DXMatrixMultiply( this, this, &m );
	}

	//	Z軸
	void	RotaZ( const float in_Angle )
	{
		Marixt4x4	m	= *this;
		D3DXMatrixRotationZ( &m, in_Angle );
		D3DXMatrixMultiply( this, this, &m );
	}

	//	スケール
	void	Scale( const float in_ScaleX, const float in_ScaleY, const float in_ScaleZ )
	{
		Marixt4x4	m	= *this;
		D3DXMatrixScaling( &m, in_ScaleX, in_ScaleY, in_ScaleZ );
		D3DXMatrixMultiply( this, this, &m );
	}

	//	平行移動
	void	Translation( const Vec3& in_Pos )
	{
		Marixt4x4	m	= *this;
		D3DXMatrixTranslation( &m, in_Pos.x, in_Pos.y, in_Pos.z );
		D3DXMatrixMultiply( this, this, &m );
	}

	//	ベクトルとマトリクスを計算してベクトルを作成
	Vec3	Transform( Vec3& in_rVec )
	{ 
		Vec3	vec;
		D3DXVec3TransformCoord( &vec, &in_rVec, this );
		return	vec;
	}

	//	転置行列取得
	Marixt4x4	GetTranspose()
	{
		Marixt4x4	mat;
		D3DXMatrixTranspose( &mat, this );

		return	mat;
	}
};

/*
	@brief	円運動座標計算
	@param	i_center_pos	:	円運動の中心座標
	@param	i_radius		:	円の半径
	@return	ip_pos			:	円運動結果の座標取得
*/
Vec3	CalcRotaryPos( const Vec3& i_center_pos, float i_radius );

#endif // __MAN_H__
