#pragma once


class Vector2Int
{
public:
	Vector2Int( int x, int y )
		: x( x )
		, y( y )
	{
	}

	inline bool operator !=( const Vector2Int& other ) const
	{
		return x != other.x
			|| y != other.y;
	}

	inline Vector2Int operator +( const Vector2Int& other ) const
	{
		return Vector2Int( x + other.x, y + other.y );
	}

	inline Vector2Int operator -( const Vector2Int& other ) const
	{
		return (*this) + other * -1;
	}

	inline Vector2Int operator *( int scalar ) const
	{
		return Vector2Int( x * scalar, y * scalar );
	}

	inline int squaredDistance( const Vector2Int& other ) const
	{
		return ((*this) - other).Dot();
	}

	inline int Dot() const
	{
		return x * x
			 + y * y;
	}

public:
	int x;
	int y;
};