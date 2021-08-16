#include <string>

#include "Vei2.h"
#include "RectI.h"
#include "Graphics.h"
#include "Surface.h"

class Font
{
public:

	Font( const std::string& p_fileName );
	void DrawText( const std::string& p_text, Graphics& p_gfx, const Vei2& p_pos );

private:
	const RectI MapGlyphRect( const char& p_char ) const;

private:

	const Surface glyphSheet{};

	const int glyphWidth{};
	const int glyphHeight{};
	const int nColumns{};
	const int nRows{};
	const char firstGlyph{};
	const char lastGlyph{};
};