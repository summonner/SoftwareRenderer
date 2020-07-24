#pragma once
template< typename T, typename U >
class Dictionary final
{
public:
	Dictionary( std::initializer_list<std::pair<const T, U>> records )
		: Dictionary( records, nullptr )
	{
	}

	Dictionary( std::initializer_list<std::pair<const T, U>> records, const U defaultValue )
		: records( records )
		, defaultValue( defaultValue )
	{
	}

	const U& operator []( const T& key ) const
	{
		if ( const auto& found { records.find( key ) }; found != records.end() )
		{
			return found->second;
		}
		else
		{
			return defaultValue;
		}
	}

private:
	std::unordered_map<T, U> records;
	const U defaultValue;
};

