#ifndef IENTITY_HPP
#define IENTITY_HPP

namespace ipgdlib::entity
{

template <
	typename TAttrIndex,			
	typename TAttrName,		
	typename TAttrSize,
	typename TAttrSizeTotal,
	typename TEntityInfo
>
class IEntity
{
public:
    using type_attr_index = TAttrIndex;
    using type_attr_name = TAttrName;
    using type_attr_size = TAttrSize;
    using type_attr_size_total = TAttrSizeTotal;
    using type_entity_info = TEntityInfo;

    virtual TEntityInfo getEntityInfo() const noexcept = 0;

    virtual bool copyAttrTo(TAttrIndex const &attrIndex,void *pDst) const = 0;
    virtual bool copyAttrTo(TAttrName const &attrName,void *pDst) const = 0;
    virtual bool copyAttrFrom(TAttrIndex const &attrIndex,void *pSrc) = 0;
    virtual bool copyAttrFrom(TAttrName const &attrName,void *pSrc) = 0;

protected:
    virtual char *getEntityPtr() const = 0;
    virtual bool setEntityPtr(char *pEntity) = 0;
};

template <
    typename TAttrIndex,			
    typename TAttrName,		
    typename TAttrSize,
    typename TAttrSizeTotal,
    typename TEntityInfo
>
class IEntityUnique :
	public IEntity<TAttrIndex,TAttrName,TAttrSize,TAttrSizeTotal,TEntityInfo>
{
public:
    virtual bool createFrom(TEntityInfo pEntityInfo) = 0;
    virtual bool createFrom(IEntity<TAttrIndex,TAttrName,TAttrSize,TAttrSizeTotal,TEntityInfo> const *pEntity) = 0;
};

template <
    typename TAttrIndex,			
    typename TAttrName,		
    typename TAttrSize,
    typename TAttrSizeTotal,
    typename TEntityInfo
>
class IEntityShared :
	public IEntity<TAttrIndex,TAttrName,TAttrSize,TAttrSizeTotal,TEntityInfo>
{
public:
    virtual bool shareFrom(IEntity<TAttrIndex,TAttrName,TAttrSize,TAttrSizeTotal,TEntityInfo> const *pEntity) = 0;
    virtual bool shareTo(IEntity<TAttrIndex,TAttrName,TAttrSize,TAttrSizeTotal,TEntityInfo> const *pEntity) = 0;
};

template <
    typename TEntityIndex,
    typename TAttrIndex,			
    typename TAttrName,		
    typename TAttrSize,
    typename TAttrSizeTotal,
    typename TEntityInfo
>
class IEntities
{
	virtual TEntityInfo getEntityInfo() const = 0;
	virtual TEntityIndex getEntityCount() const noexcept = 0;

	virtual bool copyAttrTo(TEntityIndex const &idx,TAttrIndex const &attrIndex,void *pDest) const = 0;
	virtual bool copyAttrFrom(TEntityIndex const &idx,TAttrIndex const &attrIndex,void *pSource) = 0;

	virtual bool copyAttrTo(TEntityIndex const &idx,TAttrName const &attrName,void *pDest) const = 0;
	virtual bool copyAttrFrom(TEntityIndex const &idx,TAttrName const &attrName,void *pSource) = 0;

	virtual bool copyEntityTo(TEntityIndex const &idx,
		IEntity<TAttrIndex,TAttrName,TAttrSize,TAttrSizeTotal,TEntityInfo> *pDest) const = 0;
	virtual bool copyEntityFrom(TEntityIndex const &idx,
		IEntity<TAttrIndex,TAttrName,TAttrSize,TAttrSizeTotal,TEntityInfo> *pSource) = 0;

	virtual bool copyEntityTo(TEntityIndex const &idx,void *pDest) const = 0;
	virtual bool copyEntityFrom(TEntityIndex const &idx,void *pSource) = 0;

	virtual bool shareEntityTo(TEntityIndex const &idx,
		IEntity<TAttrIndex,TAttrName,TAttrSize,TAttrSizeTotal,TEntityInfo> *pDest) const = 0;
	virtual bool shareEntityTo(TEntityIndex const &idx,void *pDest) const = 0;

	//thereis no shareEntityFrom because IEntites is Unique Entity
};

};

#endif
