#ifndef IENTITY_UNIQUE_HPP
#define IENTITY_UNIQUE_HPP

#include "IEntity.hpp"

namespace ipgdlib::entity
{

template <
    typename TEntityInfo,
    typename TEntityInfoWrapper // pointer, reference, shared or what
>
class IEntityUnique :
	public virtual IEntity<TEntityInfo,TEntityInfoWrapper>
{
public:
    virtual bool createFrom(TEntityInfo const &entityInfo) = 0;
    virtual bool createFrom(IEntity<TEntityInfo,TEntityInfoWrapper> const &entity) = 0;
};

};

#endif
