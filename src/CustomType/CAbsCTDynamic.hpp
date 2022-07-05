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

    virtual bool assignFrom(void *pSrc) = 0;
    virtual bool assignTo(void *&pDest) = 0;

    virtual bool clear() = 0; // set to Null
    virtual bool isNull() const noexcept = 0;

};

};

#endif
