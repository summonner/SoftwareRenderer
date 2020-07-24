#pragma once
class StlMapExtension final abstract
{
public:
	template< typename T, typename U >
	static U Find( const std::map<T, U>& map, const T& key, U defaultValue )
	{
		if ( const auto& found { map.find( key ) }; found != map.end() )
		{
			return found->second;
		}
		else
		{
			return defaultValue;
		}
	}
};

