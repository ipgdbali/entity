#ifndef IENTITY_HPP
#define IENTITY_HPP

#include "IAttrInfo.hpp"
#include "IEntityInfo.hpp"

namespace ipgdlib::entity
{
template <typename TEntityInfo,typename TEntityInfoWrapper> 
class IEntityShared;


template <
	typename TEntityInfo,
	typename TEntityInfoWrapper // pointer,reference, shared or what
>
class IEntity
{

using TAttrName		    = typename TEntityInfo::iface::type_attr_name;
using TAttrIndex	    = typename TEntityInfo::iface::type_attr_index;
using TAttrSize		    = typename TEntityInfo::iface::type_attr_size;
using TAttrSizeTotal	    = typename TEntityInfo::iface::type_attr_size_total;
using TAttrInfo		    = typename TEntityInfo::iface::type_attr_info;
using TAttrInfoWrapper	    = typename TEntityInfo::iface::type_attr_info_wrapper;

static_assert(std::is_integral<TAttrIndex>::value && !std::is_same<bool,TAttrIndex>::value);
static_assert(std::is_integral<TAttrSize>::value && !std::is_same<bool,TAttrSize>::value);
static_assert(std::is_integral<TAttrSizeTotal>::value && !std::is_same<bool,TAttrSizeTotal>::value);
static_assert(std::is_base_of<IAttrInfo<TAttrName,TAttrSize>,TAttrInfo>::value);
static_assert(std::is_base_of<IEntityInfo<TAttrIndex,TAttrSizeTotal,TAttrInfo,TAttrInfoWrapper>,TEntityInfo>::value);

public:
    virtual ~IEntity() {};

    using type_attr_name	    = TAttrName;
    using type_attr_index	    = TAttrIndex; 
    using type_attr_size	    = TAttrSize;
    using type_attr_size_total	    = TAttrSizeTotal;
    using type_attr_info	    = TAttrInfo;
    using type_attr_info_wrapper    = TAttrInfoWrapper;
    using type_entity_info	    = TEntityInfo;
    using type_entity_info_wrapper  = TEntityInfoWrapper;

    virtual TEntityInfoWrapper getEntityInfo() const noexcept = 0;

    virtual bool copyAttrTo(TAttrIndex const &attrIndex,void *pDst) const = 0;
    virtual bool copyAttrTo(TAttrName const &attrName,void *pDst) const = 0;
    virtual bool copyAttrFrom(TAttrIndex const &attrIndex,void *pSrc) = 0;
    virtual bool copyAttrFrom(TAttrName const &attrName,void *pSrc) = 0;

    virtual bool copyTo(void *pDest) const = 0;
    virtual bool copyFrom(void *pSrc) const = 0;

    virtual bool shareTo(IEntityShared<TEntityInfo,TEntityInfoWrapper> &eShared) const = 0;

    virtual bool isNull() const noexcept = 0;
    virtual void clear() = 0;

protected:
    virtual char *getEntityPtr() const = 0;
    virtual bool setEntityPtr(char *pEntity) = 0;
    virtual bool setEntityInfo(TEntityInfoWrapper eInfo) = 0;
};

};

#endif
