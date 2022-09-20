#ifndef CCT_PRIMITIVE
#define CCT_PRIMITIVE

#include "CustomType/CAbsCTStatic.hpp"
#include <cstring>

namespace ipgdlib::entity
{

template <typename T,typename TSize>
class CCTPrimitive :
    public CAbsCTStatic<TSize>
{
static_assert(std::is_arithmetic<T>::value);

public:
    constexpr static TSize size = sizeof(T);

    TSize getTypeSize() const noexcept override
    {
	    return size;
    }

    void copyTo(void *pDest) const override
    {
	    std::memcpy(pDest,this->m_pData,size);
    }

    void copyFrom(const void *pSrc) override
    {
	    std::memcpy(m_pData,pSrc,size);
    }

    void setPtr(void *pSrc)
    {
	    this->m_pData = static_cast<T*>(pSrc);
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
