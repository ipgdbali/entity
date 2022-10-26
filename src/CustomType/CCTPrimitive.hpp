#ifndef CCT_PRIMITIVE
#define CCT_PRIMITIVE

#include "CustomType/CAbsCTStatic.hpp"
#include <cstring>

namespace ipgdlib::entity
{

template <typename T,typename TSize = size_t>
class CCTPrimitive :
    public CAbsCTStatic<TSize>
{
static_assert(std::is_arithmetic<T>::value);

public:
    constexpr TSize getTypeSize() const noexcept override
    {
	    return sizeof(T);
    }

    CCTPrimitive<T,TSize> &operator = (const T& ref)
    {
        *this->m_pData = ref;
        return *this;
    }

    operator const T&() const
    {
	    return *this->m_pData;
    }

    operator T&()
    {
	    return *this->m_pData;
    }

private:
    T*      m_pData;
};

};

#endif
