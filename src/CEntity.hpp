#ifndef CENTITY_HPP
#define CENTITY_HPP

#include "IEntity.hpp"

namespace ipgdlib::entity
{

template <
	typename TAttrName,		
	typename TAttrIndex,			
	typename TAttrSize,
	typename TAttrSizeTotal,
	typename TEntityInfo = CEntityInfo<TAttrName,TAttrIndex,TAttrSize,TAttrSizeTotal,
	    CAttrInfo<TAttrName,TAttrSize>;
>
class CEntity :
    public virtual IEntity<TAttrName,TAttrIndex,TAttrSize,TAttrSizeTotal,TEntityInfo const *>
{
public:
    using type_attr_index = TAttrIndex;
    using type_attr_name = TAttrName;
    using type_attr_size = TAttrSize;
    using type_attr_size_total = TAttrSizeTotal;
    using type_entity_info = TEntityInfo;

    using TEntityInfoWrapper = TEntityInfo const *;

    TEntityInfoWrapper getEntityInfo() const noexcept override
    {
	this->m_EntityInfo;
    }

    bool copyAttrTo(TAttrIndex const &attrIndex,void *pDst) const override
    {
	memcpy(
		pDst,
		&this->m_pEntityData[this->getEntityInfo().getAttrOffset(attrIndex)],
		this->m_EntityInfo->getAttrInfo(attrIndex)->getSize()
	);
	return true;
    }

    bool copyAttrTo(TAttrName const &attrName,void *pDst) const override
    {
	return copyAttrTo(
	    this->m_EntityInfo->getIndex(attrName),
	    pDst
	);
    }

    bool copyAttrFrom(TAttrIndex const &attrIndex,void *pSrc) override
    {
	memcpy(
	    &this->m_pEntityData[this->getEntityInfo().getAttrOffset(attrIndex)],
	    pSrc,
	    this->m_EntityInfo->getAttrInfo(attrIdx)->getSize()
	);
	return true;
    }

    bool copyAttrFrom(TAttrName const &attrName,void *pSrc) override
    {
	return copyAttrFrom(
		this->m_EntityInfo->getIndex(attrName),
		pSrc
	);
    }

    template<typename T>
    bool toCustomType(TAttrIndex const &attrIndex,ICustomType<T> &ref)
    {
	return ref.set(
	    this->m_EntityInfo->getAttrInfo(attrIndex)->getSize(),
	    &this->m_pEntityData[this->m_EntityInfo->getAttrOffset(attrIndex)]
	);
    }
    template <typename T>
    bool toCustomType(TAttrName const &attrName,ICustomType<T> &ref)
    {
	return toCustomType(
	    this->m_EntityInfo->getIndex(attrName),
	    ref
	);
    }

    template <typename T>
    T &getAs(TAttrIndex const &attrIndex)
    {
	return *reinterpret_cast<T*>(&this->m_pEntityData[this->m_EntityInfo->getAttrOffset(attrIndex)]);
    }

    template <typename T>
    T &getAs(TAttrName const &attrName)
    {
	return getAs<T>(this->m_EntityInfo->getIndex(attrName));
    }

    bool isNull() const noexcept override
    {
	return this->m_pEntityData == nullptr;
    }

protected:

    char *getEntityPtr() const override
    {
	return this->m_pEntityData;
    }

    void setEntityPtr(char *pEntity) override
    {
	this->m_pEntityData = pEntity;
    }

    void setEntityInfo(TEntityInfoWrapper entityInfo)
    {
	this->m_EntityInfo = entityInfo;
    }

    // This is abstract class
    // Concrete class is in Unique or Shared
    void clear()
    {
	this->m_EntityInfo = nullptr;
    }

private:
    TEntityInfoWrapper m_EntityInfo;
    char *m_pEntityData;
};

};

#endif
