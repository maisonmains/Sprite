#pragma once

#include "Colors.h" 
#include "Graphics.h"

namespace Effects
{
	class Copy
	{
	public:
		void operator()( Graphics& gfx, const int& xPos, const int& yPos, const Color& src ) const
		{
			gfx.PutPixel( xPos, yPos, src );
		}
	};

	class Chroma
	{
	public:

		Chroma() = default;

		Chroma( Color p_chroma )
			:
			chroma( p_chroma )
		{

		}

		void operator()( Graphics& gfx, const int& xPos, const int& yPos, const Color& src ) const
		{
			if( src != chroma )
			{
				gfx.PutPixel( xPos, yPos, src );
			}
		}

	private:

		Color chroma{ Colors::Magenta };
	};

	class Mask
	{
	public:

		Mask( Color p_mask )
			:
			mask( p_mask )
		{}

		Mask( Color p_mask, Color p_chroma )
			:
			mask( p_mask ),
			chroma( p_chroma )
		{}

		void operator()( Graphics& gfx, const int& xPos, const int& yPos, const Color& src ) const
		{
			if( src != chroma )
			{
				gfx.PutPixel( xPos, yPos, mask );
			}
		}

	private:

		Color mask{};
		Color chroma{ Colors::Magenta };
	};

	class Transparency
	{
	public:
		Transparency() = default;
		Transparency( Color p_chroma )
			:
			chroma( p_chroma )
		{

		}

		void operator()( Graphics& gfx, const int& xPos, const int& yPos, const Color& src ) const
		{
			if( src != chroma )
			{
				Color background = gfx.GetPixel( xPos, yPos );

				Color avg
				(
					unsigned char( ( background.GetR() + src.GetR() ) / 2 ),
					unsigned char( ( background.GetG() + src.GetG() ) / 2 ),
					unsigned char( ( background.GetB() + src.GetB() ) / 2 )
				);

				gfx.PutPixel( xPos, yPos, avg );
			}
		}

	private:

		Color chroma{ Colors::Magenta };
	};
}