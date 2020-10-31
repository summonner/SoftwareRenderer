// Code writen by: Vic Hollis 09/07/2003
// I don't mind if you use this class in your own code. All I ask is 
// that you give me credit for it if you do.  And plug NeHe while your
// at it! :P  
//////////////////////////////////////////////////////////////////////
// glPoint.h: interface for the glPoint class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLPOINT_H__ADADC708_0176_471A_8241_5DD4D700BCB2__INCLUDED_)
#define AFX_GLPOINT_H__ADADC708_0176_471A_8241_5DD4D700BCB2__INCLUDED_

#include "Scene/gl/glAdapter.h"
#include "glVector.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class glPoint  
{
public:
	void operator+=(glPoint p);
	glPoint operator+(glPoint p);
	glVector operator-(glPoint p);
	void operator =(glVector v);
	void operator =(glPoint p);
	glPoint();
	virtual ~glPoint();

	GLfloat z;
	GLfloat y;
	GLfloat x;
};

#endif // !defined(AFX_GLPOINT_H__ADADC708_0176_471A_8241_5DD4D700BCB2__INCLUDED_)
