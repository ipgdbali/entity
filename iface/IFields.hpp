#ifndef IFIELDS_HPP
#define IFIELDS_HPP

#include "wrapper.hpp"
#include <type_traits>
#include "IField.hpp"

namespace ipgdlib::entity
{

template <
    typename TCount,		
    typename TSizeTotal,
    typename TField,
    eWrapper eWField
>
class IFields
{

using TWField			    = typename ipgdlib::wrap<TField,eWField>::value;
using TFieldName		    = typename TField::iface::type_name;
using TFieldSize		    = typename TField::iface::type_size;
static_assert(std::is_integral<TFieldSize>::value && !std::is_same<bool,TFieldSize>::value);
static constexpr eWrapper eWName    = TField::iface::enum_wrapper_name;
static constexpr eWrapper eWSize    = TField::iface::enum_wrapper_size;
 
static_assert(std::is_integral<TCount>::value && !std::is_same<bool,TCount>::value);
static_assert(std::is_integral<TSizeTotal>::value && !std::is_same<bool,TSizeTotal>::value);
static_assert(std::is_base_of<IField<TFieldName,TFieldSize,eWName,eWSize>,TField>::value);

public:

    virtual ~IFields() {};

    using type_count				    = TCount;
    using type_size_total			    = TSizeTotal;
    using type_field				    = TField;
    constexpr static eWrapper enum_field_wrapper    = eWField;

    virtual TCount count() const noexcept = 0;

    virtual TWField getField(TCount index) const = 0;

    virtual TSizeTotal sum(TCount index) const = 0; // field sum

    virtual TSizeTotal offset(TCount index) const = 0; // fieldoffset

    virtual TSizeTotal size() const noexcept = 0;

    virtual bool hasName(TFieldName const &fieldName) const noexcept = 0;
    virtual TCount indexOf(TFieldName const &fieldName) const = 0;

};

};

#endif
