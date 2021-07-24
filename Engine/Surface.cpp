#include "Surface.h"
#include <assert.h>

Surface::Surface( const std::string& p_filename )
{
	std::ifstream file( p_filename, std::ios::binary );
	file.seekg( 0, std::ios::beg );

	BITMAPFILEHEADER bmHeader;
	file.read( reinterpret_cast< char* >( &bmHeader ), sizeof( bmHeader ) );

	BITMAPINFOHEADER bmInfo;
	file.read( reinterpret_cast< char* >( &bmInfo ), sizeof( bmInfo ) );

	assert( bmInfo.biCompression == BI_RGB || bmInfo.biCompression == BI_BITFIELDS );
	assert( bmInfo.biBitCount == 24 || bmInfo.biBitCount == 32 );

	ReadImageData( file, bmHeader, bmInfo );
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

void Surface::ReadImageData( std::ifstream& p_file, const BITMAPFILEHEADER p_bmHeader, const BITMAPINFOHEADER& p_bmInfo )
{
	assert( pPixels == nullptr, "This surface is already populated asshole.");

	width = p_bmInfo.biWidth;
	height = p_bmInfo.biHeight;
	/*
	* Since positive bitHeight == read data bottom to top,
	* negative height == top to bottom, thus, we'll need to 
	* convert height back to positive value here in that case.
	*/
	if( height < 0 )
	{
		height *= -1;
	}
	pPixels = new Color [width * height];

	//Seek to where the image data begins in the file
	p_file.seekg( p_bmHeader.bfOffBits, std::ios::beg );

	//Padding should adjust dynamically with bit count.
	const int padding = ( 4 - ( width * ( p_bmInfo.biBitCount ) ) % 4 ) % 4;

	//In the event of bottom->top ordered data
	if( p_bmInfo.biHeight > 0 )
	{
		for( int y{ height - 1 }; y >= 0; y-- )
		{
			//Non-4 byte data 
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
				//4 byte data
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
	//In the event of top->bottom ordered data
	else
	{
		for( int y{}; y < height; y++ )
		{
			if( padding > 0 )
			{
				//Non-4 byte data 
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
				//4 byte data
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