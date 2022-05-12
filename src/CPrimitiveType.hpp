#ifndef CPRIMITIVE_TYPE_HPP
#define CPRIMITIVE_TYPE_HPP

#include "ICustomType.hpp"

namespace ipgdlib::entity
{

template <
    typename T,
    typename TSize
    >
class CPrimitiveType :
    public ICustomType<TSize>
{
    public:
	CPrimitiveType() : m_pValue(nullptr)
	{
	}

	virtual ~CPrimitiveType()
	{
	    this->m_pValue = nullptr;
	}

	TSize getTypeSize() const override
	{
	    return sizeof(T);
	}

	bool set(void *ptr) override
	{
	    if(ptr != nullptr)
	    {
		this->m_pValue = (T*)(ptr);
		return true;
	    }
	    else
		return false;
	}

	CPrimitiveType<T,TSize> &operator = (const T &ref)
	{
	    *(this->m_pValue) = ref;
	    return *this;
	}

	operator T()
	{
	    return *this->m_pValue;
	}

    private:
	T* m_pValue;
};
    
};

#endif
