#ifndef IENTITY_HPP
#define IENTITY_HPP

namespace ipgdlib::entity
{

template <
	typename TAttrIndex,			
	typename TAttrName,		
	typename TAttrSize,
	typename TAttrSizeTotal,
	typename TEntityInfoWrapper // pointer,reference, shared or what
>
class IEntity
{
public:
    virtual ~IEntity() = 0;

    using type_attr_index = TAttrIndex;
    using type_attr_name = TAttrName;
    using type_attr_size = TAttrSize;
    using type_attr_size_total = TAttrSizeTotal;
    using type_entity_info = TEntityInfo;
    using type_entity_info_wrapper = TEntityInfoWrapper;

    virtual TEntityInfoWrapper getEntityInfo() const noexcept = 0;

    virtual bool copyAttrTo(TAttrIndex const &attrIndex,void *pDst) const = 0;
    virtual bool copyAttrTo(TAttrName const &attrName,void *pDst) const = 0;
    virtual bool copyAttrFrom(TAttrIndex const &attrIndex,void *pSrc) = 0;
    virtual bool copyAttrFrom(TAttrName const &attrName,void *pSrc) = 0;

    virtual bool isNull() const noexcept = 0;
    virtual void clear() = 0;

protected:
    virtual char *getEntityPtr() const = 0;
    virtual bool setEntityPtr(char *pEntity) = 0;
    virtual bool setEntityInfo(TEntityInfoWrapper eInfo) = 0;
};

};

#endif
