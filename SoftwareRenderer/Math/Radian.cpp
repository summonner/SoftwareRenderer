#include "framework.h"
#include "Radian.h"
#include "Degree.h"

Radian::Radian( float radian )
	: value( radian )
{
}

Radian::Radian( const Degree& degree )
	: value( degree * DegreeToRadian )
{
}

Radian::~Radian()
{
}

const float Radian::DegreeToRadian = PI / 180.f;