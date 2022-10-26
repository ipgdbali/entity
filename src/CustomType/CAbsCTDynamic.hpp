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

    bool assignFrom(void *pSrc) noexcept
    {
        *this->m_pValue = pSrc;
    }

    bool assignTo(void **pDest) noexcept
    {
        *pDest = *this->m_pValue;
    }

    bool isNull() const
    {
        return *this->m_pValue == nullptr;
    }

    bool isSet() const noexcept
    {
        return this->m_pValue != nullptr;
    }

protected:
    void *getConstPtr() const
    {
        return *this->m_pValue;
    }

    void *getPtr()
    {
        return *this->m_pValue;
    }

    void _setPtr(void *ptr) override
    {
        this->m_pValue = reinterpret_cast<void**>(ptr);
    }

private:
    void **m_pValue;

};

};

#endif
