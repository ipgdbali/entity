#ifndef IFIELDS_HPP
#define IFIELDS_HPP

#include "wrapper.hpp"
#include <type_traits>
#include "IField.hpp"

namespace ipgdlib::entity
{

template <
    typename TAttrIndex,		
    typename TAttrSizeTotal,
    typename TAttrInfo,
    eWrapper w
>
class IFields
{

using TAttrName = typename TAttrInfo::iface::type_attr_name;
using TAttrSize = typename TAttrInfo::iface::type_attr_size;
using TAttrInfoWrapper = typename ipgdlib::wrap<TAttrInfo,w>::value;

static_assert(std::is_integral<TAttrIndex>::value && !std::is_same<bool,TAttrIndex>::value);
static_assert(std::is_integral<TAttrSize>::value && !std::is_same<bool,TAttrSize>::value);
static_assert(std::is_integral<TAttrSizeTotal>::value && !std::is_same<bool,TAttrSizeTotal>::value);

static_assert(std::is_base_of<IField<TAttrName,TAttrSize>,TAttrInfo>::value);

public:

    virtual ~IFields() {};

    using type_attr_name		= TAttrName;
    using type_attr_index		= TAttrIndex;
    using type_attr_size		= TAttrSize;
    using type_attr_size_total		= TAttrSizeTotal;
    using type_attr_info		= TAttrInfo;
    using type_attr_info_wrapper	= TAttrInfoWrapper;

    constexpr static eWrapper kind_attr_info_wrapper = w;

    virtual TAttrIndex count() const noexcept = 0;
    virtual TAttrInfoWrapper getAttrInfo(TAttrIndex index) const = 0;

    virtual TAttrSizeTotal getRunningSum(TAttrIndex index) const = 0;

    virtual TAttrSizeTotal getAttrOffset(TAttrIndex index) const noexcept = 0;
    virtual TAttrSizeTotal getEntitySize() const noexcept = 0;

    virtual bool hasName(TAttrName const &attrName) const noexcept = 0;
    virtual TAttrIndex getIndex(TAttrName const &attrName) const = 0;

    virtual TAttrName const &getName(TAttrIndex index) const = 0;
};

};

#endif
