#ifndef CABSCTSTATIC_HPP
#define CABSCTSTATIC_HPP

#include "ICustomType.hpp"

namespace ipgdlib::entity
{

template <typename TSize>
class CAbsCTStatic :
    public ICustomType<TSize>
{
public:
    typename ICustomType<TSize>::eCustomTypeKind getKind() const noexcept override
    {
	    return ICustomType<TSize>::ectkStatic;
    }

    void copyFrom(const void *pSrc)
    {
        std::memcpy(m_pValue,pSrc,this->getTypeSize());
    }

    void copyTo(void *pDest) const
    {
        std::memcpy(pDest,this->m_pValue,this->getTypeSize());
    }

    bool isNull() const noexcept
    {
        return this->m_pValue == nullptr;
    }

    virtual TSize getTypeSize() const noexcept = 0;

protected:
    CAbsCTStatic(void *ptr)
        : m_pValue(ptr)
    {

    }
    const char *getConstPtr() const noexcept
    {
        return this->m_pValue;
    }

    char *getPtr() noexcept
    {
        return this->m_pValue;
    }

private:
    char * m_pValue;

};

};

#endif
