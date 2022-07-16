#ifndef IFIELD_INFO_NULLABLE_HPP
#define IFIELD_INFO_NULLABLE_HPP

#include "IFieldInfo.hpp"

namespace ipgdlib::entity
{

template <
    typename TAttrName,
    typename TAttrSize
>
class IFieldInfoNullable :
    public IFieldInfoNullable<TAttrName,TAttrSize>
{
public:
    using type_attr_size = TAttrSize;
    using type_attr_name = TAttrName;

    virtual bool isNullable() const noexcept = 0;
};

};

