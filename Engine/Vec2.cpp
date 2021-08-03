#include "Vec2.h"
#include <cmath>

Vec2::Vec2( float x_in,float y_in )
	:
	x( x_in ),
	y( y_in )
{
}

Vec2::Vec2( const Vec2& src )
{
	x = src.x;
	y = src.y;
}

const Vec2& Vec2::operator=( const Vec2& rhs )
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}

Vec2 Vec2::operator+( const Vec2& rhs ) const
{
	return Vec2( x + rhs.x,y + rhs.y );
}

const Vec2& Vec2::operator+=( const Vec2& rhs )
{
	return *this = *this + rhs;
}

Vec2 Vec2::operator*( float rhs ) const
{
	return Vec2( x * rhs,y * rhs );
}

const Vec2& Vec2::operator*=( float rhs )
{
	return *this = *this * rhs;
}

Vec2 Vec2::operator-( const Vec2& rhs ) const
{
	return Vec2( x - rhs.x,y - rhs.y );
}

const Vec2& Vec2::operator-=( const Vec2& rhs )
{
	return *this = *this - rhs;
}

Vec2 Vec2::operator/( float rhs ) const
{
	return Vec2( x / rhs,y / rhs );
}

const Vec2& Vec2::operator/=( float rhs )
{
	return *this = *this / rhs;
}

const bool Vec2::operator==( const Vec2& rhs ) const
{
	return x == rhs.x && y == rhs.y;
}

const bool Vec2::operator!=( const Vec2& rhs ) const
{
	return !( *this == rhs );
}

const bool Vec2::operator>( const Vec2& rhs ) const
{
	return x > rhs.x && y > rhs.y;
}

const bool Vec2::operator<( const Vec2& rhs ) const
{
	return x < rhs.x && y < rhs.y;
}

const bool Vec2::operator>=( const Vec2& rhs ) const
{
	return rhs.x <= x && rhs.y <= y;
}

const bool Vec2::operator<=( const Vec2& rhs ) const
{
	return rhs.x >= x && rhs.y >= y;
}
float Vec2::GetLength() const
{
	return std::sqrt( float( GetLengthSq() ) );
}

float Vec2::GetLengthSq() const
{
	return x * x + y * y;
}

Vec2::operator Vei2() const
{
	return { int( x ), int ( y ) };
}
