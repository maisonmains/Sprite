#include "Surface.h"

Surface::Surface( const int& p_width, const int& p_height )
	:
	width(p_width),
	height(p_height),
	pPixels( new Color[width * height] )
{

}

Surface::Surface( const Surface& p_src )
	: Surface( p_src.width, p_src.height )
{
	delete [] pPixels;
	
	const size_t size = width * height;
	pPixels = new Color[size];

	for( size_t i{ 0 }; i < size; i++ )
	{
		pPixels [i] = p_src.pPixels [i];
	}
}

const Surface& Surface::operator= ( const Surface& p_rhs )
{
	width = p_rhs.width;
	height = p_rhs.height;

	delete [] pPixels;
	
	const size_t size = width * height;
	pPixels = new Color [size];

	for( size_t i{ 0 }; i < size; i++ )
	{
		pPixels [i] = p_rhs.pPixels [i];
	}

	return *this;
}

Surface::~Surface()
{
	delete [] pPixels;
	pPixels = nullptr;
}

const Color& Surface::GetPixel( const int& p_x, const int& p_y ) const
{
	return pPixels [( p_y * width ) + p_x];
}

void Surface::PutPixel( const int& p_x, const int& p_y, const Color& p_Col )
{
	pPixels [( p_y * width ) + p_x] = p_Col;
}

const int& Surface::GetWidth() const
{
	return width;
}

const int& Surface::GetHeight() const
{
	return height;
}