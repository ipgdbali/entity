#ifndef IENTITY_SHARED_HPP
#define IENTITY_SHARED_HPP

#include "IEntity.hpp"

namespace ipgdlib::entity
{

template <typename TEntityInfo,eWrapper ewEntityInfo>
class IEntityShared :
	public virtual IEntity<TEntityInfo,ewEntityInfo>
{
public:

    virtual void assignFrom(void *pSrc) = 0;
    virtual void assignTo(void *&pDest) const = 0;

    virtual void set(TEntityInfo const *pInfo,void *pSrc) = 0;

};

};

#endif