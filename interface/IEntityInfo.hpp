#ifndef IENTITY_INFO_HPP
#define IENTITY_INFO_HPP

#include <type_traits>
#include "IAttrInfo.hpp"

namespace ipgdlib::entity
{

template <
    typename TAttrName,
    typename TAttrIndex,		
    typename TAttrSize,
    typename TAttrSizeTotal,
    typename TAttrInfo,
    typename TAttrInfoWrapper
>
class IEntityInfo
{

public:

    static_assert(std::is_integral<TAttrIndex>::value && !std::is_same<bool,TAttrIndex>::value);
    static_assert(std::is_integral<TAttrSize>::value && !std::is_same<bool,TAttrSize>::value);
    static_assert(std::is_integral<TAttrSizeTotal>::value && !std::is_same<bool,TAttrSizeTotal>::value);

    static_assert(std::is_base_of<IAttrInfo<TAttrName,TAttrSize>,TAttrInfo>::value);

    virtual ~IEntityInfo() {};

    using type_attr_index	    = TAttrIndex;
    using type_attr_name	    = TAttrName;
    using type_attr_size	    = TAttrSize;
    using type_attr_size_total	    = TAttrSizeTotal;
    using type_attr_info_wrapper    = TAttrInfoWrapper;

    virtual TAttrIndex getAttrCount() const noexcept = 0;
    virtual TAttrInfoWrapper getAttrInfo(TAttrIndex index) const = 0;

    virtual TAttrSizeTotal getRunningSum(TAttrIndex index) const = 0;

    virtual TAttrSizeTotal getAttrOffset(TAttrIndex index) const noexcept = 0;
    virtual TAttrSizeTotal getEntitySize() const noexcept = 0;

    virtual bool hasName(TAttrName const &attrName) const noexcept = 0;
    virtual TAttrIndex getIndex(TAttrName const &attrName) const = 0;

    virtual TAttrName const &getName(TAttrIndex index) const = 0;
};

};

#endif
