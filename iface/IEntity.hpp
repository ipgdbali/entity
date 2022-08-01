#ifndef IENTITY_HPP
#define IENTITY_HPP

#include "wrapper.hpp"
#include "IField.hpp"
#include "IFields.hpp"

namespace ipgdlib::entity
{

template <typename TFields,eWrapper ewFields> 
class IEntityShared;


template <
    typename TFields,
    eWrapper ewFields
>
class IEntity
{
using TFieldsWrapper				= typename ipgdlib::wrap<TFields,ewFields>::value;

using TFieldIndex				= typename TFields::iface::type_count;
using TFieldName				= typename TFields::iface::type_field::type_name;

public:
    using type_fields = TFields;
    constexpr static eWrapper enum_wrapper_fields = ewFields;

    virtual ~IEntity() {};

    virtual TFieldsWrapper getFields() const noexcept = 0;

    virtual bool copyAttrTo(const TFieldIndex &fieldIndex,void *pDst) const = 0;
    virtual bool copyAttrTo(const TFieldName &fieldName,void *pDst) const = 0;
    virtual bool copyTo(void *pDest) const = 0;

    virtual bool copyAttrFrom(const TFieldIndex &fieldIndex,const void *pSrc) = 0;
    virtual bool copyAttrFrom(const TFieldName &fieldName,const void *pSrc) = 0;
    virtual bool copyFrom(const void *pSrc) = 0;

    virtual bool shareTo(IEntityShared<TFields,ewFields> &eShared) const = 0;

    virtual bool isNull() const noexcept = 0;
    virtual void clear() = 0;

protected:
    virtual char *getEntityPtr() const = 0;
    virtual bool setEntityPtr(char *pEntity) = 0;
    virtual bool setFields(TFieldsWrapper eInfo) = 0;
};

};

#endif
