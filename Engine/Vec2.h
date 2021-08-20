#pragma once
#include <cmath>

template <typename T>
class Vec2_
{
public:

	Vec2_() = default;

	Vec2_( T x_in, T y_in )
		:
		x( x_in ),
		y( y_in )
	{
	}

	Vec2_( const Vec2_& src )
		:
		x( src.x ),
		y( src.y )
	{
	}

	template <typename S>
	Vec2_( const Vec2_<S>& src )
		:
		x( ( T ) src.x ),
		y( ( T ) src.y )
	{
	}

	const Vec2_& operator=( const Vec2_& rhs )
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	Vec2_ operator+( const Vec2_& rhs ) const
	{
		return Vec2_( x + rhs.x, y + rhs.y );
	}

	const Vec2_& operator+=( const Vec2_& rhs )
	{
		return *this = *this + rhs;
	}

	Vec2_ operator*( T rhs ) const
	{
		return Vec2_( x * rhs, y * rhs );
	}

	const Vec2_& operator*=( T rhs )
	{
		return *this = *this * rhs;
	}

	Vec2_ operator-( const Vec2_& rhs ) const
	{
		return Vec2_( x - rhs.x, y - rhs.y );
	}

	const Vec2_& operator-=( const Vec2_& rhs )
	{
		return *this = *this - rhs;
	}

	Vec2_ operator/( T rhs ) const
	{
		return Vec2_( x / rhs, y / rhs );
	}

	const Vec2_& operator/=( T rhs )
	{
		return *this = *this / rhs;
	}

	const bool operator==( const Vec2_& rhs ) const
	{
		return x == rhs.x && y == rhs.y;
	}

	const bool operator!=( const Vec2_& rhs ) const
	{
		return !( *this == rhs );
	}

	const bool operator>( const Vec2_& rhs ) const
	{
		return x > rhs.x && y > rhs.y;
	}

	const bool operator<( const Vec2_& rhs ) const
	{
		return x < rhs.x&& y < rhs.y;
	}

	const bool operator>=( const Vec2_& rhs ) const
	{
		return rhs.x <= x && rhs.y <= y;
	}

	const bool operator<=( const Vec2_& rhs ) const
	{
		return rhs.x >= x && rhs.y >= y;
	}

	T GetLength() const
	{
		return ( T )std::sqrt( T( GetLengthSq() ) );
	}

	T GetLengthSq() const
	{
		return x * x + y * y;
	}

	T Normalize()
	{
		return *this = GetNormalized();
	}

	T GetNormalized()
	{
		const T length = GetLength();

		if( length > (T)0 )
		{
			return *this * ( (T)1 / length );
		}

		return *this;
	}

public:
	T x;
	T y;
};

typedef Vec2_<float> Vec2;
typedef Vec2_<int> Vei2;