#pragma once

#include "Character.h"

Character::Character()
	:
	surf( Surface( "Sprites\\link90x90.bmp" ) ),
	dims( 90 ),
	sequences( Sequence::StandingDown ),
	maxHoldTime( 0.16f ),
	speed( maxHoldTime * 1000 )
	
{
	pos = Vec2( float( ( Graphics::ScreenWidth / 2 ) - dims / 2 ), float( ( Graphics::ScreenHeight / 2 ) - dims / 2 ) );

	animations.reserve( int ( Sequence::Count ) );

	for( int i = int( Sequence::StandingLeft ); i < int( Sequence::WalkingLeft ); i++ )
	{
		animations.emplace_back
		( 
			Animation
			( 
				surf, 
				int( Sequence::StandingRight ), 
				maxHoldTime, Vei2( pos ), 
				Vei2{ 0, dims * i }, dims 
			) 
		);

	}

	for( int i = int( Sequence::WalkingLeft ); i < int( Sequence::Count ); i++ )
	{
		animations.emplace_back
		( 
			Animation
			( 
				surf, 
				int( Sequence::WalkingLeft ), maxHoldTime, Vei2( pos ), 
				Vei2{ dims, dims *  ( i - int( Sequence::WalkingLeft ) ) }, 
				dims 
			) 
		);
	}
}

void Character::SetDirection( MainWindow& wnd, Vec2& dir, const float& dt )
{
	if( wnd.kbd.KeyIsPressed( VK_LEFT ) )
	{
		dir.x -= 1.0f;
	}
	else if( wnd.kbd.KeyIsPressed( VK_RIGHT ) )
	{
		dir.x += 1.0f;
	}
	else if( wnd.kbd.KeyIsPressed( VK_UP ) )
	{
		dir.y -= 1.0f;
	}
	else if( wnd.kbd.KeyIsPressed( VK_DOWN ) )
	{
		dir.y += 1.0f;
	}

	pos += ( vel * dt );
}

void Character::SetSequence( Vec2& dir )
{
	if( dir.x < 0.0f )
	{
		sequences = Sequence::WalkingLeft;
	}
	else if( dir.x > 0.0f )
	{
		sequences = Sequence::WalkingRight;
	}
	else if( dir.y < 0.0f )
	{
		sequences = Sequence::WalkingUp;
	}
	else if( dir.y > 0.0f )
	{
		sequences = Sequence::WalkingDown;
	}
	else
	{
		if( vel.x < 0.0f )
		{
			sequences = Sequence::StandingLeft;
		}
		else if( vel.x > 0.0f )
		{
			sequences = Sequence::StandingRight;
		}
		else if( vel.y < 0.0f )
		{
			sequences = Sequence::StandingUp;
		}
		else if( vel.y > 0.0f )
		{
			sequences = Sequence::StandingDown;
		}
	}

	vel = dir * speed;
}

void Character::Update( MainWindow& wnd, Vec2& dir, const float& dt )
{
	SetDirection( wnd, dir, dt );
	SetSequence( dir );
	animations [int( sequences )].Update( Vei2( pos ), dt );
}

void Character::Draw( Graphics& gfx )
{
	animations[int( sequences )].Draw( gfx );
}
