#ifndef IFIELD_INFO_NULLABLE_HPP
#define IFIELD_INFO_NULLABLE_HPP

#include "IFieldInfo.hpp"

namespace ipgdlib::entity
{

template <
    typename TFieldName,
    typename TFieldSize
>
class IFieldInfoNullable :
    public IFieldInfoNullable<TFieldName,TFieldSize>
{
public:
    using type_field_size = TFieldSize;
    using type_field_name = TFieldName;

    virtual bool isNullable() const noexcept = 0;
};

};

