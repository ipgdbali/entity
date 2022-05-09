#ifndef IENTITY_UNIQUE_HPP
#define IENTITY_UNIQUE_HPP

#include "IEntity.hpp"

namespace ipgdlib::entity
{

template <
    typename TAttrIndex,			
    typename TAttrName,		
    typename TAttrSize,
    typename TAttrSizeTotal,
    typename TEntityInfo,
    typename TEntityInfoWrapper
>
class IEntityUnique :
	public virtual IEntity<TAttrName,TAttrIndex,TAttrSize,TAttrSizeTotal,TEntityInfoWrapper>
{
public:
    virtual bool createFrom(TEntityInfo const &entityInfo) = 0;
    virtual bool createFrom(IEntity<TAttrIndex,TAttrName,TAttrSize,TAttrSizeTotal,TEntityInfoWrapper> const &entity) = 0;
};

};

#endif
