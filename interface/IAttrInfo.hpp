#ifndef IATTRINFO_HPP
#define IATTRINFO_HPP

namespace ipgdlib::entity
{

template <
    typename TAttrName,
    typename TAttrSize
>
class IAttrInfo
{
public:

    virtual ~IAttrInfo() {};

    using type_attr_size = TAttrSize;
    using type_attr_name = TAttrName;

    virtual TAttrName const &getName() const noexcept = 0;
    virtual TAttrSize const &getSize() const noexcept = 0;
};

};

#endif
