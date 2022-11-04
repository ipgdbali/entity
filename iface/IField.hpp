#ifndef IFIELD_HPP
#define IFIELD_HPP

#include <type_traits>
#include "wrapper.hpp"

namespace ipgdlib::entity
{

template <
    typename FieldNameT,
    typename FieldSizeT
>
class IField
{
    static_assert(std::is_integral<FieldSizeT>::value && !std::is_same<bool,FieldSizeT>::value);

    public:

        using TFieldName = FieldNameT;
        using TFieldSize = FieldSizeT;

        virtual ~IField() {};

        virtual TFieldName name() const noexcept = 0;
        virtual TFieldSize size() const noexcept = 0;
};

};

#endif
