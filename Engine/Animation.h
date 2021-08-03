#pragma once
#include <vector>
#include "Vei2.h"
#include "RectI.h"
#include "Graphics.h"

class Animation
{
public:
	Animation( Surface& p_surf, const int& frameCount, const float& p_maxHoldTime, const Vei2& p_pos, const Vei2& topLeft, const int& p_dims );
	void Draw( Graphics& gfx );
	void Draw( Graphics& gfx, const RectI& clipRegion );
	void Update( const Vei2& p_pos, const float& dt );

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
};
