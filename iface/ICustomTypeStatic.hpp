#ifndef ICUSTOM_TYPE_STATIC_HPP
#define ICUSTOM_TYPE_STATIC_HPP

#include "ICustomType.hpp"

namespace ipgdlib::entity
{

template <typename TSize>
class ICustomTypeStatic :
    public ICustomType<TSize>
{
public:
    virtual void copyFrom(const void *pSrc) = 0;
    virtual void copyTo(void *pDest) const = 0;

    typename ICustomType<TSize>::eCustomTypeKind getKind() const noexcept override
    {
	return ICustomType<TSize>::ectkStatic;
    }

};

};

#endif
