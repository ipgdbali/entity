#ifndef IATTRINFONULLABLE_HPP
#define IATTRINFONULLABLE_HPP

#include "IAttrInfo.hpp"

namespace ipgdlib::entity
{

template <
    typename TAttrName,
    typename TAttrSize
>
class IAttrInfoNullable :
    public IAttrInfoNullable<TAttrName,TAttrSize>
{
public:
    using type_attr_size = TAttrSize;
    using type_attr_name = TAttrName;

    virtual bool isNullable() const noexcept = 0;
};

};

