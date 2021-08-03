#pragma once

#include <fstream>
#include <string>
#include "ChiliWin.h"
#include "Colors.h"
#include "RectI.h"

class Surface
{
public:
	Surface() = default;
	Surface( const std::string& p_filename );
	Surface(const int& p_width, const int& p_heigth );
	Surface(const Surface& p_src);
	const Surface& operator=( const Surface& p_rhs );
	~Surface();
	void ReadImageData( std::ifstream& p_file, const BITMAPFILEHEADER p_bmHeader, const BITMAPINFOHEADER& p_bmInfo );
	const Color& GetPixel( const int& p_x, const int& p_y ) const;
	void PutPixel( const int& p_x, const int& p_y, const Color& p_Col );
	const int& GetWidth() const;
	const int& GetHeight() const;
	const RectI GetRect() const;

private:
	int width{};
	int height{};
	Color* pPixels{ nullptr };
};