#pragma once

template<class DerivedIterator, class ReturnType>
class IBaseIterator abstract
{
	virtual bool operator !=( const DerivedIterator& other ) const abstract;
	virtual const DerivedIterator& operator ++() abstract;
	virtual ReturnType operator *() const abstract;
};
