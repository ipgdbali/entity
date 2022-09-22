#ifndef IENTITY_UNIQUE_HPP
#define IENTITY_UNIQUE_HPP

#include "wrapper.hpp"
#include "IEntity.hpp"

namespace ipgdlib::entity
{

template <
    typename TFields,
    eWrapper ewFields
>
class IEntityUnique :
	public virtual IEntity<TFields,ewFields>
{
    
};

};

#endif
