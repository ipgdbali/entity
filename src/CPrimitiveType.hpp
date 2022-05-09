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
    public ICustomType<TSize,TPtr>
{
    public:

	static TSize size() const noexcept
	{
	    return sizeof(TSize);
	}

	bool set(TSize size,void *ptr) override
	{
	    if(size == size())
	    {
		this->m_pValue = ptr;
		return true;
	    }
	    else
		return false;

	}

	T &val()
	{
	    return *m_pValue;
	}

    private:
	T* m_pValue;
}
    
};

#endif
