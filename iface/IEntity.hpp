#ifndef IENTITY_HPP
#define IENTITY_HPP

#include "wrapper.hpp"
#include "IField.hpp"
#include "IFields.hpp"

namespace ipgdlib::entity
{

template <typename TEntityInfo,eWrapper ewEntityInfo> 
class IEntityShared;


template <
	typename TEntityInfo,
	eWrapper ewEntityInfo
>
class IEntity
{

using TFieldName		    = typename TEntityInfo::iface::type_field_name;
using TFieldIndex	    = typename TEntityInfo::iface::type_field_index;
using TFieldSize		    = typename TEntityInfo::iface::type_field_size;
using TFieldSizeTotal	    = typename TEntityInfo::iface::type_field_size_total;
using TFieldInfo		    = typename TEntityInfo::iface::type_field_info;
using TFieldInfoWrapper	    = typename TEntityInfo::iface::type_field_info_wrapper;
using TEntityInfoWrapper    = typename ipgdlib::wrap<TEntityInfo,ewEntityInfo>::value;
constexpr static eWrapper eFieldInfo = TEntityInfo::iface::kind_field_info_wrapper;

static_assert(std::is_integral<TFieldIndex>::value && !std::is_same<bool,TFieldIndex>::value);
static_assert(std::is_integral<TFieldSize>::value && !std::is_same<bool,TFieldSize>::value);
static_assert(std::is_integral<TFieldSizeTotal>::value && !std::is_same<bool,TFieldSizeTotal>::value);
static_assert(std::is_base_of<IField<TFieldName,TFieldSize>,TFieldInfo>::value);
static_assert(std::is_base_of<IFields<TFieldIndex,TFieldSizeTotal,TFieldInfo,eFieldInfo>,TEntityInfo>::value);

public:
    virtual ~IEntity() {};

    using type_field_name	    = TFieldName;
    using type_field_index	    = TFieldIndex; 
    using type_field_size	    = TFieldSize;
    using type_field_size_total	    = TFieldSizeTotal;
    using type_field_info	    = TFieldInfo;
    using type_field_info_wrapper    = TFieldInfoWrapper;
    using type_entity_info	    = TEntityInfo;
    using type_entity_info_wrapper  = TEntityInfoWrapper;

    virtual TEntityInfoWrapper getEntityInfo() const noexcept = 0;

    virtual bool copyFieldTo(TFieldIndex const &fieldIndex,void *pDst) const = 0;
    virtual bool copyFieldTo(TFieldName const &fieldName,void *pDst) const = 0;
    virtual bool copyFieldFrom(TFieldIndex const &fieldIndex,const void *pSrc) = 0;
    virtual bool copyFieldFrom(TFieldName const &fieldName,const void *pSrc) = 0;

    virtual bool copyFieldsFrom(const void *pSrc) = 0;
    virtual bool copyFieldsTo(void *pDest) const = 0;

    virtual bool shareTo(IEntityShared<TEntityInfo,ewEntityInfo> &eShared) const = 0;

    virtual bool isNull() const noexcept = 0;
    virtual void clear() = 0;

protected:
    virtual char *getEntityPtr() const = 0;
    virtual bool setEntityPtr(char *pEntity) = 0;
    virtual bool setEntityInfo(TEntityInfoWrapper eInfo) = 0;
};

};

#endif
