#ifndef IENTITIES_HPP
#define IENTITIES_HPP

namespace ipgdlib::entity
{

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
public:
    virtual ~IEntities() {};

    virtual TEntityInfo getEntityInfo() const = 0;
    virtual TEntityIndex getEntityCount() const noexcept = 0;

    virtual bool copyAttrTo(TEntityIndex const &idx,TAttrIndex const &attrIndex,void *pDest) const = 0;
    virtual bool copyAttrFrom(TEntityIndex const &idx,TAttrIndex const &attrIndex,void *pSource) = 0;

    virtual bool copyAttrTo(TEntityIndex const &idx,TAttrName const &attrName,void *pDest) const = 0;
    virtual bool copyAttrFrom(TEntityIndex const &idx,TAttrName const &attrName,void *pSource) = 0;

    virtual bool copyEntityTo(TEntityIndex const &idx,
	    IEntity<TAttrIndex,TAttrName,TAttrSize,TAttrSizeTotal,TEntityInfo> &pDest) const = 0;
    virtual bool copyEntityFrom(TEntityIndex const &idx,
	    IEntity<TAttrIndex,TAttrName,TAttrSize,TAttrSizeTotal,TEntityInfo> &pSource) = 0;

    virtual bool copyEntityTo(TEntityIndex const &idx,void *pDest) const = 0;
    virtual bool copyEntityFrom(TEntityIndex const &idx,void *pSource) = 0;

    virtual bool shareEntityTo(TEntityIndex const &idx,
	    IEntity<TAttrIndex,TAttrName,TAttrSize,TAttrSizeTotal,TEntityInfo> &pDest) const = 0;
    virtual bool shareEntityTo(TEntityIndex const &idx,void *pDest) const = 0;

	//thereis no shareEntityFrom because IEntites is Unique Entity
};

};

#endif
