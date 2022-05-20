#ifndef IENTITY_UNIQUE_HPP
#define IENTITY_UNIQUE_HPP

#include "wrapper.hpp"
#include "IEntity.hpp"

namespace ipgdlib::entity
{

template <
    typename TEntityInfo,
    eWrapper ewEntityInfo
>
class IEntityUnique :
	public virtual IEntity<TEntityInfo,ewEntityInfo>
{
public:
    virtual bool createFrom(TEntityInfo const &entityInfo) = 0;
    virtual bool createFrom(IEntity<TEntityInfo,ewEntityInfo> const &entity) = 0;
};

};

#endif
