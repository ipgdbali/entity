#ifndef CCT_FIXED_CSTRING
#define CCT_FIXED_CSTRING

#include "CustomType/CAbsCTStatic.hpp"
#include <cstring>

namespace ipgdlib::entity
{

/**
 *
 * len -> maximum length without null
 *
 **/
template <typename TSize,TSize len>
class CCTFixedCString :
    public CAbsCTStatic<size_t>
{
public:

    constexpr TSize getTypeSize() const noexcept override
    {
	    return len+1;
    }

    TSize getMaxLength()
    {
        return len;
    }

    TSize getLength() const noexcept
    {
	    return this->m_Length;
    }

    void copyTo(void *pDest) const override
    {
        std::strcpy(pDest,this->m_pData);
    }

    void copyFrom(const void *pSrc) override
    {
        std::strncpy_s(this->m_pData,len,pSrc,len-1);
    }

    CCTFixedCString<TSize,len> &operator = (const char* ref)
    {
        this->copyFrom(ref);
        return *this;
    }

    const char &get(TSize index) const
    {
	    return m_pData[index];
    }

private:
    T*          m_pData;
    TIndex      m_Length;
};

};

#endif
