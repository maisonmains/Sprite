#pragma once

#include "Colors.h"

class Surface
{
public:
	Surface(const int& p_width, const int& p_heigth );
	Surface(const Surface& p_src);
	const Surface& operator=( const Surface& p_rhs );
	~Surface();
	const Color& GetPixel( const int& p_x, const int& p_y ) const;
	void PutPixel( const int& p_x, const int& p_y, const Color& p_Col );
	const int& GetWidth() const;
	const int& GetHeight() const;

private:
	int width{};
	int height{};
	Color* pPixels{ nullptr };
};