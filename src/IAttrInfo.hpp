#ifndef IATTRINFO_HPP
#define IATTRINFO_HPP

namespace ipgdlib::entity
{

template <
    typename TAttrSize,
    typename TAttrName
>
class IAttrInfo
{
public:
    using type_attr_size = TAttrSize;
    using type_attr_name = TAttrName;
    virtual TAttrSize const &getSize() const noexcept = 0;
    virtual TAttrName const &getName() const noexcept = 0;
};

};

#endif
