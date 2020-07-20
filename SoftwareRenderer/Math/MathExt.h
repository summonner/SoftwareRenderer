#pragma once

#define PI       3.141592f


inline float Lerp( float a, float b, float t )
{
	return a * (1.f - t) + b * t;
}