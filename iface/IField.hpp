#ifndef IFIELD_HPP
#define IFIELD_HPP

#include <type_traits>

namespace ipgdlib::entity
{

template <
    typename TFieldName,
    typename TFieldSize
>
class IField
{

static_assert(std::is_integral<TFieldSize>::value && !std::is_same<bool,TFieldSize>::value);

public:

    virtual ~IField() {};

    using type_field_size = TFieldSize;
    using type_field_name = TFieldName;

    virtual const TFieldName &name() const noexcept = 0;
    virtual const TFieldSize &size() const noexcept = 0;
};

};

#endif
