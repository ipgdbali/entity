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
using TFieldName		    = typename TEntityInfo::type_field_name;
using TFieldIndex	    = typename TEntityInfo::type_field_index;
using TFieldSize		    = typename TEntityInfo::type_field_size;
using TFieldSizeTotal	    = typename TEntityInfo::type_field_size_total;
using TFieldInfo		    = typename TEntityInfo::type_field_info;
using TFieldInfoWrapper	    = typename TEntityInfo::type_field_info_wrapper;
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

    bool copyFieldTo(TFieldIndex const &fieldIndex,void *pDst) const override
    {
	std::memcpy(
		pDst,
		&this->m_pEntityData[this->getEntityInfo()->getFieldOffset(fieldIndex)],
		this->m_EntityInfo->getField(fieldIndex)->size()
	);
	return true;
    }

    bool copyFieldTo(TFieldName const &fieldName,void *pDst) const override
    {
	return copyFieldTo(
	    this->m_EntityInfo->getIndex(fieldName),
	    pDst
	);
    }

    bool copyFieldFrom(TFieldIndex const &fieldIndex,const void *pSrc) override
    {
	std::memcpy(
	    &this->m_pEntityData[this->getEntityInfo()->getFieldOffset(fieldIndex)],
	    pSrc,
	    this->m_EntityInfo->getField(fieldIndex)->size()
	);
	return true;
    }

    bool copyFieldFrom(TFieldName const &fieldName,const void *pSrc) override
    {
	return copyFieldFrom(
		this->m_EntityInfo->getIndex(fieldName),
		pSrc
	);
    }

    bool copyFieldsTo(void *pDest) const override
    {
	std::memcpy(pDest,this->m_pEntityData,this->getEntityInfo()->getFieldsSize());
	return true;
    }

    bool copyFieldsFrom(const void *pSrc) override
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
    T &getAs(TFieldIndex const &fieldIndex)
    {
	return *reinterpret_cast<T*>(&this->m_pEntityData[this->m_EntityInfo->getFieldOffset(fieldIndex)]);
    }

    template <typename T>
    T const &getAs(TFieldIndex const &fieldIndex) const
    {
	return *reinterpret_cast<T*>(&this->m_pEntityData[this->m_EntityInfo->getFieldOffset(fieldIndex)]);
    }

    template <typename T>
    T const &getAs(TFieldName const &fieldName) const
    {
	return getAs<T>(this->m_EntityInfo->getIndex(fieldName));
    }

    template <typename T>
    T &getAs(TFieldName const &fieldName)
    {
	return getAs<T>(this->m_EntityInfo->getIndex(fieldName));
    }


    template<typename T>
    bool toCustomType(TFieldIndex const &fieldIndex,ICustomType<T> &ref)
    {
	if(ref.getTypeSize() == this->m_EntityInfo->getField(fieldIndex)->size())
	{
	    ref.setPtr(&this->m_pEntityData[this->m_EntityInfo->getFieldOffset(fieldIndex)]);
	    return true;
	}
	else
	    return false;
    }
    template <typename T>
    bool toCustomType(TFieldName const &fieldName,ICustomType<T> &ref)
    {
	return toCustomType(
	    this->m_EntityInfo->getIndex(fieldName),
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
