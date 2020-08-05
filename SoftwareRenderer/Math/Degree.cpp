#include "framework.h"
#include "Degree.h"
#include "Radian.h"

Degree::Degree( float degree )
	: value( degree )
{
}

Degree::Degree( const Radian& radian )
	: value( radian * RadianToDegree )
{
}

Degree::~Degree()
{
}

const float Degree::RadianToDegree = 180.f / PI;