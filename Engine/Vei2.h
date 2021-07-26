#pragma once

class Vei2
{
public:
	Vei2() = default;
	Vei2( int x_in,int y_in );
	Vei2( const Vei2& src );
	const Vei2& operator=( const Vei2& rhs );
	Vei2 operator+( const Vei2& rhs ) const;
	const Vei2& operator+=( const Vei2& rhs );
	Vei2 operator*( int rhs ) const;
	const Vei2& operator*=( int rhs );
	Vei2 operator-( const Vei2& rhs ) const;
	const Vei2& operator-=( const Vei2& rhs );
	Vei2 operator/( int rhs ) const;
	const Vei2& operator/=( int rhs );
	const bool operator==( const Vei2& rhs ) const;
	const bool operator!=( const Vei2& rhs ) const;
	const bool operator>( const Vei2& rhs ) const;
	const bool operator<( const Vei2& rhs ) const;
	const bool operator>=( const Vei2& rhs ) const;
	const bool operator<=( const Vei2& rhs ) const;
	float GetLength() const;
	int GetLengthSq() const;
public:
	int x;
	int y;
};