#ifndef IENTITIES_HPP
#define IENTITIES_HPP

#include "IEntityShared.hpp"

namespace ipgdlib::entity
{

template <
    typename TCount,
    typename TFields,
    eWrapper ewFields>
class IEntities
{
using TFieldsWrapper = typename ipgdlib::wrap<TFields,ewFields>::value;

public:
    using type_count = TCount;
    using type_fields = TFields;
    constexpr static eWrapper enum_wrapper_fields = ewFields;

    virtual ~IEntities() {};

    virtual TFieldsWrapper getFields() const = 0;
    virtual TCount count() const noexcept = 0;

    virtual bool isNullEntities() const noexcept = 0;
    virtual bool isNullEntity(TCount rowPos) const = 0;

    virtual void assignFrom(TCount rowPos,void *pSrc) = 0;
    virtual void assignTo(TCount rowPos,void *&pDest) const = 0;
    virtual void *getPData(TCount rowPos) = 0;
    
    // must be called for non null row
    virtual void copyFrom(TCount rowPos,const void *pSrc) = 0;
    virtual void copyTo(TCount rowPos,void *pDest) const = 0;
    virtual void shareTo(IEntityShared<TFields,ewFields> &eShared,TCount rowPos) const = 0;

};

};

#endif
