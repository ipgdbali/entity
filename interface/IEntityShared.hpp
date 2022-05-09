#ifndef IENTITY_SHARED_HPP
#define IENTITY_SHARED_HPP

#include "IEntity.hpp"

namespace ipgdlib::entity
{

template <
    typename TAttrName,		
    typename TAttrIndex,			
    typename TAttrSize,
    typename TAttrSizeTotal,
    typename TEntityInfo
>
class IEntityShared :
	public virtual IEntity<TAttrName,TAttrIndex,TAttrSize,TAttrSizeTotal,TEntityInfo>
{
public:
    virtual bool shareFrom(IEntity<TAttrIndex,TAttrName,TAttrSize,TAttrSizeTotal,TEntityInfo> const &pEntity) = 0;
    virtual bool shareTo(IEntity<TAttrIndex,TAttrName,TAttrSize,TAttrSizeTotal,TEntityInfo> const &pEntity) = 0;
};

};

#endif
