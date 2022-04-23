#ifndef IENTITY_INFO_HPP
#define IENTITY_INFO_HPP

namespace ipgdlib::entity
{

template <
    typename TAttrIndex,		
    typename TAttrName,
    typename TAttrSize,
    typename TAttrSizeTotal,
    typename TAttrInfo
>
class IEntityInfo
{
public:

	using type_attr_index	    = TAttrIndex;
	using type_attr_name	    = TAttrName;
	using type_attr_size	    = TAttrSize;
	using type_attr_size_total  = TAttrSizeTotal;
	using type_attr_info	    = TAttrInfo;

	virtual TAttrIndex const &getAttrCount() const noexcept = 0;
	virtual TAttrInfo getAttrInfo(TAttrIndex const &index) const = 0;

	virtual TAttrSizeTotal const &getRunningSum(TAttrIndex const &index) const = 0;
	virtual TAttrSizeTotal const &getEntitySize() const noexcept = 0;

	virtual bool hasName(TAttrName const &attrName) const noexcept = 0;
	virtual TAttrIndex const &getIndex(TAttrName const &attrName) const = 0;

	virtual TAttrName const &getName(TAttrIndex const &index) const = 0;
};

};

#endif
