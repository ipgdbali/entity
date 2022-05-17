#ifndef CENTITY_HPP
#define CENTITY_HPP

#include "IEntity.hpp"
#include "CAttrInfo.hpp"
#include "CEntityInfo.hpp"
#include "ICustomType.hpp"
#include <cstring>
#include <iostream>

namespace ipgdlib::entity
{

template <typename TEntityInfo>
class CEntity :
    public virtual IEntity<TEntityInfo,TEntityInfo const *>
{
using TAttrName		    = typename TEntityInfo::type_attr_name;
using TAttrIndex	    = typename TEntityInfo::type_attr_index;
using TAttrSize		    = typename TEntityInfo::type_attr_size;
using TAttrSizeTotal	    = typename TEntityInfo::type_attr_size_total;
using TAttrInfo		    = typename TEntityInfo::type_attr_info;
using TAttrInfoWrapper	    = typename TEntityInfo::type_attr_info_wrapper;
using TEntityInfoWrapper    = TEntityInfo const*;

public:
    using iface = IEntity<TEntityInfo,TEntityInfoWrapper>;
    using type_entity_info = TEntityInfo;
    using type_entity_info_wrapper = TEntityInfoWrapper;

public:

    CEntity() :
	m_EntityInfo(nullptr),m_pEntityData(nullptr)
    {
    }

    TEntityInfoWrapper getEntityInfo() const noexcept override
    {
	return this->m_EntityInfo;
    }

    bool copyAttrTo(TAttrIndex const &attrIndex,void *pDst) const override
    {
	std::memcpy(
		pDst,
		&this->m_pEntityData[this->getEntityInfo()->getAttrOffset(attrIndex)],
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
	std::memcpy(
	    &this->m_pEntityData[this->getEntityInfo()->getAttrOffset(attrIndex)],
	    pSrc,
	    this->m_EntityInfo->getAttrInfo(attrIndex)->getSize()
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

    bool copyTo(void *pDest) const override
    {
	std::memcpy(pDest,this->m_pEntityData,this->getEntityInfo()->getEntitySize());
	return true;
    }

    bool copyFrom(void *pSrc) override
    {
	std::memcpy(this->m_pEntityData,pSrc,this->getEntityInfo()->getEntitySize());
	return true;
    }

    bool shareTo(IEntityShared<TEntityInfo,TEntityInfoWrapper> &eShared) const override
    {
	eShared.set(this->m_EntityInfo,this->m_pEntityData);
	return true;
    }

    bool isNull() const noexcept override
    {
	return this->m_pEntityData == nullptr;
    }

    template <typename T>
    T &getAs(TAttrIndex const &attrIndex)
    {
	return *reinterpret_cast<T*>(&this->m_pEntityData[this->m_EntityInfo->getAttrOffset(attrIndex)]);
    }

    template <typename T>
    T const &getAs(TAttrIndex const &attrIndex) const
    {
	return *reinterpret_cast<T*>(&this->m_pEntityData[this->m_EntityInfo->getAttrOffset(attrIndex)]);
    }

    template <typename T>
    T const &getAs(TAttrName const &attrName) const
    {
	return getAs<T>(this->m_EntityInfo->getIndex(attrName));
    }

    template <typename T>
    T &getAs(TAttrName const &attrName)
    {
	return getAs<T>(this->m_EntityInfo->getIndex(attrName));
    }


    template<typename T>
    bool toCustomType(TAttrIndex const &attrIndex,ICustomType<T> &ref)
    {
	if(ref.getTypeSize() == this->m_EntityInfo->getAttrInfo(attrIndex)->getSize())
	{
	    ref.set(&this->m_pEntityData[this->m_EntityInfo->getAttrOffset(attrIndex)]);
	    return true;
	}
	else
	    return false;
    }
    template <typename T>
    bool toCustomType(TAttrName const &attrName,ICustomType<T> &ref)
    {
	return toCustomType(
	    this->m_EntityInfo->getIndex(attrName),
	    ref
	);
    }

protected:

    char *getEntityPtr() const override
    {
	return this->m_pEntityData;
    }

    bool setEntityPtr(char *pEntity) override
    {
	this->m_pEntityData = pEntity;
	return true;
    }

    bool setEntityInfo(TEntityInfoWrapper entityInfo) override
    {
	this->m_EntityInfo = entityInfo;
	return true;
    }

private:
    TEntityInfoWrapper m_EntityInfo;
    char *m_pEntityData;
};

};

#endif
