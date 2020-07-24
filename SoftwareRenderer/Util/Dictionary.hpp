#pragma once
template< typename Key, typename Value >
class Dictionary final
{
public:
	Dictionary()
	{
	}

	Dictionary( std::initializer_list<std::pair<const Key, Value>> records )
		: Dictionary( records, nullptr )
	{
	}

	Dictionary( std::initializer_list<std::pair<const Key, Value>> records, const Value defaultValue )
		: records( records )
		, defaultValue( defaultValue )
	{
	}

	const Value& operator []( const Key& key ) const
	{
		if ( const auto& found{ records.find( key ) }; found != records.end() )
		{
			return found->second;
		}
		else
		{
			return defaultValue;
		}
	}

	Value& operator []( const Key& key )
	{
		if ( const auto& found{ records.find( key ) }; found != records.end() )
		{
			return found->second;
		}
		else
		{
			return records[key] = defaultValue;
		}
	}

	bool Contains( const Key& key ) const
	{
		return records.find( key ) != records.end();
	}

	bool Add( const Key& key, const Value& value )
	{
		auto ret = records.insert( std::pair( key, value ) );
		return ret.second;
	}

	bool Remove( const Key& key )
	{
		return records.erase( key ) > 0;
	}

	void Clear()
	{
		records.clear();
	}

private:
	std::unordered_map<Key, Value> records;
	const Value defaultValue;
};

