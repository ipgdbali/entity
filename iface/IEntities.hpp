#ifndef IENTITIES_HPP
#define IENTITIES_HPP

#include "IEntityShared.hpp"

namespace ipgdlib::entity
{

template <typename TEntityCount,typename TEntityInfo,eWrapper ewEntityInfo>
class IEntities
{
using TEntityInfoWrapper = typename ipgdlib::wrap<TEntityInfo,ewEntityInfo>::value;

public:
    using type_entity_count = TEntityCount;
    using type_entity_info = TEntityInfo;
    using type_entity_info_wrapper = TEntityInfoWrapper;

    virtual ~IEntities() {};

    virtual TEntityInfoWrapper getEntityInfo() const = 0;
    virtual TEntityCount getEntityCount() const noexcept = 0;

    virtual bool isNullEntities() const noexcept = 0;
    virtual bool isNullEntity(TEntityCount rowPos) const = 0;

    virtual void assignFrom(TEntityCount rowPos,void *pSrc) = 0;
    virtual void assignTo(TEntityCount rowPos,void *&pDest) const = 0;
    virtual void *getPData(TEntityCount rowPos) = 0;
    
    // must be called for non null row
    virtual void copyFrom(TEntityCount rowPos,const void *pSrc) = 0;
    virtual void copyTo(TEntityCount rowPos,void *pDest) const = 0;
    virtual void shareTo(TEntityCount rowPos,IEntityShared<TEntityInfo,ewEntityInfo> &eShared) const = 0;

};

};

#endif
