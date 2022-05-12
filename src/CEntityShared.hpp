#ifndef CENTITY_SHARED_HPP
#define CENTITY_SHARED_HPP

#include "IEntityShared.hpp"
#include "CEntity.hpp"

namespace ipgdlib::entity
{

template <
    typename TAttrName,		
    typename TAttrIndex,			
    typename TAttrSize,
    typename TAttrSizeTotal
>
class CEntityShared :
    public CEntity<TAttrName,TAttrIndex,TAttrSize,TAttrSizeTotal>
    public virtual IEntityShared
{
public:
    bool shareFrom(IEntity const &entity) override
    {
	return true;
    }

    bool shareTo(IEntity &entity) override
    {
	return true;
    }

};


};

#endif
