#include "Surface.h"
#include <assert.h>

Surface::Surface( const std::string& p_filename )
{
	std::ifstream file( p_filename, std::ios::binary );
	file.seekg( 0, std::ios::beg );

	BITMAPFILEHEADER bmHeader;
	file.read( reinterpret_cast<char*>( &bmHeader ), sizeof( bmHeader ) );

	BITMAPINFOHEADER bmInfo;
	file.read( reinterpret_cast<char*>( &bmInfo ), sizeof( bmInfo ) );

	assert( bmInfo.biCompression == BI_RGB || bmInfo.biCompression == BI_BITFIELDS );
	assert( bmInfo.biBitCount == 24 || bmInfo.biBitCount == 32 );

	width = bmInfo.biWidth;
	height = bmInfo.biHeight;
	pPixels = new Color [width * height];

	file.seekg( bmHeader.bfOffBits, std::ios::beg );

	ReadImageData( file, bmInfo );
}

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

void Surface::ReadImageData( std::ifstream& p_file, const BITMAPINFOHEADER& p_bmInfo )
{
	const int padding = ( 4 - ( width * ( p_bmInfo.biBitCount ) ) % 4 ) % 4;

	if( p_bmInfo.biHeight > 0 )
	{
		for( int y{ height - 1 }; y >= 0; y-- )
		{
			if( padding > 0 )
			{
				for( int x{}; x < width; x++ )
				{
					const int b{ p_file.get() };
					const int g{ p_file.get() };
					const int r{ p_file.get() };

					PutPixel( x, y, Color( r, g, b ) );
				}
				p_file.seekg( padding, std::ios::cur );
			}
			else
			{
				for( int x{}; x < width; x++ )
				{
					const int a{ p_file.get() };
					const int b{ p_file.get() };
					const int g{ p_file.get() };
					const int r{ p_file.get() };

					PutPixel( x, y, Color( r, g, b, a ) );
				}
			}
		}
	}
	else
	{
		for( int y{}; y < height; y++ )
		{
			if( padding > 0 )
			{
				for( int x{}; x < width; x++ )
				{
					const int b{ p_file.get() };
					const int g{ p_file.get() };
					const int r{ p_file.get() };

					PutPixel( x, y, Color( r, g, b ) );
				}
				p_file.seekg( padding, std::ios::cur );
			}
			else
			{
				for( int x{}; x < width; x++ )
				{
					const int a{ p_file.get() };
					const int b{ p_file.get() };
					const int g{ p_file.get() };
					const int r{ p_file.get() };

					PutPixel( x, y, Color( r, g, b, a ) );
				}
			}
		}
	}
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