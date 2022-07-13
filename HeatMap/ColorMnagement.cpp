#include "pch.h"
#include "ColorMnagement.h"

COLORREF HSLtoRGB(float h, float s, float l)
{
	float r, g, b;
	if (0 == s) {
		r = g = b = l; // achromatic
	}
	else {
		float q = l <= 0.5f ? l * (1 + s) : l + s - l * s;
		float p = 2 * l - q;
		r = HueToRGB(p, q, h + 1.f / 3) * 255;
		g = HueToRGB(p, q, h) * 255;
		b = HueToRGB(p, q, h - 1.f / 3) * 255;
	}
	return RGB(r, g, b);
}

float HueToRGB(float p, float q, float t)
{
	if (t < 0)
		t += 1;
	if (t > 1)
		t -= 1;
	if (t < 1.f / 6)
		return p + (q - p) * 6 * t;
	if (t < 1.f / 2)
		return q;
	if (t < 2.f / 3)
		return p + (q - p) * (2.f / 3 - t) * 6;

	return p;
}
