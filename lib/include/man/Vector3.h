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

	// ®”İ’è
	explicit	Vector3( int aX, int aY, int aZ );

	//	‰Šú‰»
	void	zero( void )	{	x	= 0.f;	y	= 0.f;	z	= 0.f;	}

	// Ï˜a
	void madd( const Vector3& a, double b );

	// Ï˜aİ’è
	void setMadd( const Vector3& a, double b, const Vector3& c );

	// ‰ÁZ
	void setAdd( const Vector3& a, const Vector3& b );
	
	// Œ¸Z
	void setSub( const Vector3& a, const Vector3& b );
	
	// ÏZ
	void setMul( const Vector3& a, const Vector3& b );	

	// ‚QŸŒ³•âŠÔ‚ğs‚¤
	void setInterporation(	const Vector3& a,
							const Vector3& ab,
							const Vector3& ac,
							double u,
							double v );

	//	³‹K‰»
	void	normalize( void );

	// ‰‰Z’è‹`
	void operator+=( const Vector3& a );	// ‘«‚µZ
	void operator-=( const Vector3& a );	// ˆø‚«Z
	void operator=( const Vector3& a );		// ƒRƒs[
	void operator*=( const Vector3& a );	// Š|‚¯Z
	void operator/=( const Vector3& a );	// Š„‚èZ

	// •p”É‚ÉƒAƒNƒZƒX‚·‚é•Ï”‚É‚Íprivatew’è‚É‚Í‚µ‚È‚¢
	double x, y, z;
};

//	”ñƒƒ“ƒo[ŠÖ”

//	‘å‚«‚³æ“¾
inline	double	GetVector3Mag( const Vector3&	in_v );

//	‹——£æ“¾
inline	double	GetVector3Distance( const Vector3&	in_v, const Vector3&	in_v2 );

#endif // __VECTOR3_H__
