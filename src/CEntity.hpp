#ifndef CENTITY_HPP
#define CENTITY_HPP

#include "IEntity.hpp"
#include "CField.hpp"
#include "CFields.hpp"
#include "ICustomType.hpp"
#include <cstring>
#include <iostream>

namespace ipgdlib::entity
{

template <typename TEntityInfo>
class CEntity :
    public virtual IEntity<TEntityInfo,ewConstPointer>
{
using TAttrName		    = typename TEntityInfo::type_attr_name;
using TAttrIndex	    = typename TEntityInfo::type_attr_index;
using TAttrSize		    = typename TEntityInfo::type_attr_size;
using TAttrSizeTotal	    = typename TEntityInfo::type_attr_size_total;
using TAttrInfo		    = typename TEntityInfo::type_attr_info;
using TAttrInfoWrapper	    = typename TEntityInfo::type_attr_info_wrapper;
using TEntityInfoWrapper    = typename ipgdlib::wrap<TEntityInfo,ewConstPointer>::value;

public:
    using iface = IEntity<TEntityInfo,ewConstPointer>;
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
		&this->m_pEntityData[this->getEntityInfo()->getFieldOffset(attrIndex)],
		this->m_EntityInfo->getField(attrIndex)->size()
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

    bool copyAttrFrom(TAttrIndex const &attrIndex,const void *pSrc) override
    {
	std::memcpy(
	    &this->m_pEntityData[this->getEntityInfo()->getFieldOffset(attrIndex)],
	    pSrc,
	    this->m_EntityInfo->getField(attrIndex)->size()
	);
	return true;
    }

    bool copyAttrFrom(TAttrName const &attrName,const void *pSrc) override
    {
	return copyAttrFrom(
		this->m_EntityInfo->getIndex(attrName),
		pSrc
	);
    }

    bool copyAttrsTo(void *pDest) const override
    {
	std::memcpy(pDest,this->m_pEntityData,this->getEntityInfo()->getFieldsSize());
	return true;
    }

    bool copyAttrsFrom(const void *pSrc) override
    {
	std::memcpy(this->m_pEntityData,pSrc,this->getEntityInfo()->getFieldsSize());
	return true;
    }

    bool shareTo(IEntityShared<TEntityInfo,ewConstPointer> &eShared) const override
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
	return *reinterpret_cast<T*>(&this->m_pEntityData[this->m_EntityInfo->getFieldOffset(attrIndex)]);
    }

    template <typename T>
    T const &getAs(TAttrIndex const &attrIndex) const
    {
	return *reinterpret_cast<T*>(&this->m_pEntityData[this->m_EntityInfo->getFieldOffset(attrIndex)]);
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
	if(ref.getTypeSize() == this->m_EntityInfo->getField(attrIndex)->size())
	{
	    ref.setPtr(&this->m_pEntityData[this->m_EntityInfo->getFieldOffset(attrIndex)]);
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
