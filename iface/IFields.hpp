#ifndef IFIELDS_HPP
#define IFIELDS_HPP

#include <type_traits>
#include "IField.hpp"

namespace ipgdlib::entity
{

template <
    typename CountT,		
    typename TotalSizeT,
    typename FieldT,
    typename FieldNameT
>
class IFields
{

static_assert(std::is_integral<CountT>::value && !std::is_same<bool,CountT>::value);
static_assert(std::is_integral<TotalSizeT>::value && !std::is_same<bool,TotalSizeT>::value);

public:

    using TCount                                    = CountT;
    using TTotalSize                                = TotalSizeT;
    using TField                                    = FieldT;
    
    using TFieldName                                = FieldNameT;
    using TFieldIndex                               = TCount;

    virtual ~IFields() {};

    virtual TCount count() const noexcept = 0;
    virtual TTotalSize sum(TFieldIndex index) const = 0; // field running sum
    virtual TTotalSize offset(TFieldIndex index) const = 0; // offset(0) = 0

    virtual TTotalSize size() const noexcept = 0; // = sum(count() - 1)

    virtual TField getField(TFieldIndex index) const = 0;

    virtual bool hasName(TFieldName fieldName) const noexcept = 0;
    virtual TFieldIndex indexOf(TFieldName fieldName) const = 0;

};

};

#endif
