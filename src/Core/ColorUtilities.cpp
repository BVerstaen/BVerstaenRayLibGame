#include "ColorUtilities.h"
#include <cmath>
#include <algorithm>


Color ColorUtilities::ColorFromHue(float hue)
{
	hue = std::fmod(hue, 1.0f);
	if (hue < 0.0f) hue += 1.0f;

	Color newColor;

	float r = std::fmod(5 + hue * 6, 6);
	float g = std::fmod(3 + hue * 6, 6);
	float b = std::fmod(1 + hue * 6, 6);

	newColor.r = 255 * (1 - std::max(std::min(std::min(r, 4 - r), 1.0f), 0.0f));
	newColor.g = 255 * (1 - std::max(std::min(std::min(g, 4 - g), 1.0f), 0.0f));
	newColor.b = 255 * (1 - std::max(std::min(std::min(b, 4 - b), 1.0f), 0.0f));

	return newColor;
}