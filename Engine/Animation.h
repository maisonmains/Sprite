#pragma once
#include <vector>
#include "Vec2.h"
#include "Rect.h"
#include "Graphics.h"
#include "Effects.h"

class Animation
{

public:
	Animation
	( 
		Surface& p_surf, 
		const int& frameCount, 
		const float& p_maxHoldTime, 
		const Vei2& p_pos, 
		const Vei2& topLeft, 
		const int& p_dims,
		Effects::VFX& p_effectFlag
	);
	void Draw( Graphics& gfx );
	void DrawCustomClipRegion( Graphics& gfx, const RectI& clipRegion );
	void Update( const Vei2& p_pos, const float& dt );
	void SenseEffect( Effects::VFX& p_effectFlag, const float& dt );

private:
	void AdvanceFrame();

private:
	Surface& surf;
	const int dims{};

	std::vector<RectI> frames{};
	int frameIndex{};
	float heldTime{};
	const float maxHoldTime{};

	Vei2 pos{};

	const float maxEffectTime{};
	float effectTimeLapsed{};

public:
	Effects::VFX& effectState;
};
