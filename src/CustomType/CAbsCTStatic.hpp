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

    virtual void copyFrom(const void *pSrc) = 0;
    virtual void copyTo(void *pDest) const = 0;

};

};

#endif
