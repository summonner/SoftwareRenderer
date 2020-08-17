#pragma once

#define PI       3.14159265358979323846f


inline float Lerp( float a, float b, float t )
{
	return a * (1.f - t) + b * t;
}