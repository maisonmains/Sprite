#pragma once
#include <vector>
#include "RectI.h"
#include "Graphics.h"
#include "Vei2.h"

class Animation
{
public:
	Animation( Surface& p_surf, const int frameCount, const float p_maxHoldTime, const Vei2& topLeft );
	void Draw( Graphics& gfx );
	void Draw( Graphics& gfx, const RectI& clipRegion );
	void Update( const Vei2& p_pos, const float dt );

private:
	void AdvanceFrame();

private:
	Surface& surf;
	const int dimensions{};

	std::vector<RectI> frames{};
	int frameIndex{};
	float heldTime{};
	const float maxHoldTime{};

	Vei2 pos{};
};
