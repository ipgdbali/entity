#ifndef IFIELD_HPP
#define IFIELD_HPP

#include <type_traits>
#include "wrapper.hpp"

namespace ipgdlib::entity
{

template <
    typename TName,
    typename TSize,
    eWrapper eWName,
    eWrapper eWSize
>
class IField
{

static_assert(std::is_integral<TSize>::value && !std::is_same<bool,TSize>::value);

using TWName			    = typename ipgdlib::wrap<TName,eWName>::value;
using TWSize			    = typename ipgdlib::wrap<TSize,eWSize>::value;

public:

    virtual ~IField() {};

    using type_name				= TName;
    using type_size				= TSize;
    static constexpr eWrapper enum_wrapper_name = eWName;
    static constexpr eWrapper enum_wrapper_size = eWSize;

    virtual TWName name() const noexcept = 0;
    virtual TWSize size() const noexcept = 0;
};

};

#endif
