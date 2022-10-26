#ifndef CABSCTDYNAMIC_HPP
#define CABSCTDYNAMIC_HPP

#include "ICustomType.hpp"

namespace ipgdlib::entity
{

template <typename TSize>
class CAbsCTDynamic :
    public ICustomType<TSize>
{

public:
    typename ICustomType<TSize>::eCustomTypeKind getKind() const noexcept override
    {
	    return ICustomType<TSize>::ectkDynamic;
    }

    bool assignFrom(void **pSrc) noexcept
    {
        this->m_pValue = pSrc;
    }

    bool assignTo(void **pDest) noexcept
    {
        *pDest = *this->m_pValue;
    }

    bool isNull() const noexcept
    {
        return *this->m_pValue == nullptr;
    }

protected:
    char *getPtr() noexcept
    {
        return *this->m_pValue;
    }

    virtual bool setPtr(void **ptr)
    {
        this->m_pValue = ptr;
        return true;
    }

private:
    char **m_pValue;

};

};

#endif
