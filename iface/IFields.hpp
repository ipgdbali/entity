#ifndef IFIELDS_HPP
#define IFIELDS_HPP

#include "wrapper.hpp"
#include <type_traits>
#include "IField.hpp"

namespace ipgdlib::entity
{

template <
    typename TFieldIndex,		
    typename TFieldSizeTotal,
    typename TFieldInfo,
    eWrapper w
>
class IFields
{

using TFieldName = typename TFieldInfo::iface::type_field_name;
using TFieldSize = typename TFieldInfo::iface::type_field_size;
using TFieldInfoWrapper = typename ipgdlib::wrap<TFieldInfo,w>::value;

static_assert(std::is_integral<TFieldIndex>::value && !std::is_same<bool,TFieldIndex>::value);
static_assert(std::is_integral<TFieldSize>::value && !std::is_same<bool,TFieldSize>::value);
static_assert(std::is_integral<TFieldSizeTotal>::value && !std::is_same<bool,TFieldSizeTotal>::value);

static_assert(std::is_base_of<IField<TFieldName,TFieldSize>,TFieldInfo>::value);

public:

    virtual ~IFields() {};

    using type_field_name		= TFieldName;
    using type_field_index		= TFieldIndex;
    using type_field_size		= TFieldSize;
    using type_field_size_total		= TFieldSizeTotal;
    using type_field_info		= TFieldInfo;
    using type_field_info_wrapper	= TFieldInfoWrapper;

    constexpr static eWrapper kind_field_info_wrapper = w;

    virtual TFieldIndex getFieldCount() const noexcept = 0;
    virtual TFieldInfoWrapper getField(TFieldIndex index) const = 0;

    virtual TFieldSizeTotal getRunningSum(TFieldIndex index) const = 0;

    virtual TFieldSizeTotal getFieldOffset(TFieldIndex index) const noexcept = 0;
    virtual TFieldSizeTotal getFieldsSize() const noexcept = 0;

    virtual bool hasName(TFieldName const &fieldName) const noexcept = 0;
    virtual TFieldIndex getIndex(TFieldName const &fieldName) const = 0;

    virtual TFieldName const &getName(TFieldIndex index) const = 0;
};

};

#endif
