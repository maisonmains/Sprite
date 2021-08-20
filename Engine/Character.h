#pragma once

#include "MainWindow.h"
#include "Keyboard.h"
#include "Animation.h"
#include "Vec2.h"

class Character
{
private:
	enum class Sequence
	{
		StandingLeft,
		StandingRight,
		StandingUp,
		StandingDown,
		WalkingLeft,
		WalkingRight,
		WalkingUp,
		WalkingDown,
		Count
	};

public:
	Character( const std::string& p_fileName );
	void Update( MainWindow& wnd, Vec2& dir, const float& dt );
	void Draw( Graphics& gfx );
	void SetDirection( MainWindow& wnd, Vec2& dir );
	void SetSequence( Vec2& dir, const float& dt );

private:
	Surface surf{};
	const int dims{};

	Sequence sequences{};
	std::vector<Animation> animations{};
	const float maxHoldTime{};

	Vec2 pos{};
	Vec2 vel{};
	const float speed{ };
	
	bool effectInjury{};
};