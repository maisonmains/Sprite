#pragma once
#include "Animation.h"

Animation::Animation( Surface& p_surf, const int& frameCount , const float& p_maxHoldTime, const Vei2& p_pos, const Vei2& topLeft, const int& p_dims )
	:
	surf( p_surf ), 
	dims( p_dims ),
	maxHoldTime( p_maxHoldTime ),
	pos( p_pos )
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
	gfx.DrawSprite( pos, frames[frameIndex], surf );
}

void Animation::Draw( Graphics& gfx, const RectI& clipRegion )
{
	gfx.DrawSprite( pos, clipRegion, frames[frameIndex], surf );
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
