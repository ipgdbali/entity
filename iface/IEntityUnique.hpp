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
};

};

#endif
