#pragma once

namespace Renderer
{
	class IFogFunc abstract
	{
	public:
		virtual ~IFogFunc() {}

		virtual float operator ()( float c ) const abstract;
	};

	namespace FogFunc
	{
		class Linear final : public IFogFunc
		{
		public:
			Linear();
			~Linear() override;

			float operator ()( float c ) const override;

			float start;
			float end;
		};

		class Exp final : public IFogFunc
		{
		public:
			Exp( int exponent );
			~Exp() override;

			float operator ()( float c ) const override;

			float density;

		private:
			float Pow( float c ) const;

		private:
			const int exponent;
		};
	}
}