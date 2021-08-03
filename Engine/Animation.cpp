#pragma once
#include "Animation.h"

Animation::Animation( const int frameCount, const Vei2& topLeft )
	:
	dimensions( 90 ),
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

void Animation::Update( const float dt )
{
	heldTime += dt;
	if( heldTime >= maxHoldTime )
	{
		heldTime -= maxHoldTime;
		AdvanceFrame();
	}
}

void Animation::AdvanceFrame()
{
	frameIndex++;
}
