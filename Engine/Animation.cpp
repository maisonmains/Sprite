#pragma once
#include "Animation.h"

Animation::Animation( Surface& p_surf, const int& frameCount , const float& p_maxHoldTime, const Vei2& p_pos, const Vei2& topLeft, const int& p_dims )
	:
	surf( p_surf ), 
	dims( p_dims ),
	maxHoldTime( p_maxHoldTime ),
	pos( p_pos ),
	maxEffectTime( p_maxHoldTime * 2.0f )
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
	if( effectState )
	{
		gfx.DrawMaskedSprite( pos, frames [frameIndex], surf, Colors::Red );
	}
	else
	{
		gfx.DrawFadedSprite( pos, frames [frameIndex], surf );
	}
}

void Animation::Draw( Graphics& gfx, const RectI& clipRegion )
{
	if( effectState )
	{
		gfx.DrawMaskedSprite( pos, clipRegion, frames[frameIndex], surf, Colors::Red );
	}
	else
	{
		gfx.DrawFadedSprite( pos, clipRegion, frames [frameIndex], surf );
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
	if( frameIndex++ >= frames.size() - 1 )
	{
		frameIndex = 0;
	}
}

void Animation::ActivateEffect( bool& p_effectFlag, const float& dt )
{
	if( p_effectFlag )
	{
		effectState = true;

		effectTimeLapsed += dt;
		if( effectTimeLapsed >= maxEffectTime )
		{
			effectTimeLapsed -= maxEffectTime;
			effectState = false;
			p_effectFlag = false;
		}
	}
}
