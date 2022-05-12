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

    virtual bool assignFrom(void *pSrc) = 0;
    virtual bool shareFrom(IEntity<TAttrIndex,TAttrName,TAttrSize,TAttrSizeTotal,TEntityInfo> const &entity) = 0;

    virtual bool assignTo(void *pDest) const = 0;
    virtual bool shareTo(IEntityShared<TAttrIndex,TAttrName,TAttrSize,TAttrSizeTotal,TEntityInfo> const &entity) const = 0;
};

};

#endif
