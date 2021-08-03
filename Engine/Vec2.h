#pragma once
#include "Vei2.h"

class Vec2
{
public:
	Vec2() = default;
	Vec2( float x_in,float y_in );
	Vec2( const Vec2& src );
	const Vec2& operator=( const Vec2& rhs );
	Vec2 operator+( const Vec2& rhs ) const;
	const Vec2& operator+=( const Vec2& rhs );
	Vec2 operator*( float rhs ) const;
	const Vec2& operator*=( float rhs );
	Vec2 operator-( const Vec2& rhs ) const;
	const Vec2& operator-=( const Vec2& rhs );
	Vec2 operator/( float rhs ) const;
	const Vec2& operator/=( float rhs );
	const bool operator==( const Vec2& rhs ) const;
	const bool operator!=( const Vec2& rhs ) const;
	const bool operator>( const Vec2& rhs ) const;
	const bool operator<( const Vec2& rhs ) const;
	const bool operator>=( const Vec2& rhs ) const;
	const bool operator<=( const Vec2& rhs ) const;
	float GetLength() const;
	float GetLengthSq() const;
	explicit operator Vei2() const;

public:
	float x;
	float y;
};