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

template <typename TFields>
class CEntity :
    public virtual IEntity<TFields,ewConstPointer>
{

using TFieldName		    = typename TFields::iface::type_field::type_name;
using TFieldIndex		    = typename TFields::type_count;
using TFieldsWrapper		    = typename ipgdlib::wrap<TFields,ewConstPointer>::value;

public:
    using iface = IEntity<TFields,ewConstPointer>;
    using type_fields = TFields;

public:

    CEntity() :
	m_Fields(nullptr),m_pEntityData(nullptr)
    {
    }

    TFieldsWrapper getFields() const noexcept override
    {
	return this->m_Fields;
    }

    bool copyAttrTo(TFieldIndex const &fieldIndex,void *pDst) const override
    {
	std::memcpy(
		pDst,
		&this->m_pEntityData[this->getFields()->offset(fieldIndex)],
		this->m_Fields->getField(fieldIndex)->size()
	);
	return true;
    }

    bool copyAttrTo(TFieldName const &fieldName,void *pDst) const override
    {
	return copyAttrTo(
	    this->m_Fields->indexOf(fieldName),
	    pDst
	);
    }

    bool copyTo(void *pDest) const override
    {
	std::memcpy(pDest,this->m_pEntityData,this->getFields()->size());
	return true;
    }

    bool copyAttrFrom(TFieldIndex const &fieldIndex,const void *pSrc) override
    {
	std::memcpy(
	    &this->m_pEntityData[this->getFields()->offset(fieldIndex)],
	    pSrc,
	    this->m_Fields->getField(fieldIndex)->size()
	);
	return true;
    }

    bool copyAttrFrom(TFieldName const &fieldName,const void *pSrc) override
    {
	return copyAttrFrom(
		this->m_Fields->indexOf(fieldName),
		pSrc
	);
    }

    bool copyFrom(const void *pSrc) override
    {
	std::memcpy(this->m_pEntityData,pSrc,this->getFields()->size());
	return true;
    }

    bool shareTo(IEntityShared<TFields,ewConstPointer> &eShared) const override
    {
	eShared.set(this->m_Fields,this->m_pEntityData);
	return true;
    }

    bool isNull() const noexcept override
    {
	return this->m_pEntityData == nullptr;
    }

    template <typename T>
    T &as(TFieldIndex const &fieldIndex)
    {
	return *reinterpret_cast<T*>(&this->m_pEntityData[this->m_Fields->offset(fieldIndex)]);
    }

    template <typename T>
    T const &as(TFieldIndex const &fieldIndex) const
    {
	return *reinterpret_cast<T*>(&this->m_pEntityData[this->m_Fields->offset(fieldIndex)]);
    }

    template <typename T>
    T &as(TFieldName const &fieldName)
    {
	return as<T>(this->m_Fields->indexOf(fieldName));
    }

    template <typename T>
    T const &as(TFieldName const &fieldName) const
    {
	return as<T>(this->m_Fields->indexOf(fieldName));
    }


    template<typename T>
    bool toCustomType(TFieldIndex const &fieldIndex,ICustomType<T> &ref)
    {
	if(ref.getTypeSize() == this->m_Fields->getField(fieldIndex)->size())
	{
	    ref.setPtr(&this->m_pEntityData[this->m_Fields->offset(fieldIndex)]);
	    return true;
	}
	else
	    return false;
    }
    template <typename T>
    bool toCustomType(TFieldName const &fieldName,ICustomType<T> &ref)
    {
	return toCustomType(
	    this->m_Fields->indexOf(fieldName),
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

    bool setFields(TFieldsWrapper entityInfo) override
    {
	this->m_Fields = entityInfo;
	return true;
    }

private:
    TFieldsWrapper m_Fields;
    char *m_pEntityData;
};

};

#endif
