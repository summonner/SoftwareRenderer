#pragma once
#include "glAdapter.h"

class glSelectMode
{
public:
	glSelectMode();
	~glSelectMode();

	int SetEnable( bool enable );
	bool IsEnabled() const;

	void SetBuffer( GLsizei size, GLuint* buffer );

	void InitNames();
	void PushName( GLuint name );
	void PopName();
	void LoadName( GLuint name );

	void OnRasterize( const Renderer::IRasterizer& rasterizer, const Bounds& bounds );

private:
	void ResetRecord();

private:
	bool enabled;
	std::stack<GLuint> nameStack;


	class HitRecord
	{
	public:
		void Reset();
		void Hit( const std::stack<GLuint>& stack, const std::pair<float, float>& range );
		bool IsHit() const;

	private:
		GLuint numStack{ 0 };
		GLuint near{ UINT_MAX };
		GLuint far{ 0 };
		GLuint name{ 0 };
	};
	HitRecord record;

	class Buffer
	{
	public:
		Buffer( GLsizei size, GLuint* buffer );
		int Reset();
		void Push( const HitRecord& record );

	private:
		GLuint* container;
		GLsizei maxSize;
		int current;
	};
	Buffer buffer;
};

