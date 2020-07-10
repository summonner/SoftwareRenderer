#pragma once

class Vector2Int;

class IPrimitive abstract
{
public:
	virtual bool Contains( const Vector2Int& coordinate ) const abstract;
};

