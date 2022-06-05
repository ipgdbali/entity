#ifndef CCT_STATIC_PRIMITIVE
#define CCT_STATIC_PRIMITIVE

#include "ICustomTypeStatic.hpp"
#include <cstring>

namespace ipgdlib::entity
{

template <typename T,typename TSize>
class CCTStaticPrimitive :
    public ICustomTypeStatic<TSize>
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

    CCTStaticPrimitive<T,TSize> &operator = (const T& ref)
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
    T *m_pData;
};

};

#endif
