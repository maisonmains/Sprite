#include "Font.h"
#include "assert.h"

Font::Font( const std::string& p_fileName )
	:
	glyphSheet( Surface( p_fileName ) ),
	glyphWidth( 16 ),
	glyphHeight( 28 ),
	nColumns( glyphSheet.GetWidth() / glyphWidth ),
	nRows( glyphSheet.GetHeight() / glyphHeight ),
	firstGlyph( ' ' ),
	lastGlyph( '~' )
{

}

void Font::DrawText( const std::string& p_text, Graphics& p_gfx, const Vei2& p_pos )
{
	Vei2 ogPos{ p_pos };
	Vei2 curPos{ ogPos };
	Effects::Mask mask( Colors::White, Colors::White );

	const char* c{ p_text.data() };
	
	for( int i = 0; i < p_text.length(); c ++, i++ )
	{	
		if( *c == ' ' )
		{
			curPos.x += glyphWidth;
		}
		else if( *c != '\n' )
		{
			p_gfx.DrawSprite( curPos, p_gfx.GetScreenRect(), MapGlyphRect( *c ), glyphSheet, mask );
			curPos.x += glyphWidth;
		}
		else
		{
			curPos = ogPos;
			curPos.y += glyphHeight;
		}
	}
}

const RectI Font::MapGlyphRect( const char& p_char ) const
{
	assert( p_char >= ( firstGlyph + 1 ) && p_char <= lastGlyph );

	int targetX = ( ( p_char - firstGlyph ) % nColumns );
	int targetY = ( ( p_char - firstGlyph ) / nColumns );

	targetX *= glyphWidth;
	targetY *= glyphHeight;

	assert
	(
		targetX >= 0 && targetX < glyphSheet.GetWidth() &&
		targetY >= 0 && targetY < glyphSheet.GetHeight()
	);

	return
		(
			RectI
			(
				targetX,
				targetX + glyphWidth,
				targetY,
				targetY + glyphHeight
			)
		);
}