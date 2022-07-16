#ifndef IATTRINFO_HPP
#define IATTRINFO_HPP

#include <type_traits>

namespace ipgdlib::entity
{

template <
    typename TAttrName,
    typename TAttrSize
>
class IAttrInfo
{

static_assert(std::is_integral<TAttrSize>::value && !std::is_same<bool,TAttrSize>::value);

public:

    virtual ~IAttrInfo() {};

    using type_attr_size = TAttrSize;
    using type_attr_name = TAttrName;

    virtual const TAttrName &name() const noexcept = 0;
    virtual const TAttrSize &size() const noexcept = 0;
};

};

#endif
