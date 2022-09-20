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

    virtual void set(void *pSrc) = 0;
    virtual bool isNull() const noexcept = 0;
    virtual void clear() noexcept = 0;

};

};

#endif
