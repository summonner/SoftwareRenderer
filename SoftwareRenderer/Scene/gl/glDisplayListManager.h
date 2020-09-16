#pragma once
#include "glAdapter.h"
#include "glDisplayList.h"

class glDisplayListManager final
{
public:
	glDisplayListManager();
	~glDisplayListManager();

	GLuint Generate( GLsizei range );
	void Delete( GLuint list, GLsizei range );
	void SetBase( GLuint base );
	glDisplayList* Get( GLuint list );
	const std::vector<const glDisplayList*> Get( GLsizei n, GLenum type, const GLvoid* list ) const;

private:
	GLuint base;

	Dictionary<GLuint, glDisplayList> displayLists;
};

