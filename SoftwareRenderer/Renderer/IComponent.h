#pragma once

namespace Renderer
{
	class IComponent abstract
	{
	public:
		virtual ~IComponent() {}

		virtual void SetEnable( const bool enable ) abstract;
		virtual bool IsEnable() const abstract;
		virtual void Reset() abstract;
	};

	class BaseComponent abstract : public IComponent
	{
	public:
		BaseComponent()
			: enabled( false )
		{
		}

		virtual ~BaseComponent() override {}

		inline void SetEnable( const bool enable ) override
		{
			enabled = enable;
		}

		inline bool IsEnable() const override
		{
			return enabled;
		}

		virtual void Reset() override
		{
			enabled = false;
		}

	protected:
		bool enabled;
	};
}