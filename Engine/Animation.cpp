#pragma once
#include "Animation.h"

Animation::Animation( Surface& p_surf, const int frameCount , const float p_maxHoldTime, const Vei2& topLeft )
	:
	surf( p_surf ), 
	dimensions( 90 ),
	maxHoldTime( p_maxHoldTime ),
	pos( pos )
{
	frames.reserve( frameCount );

	for( int i = 0; i < frameCount; i++ )
	{
		frames.emplace_back
		( 
			RectI
			{ 
				( topLeft.x + ( dimensions * i ) ), 
				( topLeft.x + ( dimensions * ( i + 1 ) ) ),
				topLeft.y, topLeft.y + dimensions
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
	gfx.DrawSprite( pos, clipRegion, frames [frameIndex], surf );
}

void Animation::Update( const Vei2& p_pos, const float dt )
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
