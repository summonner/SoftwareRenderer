#pragma once
class IMouseInputListener abstract
{
public:
	virtual void OnMove( int x, int y ) abstract;
	virtual void OnButton( UINT message ) abstract;
};