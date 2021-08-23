#pragma once
#include "Animation.h"

Animation::Animation
( 
	Surface& p_surf, 
	const int& frameCount , 
	const float& p_maxHoldTime, 
	const Vei2& p_pos, 
	const Vei2& topLeft, 
	const int& p_dims,
	Effects::VFX& p_effectFlag
)
	:
	surf( p_surf ), 
	dims( p_dims ),
	maxHoldTime( p_maxHoldTime ),
	pos( p_pos ),
	maxEffectTime( p_maxHoldTime * 2.0f ),
	effectState( p_effectFlag )
{
	frames.reserve( frameCount );

	for( int i = 0; i < frameCount; i++ )
	{
		frames.emplace_back
		( 
			RectI
			{ 
				( topLeft.x + ( dims * i ) ), 
				( topLeft.x + ( dims * ( i + 1 ) ) ),
				topLeft.y, topLeft.y + dims
			} 
		);
	}
}

void Animation::Draw( Graphics& gfx )
{
	switch( effectState )
	{

	case Effects::VFX::None:

		gfx.DrawSprite( pos, frames[frameIndex], surf, Effects::Chroma{} );
		break;

	case Effects::VFX::Injury:

		gfx.DrawSprite( pos, frames[frameIndex], surf, Effects::Mask{ Colors::Red } );
		break;

	case Effects::VFX::Transparency:
	/*
	* Placing () after the variable name is a no go.
	* That is interpreted as a member function call,
	* so submiting that as a parameter isnt gonna cut it.
	* Ideally, perform zero/brace initialization, as usual,
	* directly instantiate in the function call or without the call,
	*/
	gfx.DrawSprite( pos, frames [frameIndex], surf, Effects::Transparency{} );
		break;
	}
}

void Animation::DrawCustomClipRegion( Graphics& gfx, const RectI& clipRegion )
{
	switch( effectState )
	{

	case Effects::VFX::None:

		gfx.DrawSprite( pos, clipRegion, frames[frameIndex], surf, Effects::Chroma{} );
		break;

	case Effects::VFX::Injury:

		gfx.DrawSprite( pos, clipRegion, frames[frameIndex], surf, Effects::Mask{ Colors::Red } );
		break;

	case Effects::VFX::Transparency:

		Effects::Transparency t{};

		gfx.DrawSprite( pos, clipRegion, frames[frameIndex], surf, Effects::Transparency{} );
		break;
	}
}

void Animation::Update( const Vei2& p_pos, const float& dt )
{
	heldTime += dt;
	if( heldTime >= maxHoldTime )
	{
		heldTime -= maxHoldTime;
		AdvanceFrame();
	}
	pos = p_pos;

}

void Animation::AdvanceFrame()
{
	if( ++frameIndex > frames.size() - 1 )
	{
		frameIndex = 0;
	}
}

void Animation::SenseEffect( Effects::VFX& p_effectFlag, const float& dt )
{
	switch( p_effectFlag )
	{
	case Effects::VFX::None:
	break;

	case Effects::VFX::Injury:
	case Effects::VFX::Transparency:

		if( effectState == Effects::VFX::None )
		{
			effectState = p_effectFlag;
		}

		effectTimeLapsed += dt;
		if( effectTimeLapsed >= maxEffectTime )
		{
			effectTimeLapsed -= maxEffectTime;
			p_effectFlag = Effects::VFX::None;
			effectState = p_effectFlag;
		}

		break;
	}
}
