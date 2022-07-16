#ifndef IFIELD_HPP
#define IFIELD_HPP

#include <type_traits>

namespace ipgdlib::entity
{

template <
    typename TAttrName,
    typename TAttrSize
>
class IField
{

static_assert(std::is_integral<TAttrSize>::value && !std::is_same<bool,TAttrSize>::value);

public:

    virtual ~IField() {};

    using type_attr_size = TAttrSize;
    using type_attr_name = TAttrName;

    virtual const TAttrName &name() const noexcept = 0;
    virtual const TAttrSize &size() const noexcept = 0;
};

};

#endif
