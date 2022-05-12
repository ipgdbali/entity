#ifndef IENTITY_SHARED_HPP
#define IENTITY_SHARED_HPP

#include "IEntity.hpp"

namespace ipgdlib::entity
{

template <
    typename TEntityInfo,
    typename TEntityInfoWrapper
>
class IEntityShared :
	public virtual IEntity<TEntityInfo,TEntityInfoWrapper>
{
public:

    virtual bool assignFrom(void *pSrc) = 0;
    virtual bool assignTo(void *&pDest) const = 0;

    virtual bool set(void *pSrc,TEntityInfo const *pInfo) = 0;

};

};

#endif
