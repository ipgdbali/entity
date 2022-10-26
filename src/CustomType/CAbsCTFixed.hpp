#ifndef CABSCTFIXED_HPP
#define CABSCTFIXED_HPP

#include "ICustomType.hpp"

namespace ipgdlib::entity
{

template <typename TSize>
class CAbsCTFixed :
    public CAbsCustomType<TSize>
{
public:
    CAbsCTFixed()
        : m_pValue(nullptr)
    {
        
    }

    typename ICustomType<TSize>::eCustomTypeKind getKind() const noexcept override
    {
	    return ICustomType<TSize>::ectkStatic;
    }

    virtual void copyFrom(const void *pSrc)
    {
        std::memcpy(this->getPtr(),pSrc,this->getTypeSize());
    }

    virtual void copyTo(void *pDest) const
    {
        std::memcpy(pDest,this->getConstPtr(),this->getTypeSize());
    }

    bool isSet() const noexcept override
    {
        return this->m_pValue != nullptr;
    }

    virtual constexpr TSize getTypeSize() const noexcept = 0;

protected:
    CAbsCTFixed(void *ptr) 
        : m_pValue(ptr)
    {
    }

    char *getConstPtr() const
    {
        return this->m_pValue;
    }

    char *getPtr()
    {
        return this->m_pValue;
    }

    void _setPtr(void *ptr) override
    {
        this->m_pValue = reinterpret_cast<char*>(ptr);
    }

private:
    char *m_pValue;
};

};

#endif