#ifndef CENTITYABS_HPP
#define CENTITYABS_HPP

#include "IEntity.hpp"
#include "CField.hpp"
#include "CFields.hpp"
#include "ICustomType.hpp"
#include <cstring>
#include <iostream>

namespace ipgdlib::entity
{

template <typename TFields>
class CEntityAbs : 
    public virtual IEntity<TFields, ewConstPointer>
{

using TFieldName        = typename TFields::iface::type_field::type_name;
using TFieldIndex       = typename TFields::type_count;
using TFieldsWrapper    = typename ipgdlib::wrap<TFields, ewConstPointer>::value;

public:
    using iface = IEntity<TFields, ewConstPointer>;
    using type_fields = TFields;

public:


    TFieldsWrapper getFields() const noexcept override
    {
        return this->m_Fields;
    }

    bool copyAttrTo(TFieldIndex const &fieldIndex, void *pDst) const override
    {
        std::memcpy(
            pDst,
            &this->m_pEntityData[this->getFields()->offset(fieldIndex)],
            this->m_Fields->getField(fieldIndex)->size());
        return true;
    }

    bool copyAttrTo(TFieldName const &fieldName, void *pDst) const override
    {
        return copyAttrTo(
            this->m_Fields->indexOf(fieldName),
            pDst);
    }

    bool copyAttrFrom(TFieldIndex const &fieldIndex, const void *pSrc) override
    {
        std::memcpy(
            &this->m_pEntityData[this->getFields()->offset(fieldIndex)],
            pSrc,
            this->m_Fields->getField(fieldIndex)->size());
        return true;
    }

    bool copyAttrFrom(TFieldName const &fieldName, const void *pSrc) override
    {
        return copyAttrFrom(
            this->m_Fields->indexOf(fieldName),
            pSrc);
    }

    template <typename T>
    T &as(TFieldIndex const &fieldIndex)
    {
        return *reinterpret_cast<T *>(&this->m_pEntityData[this->m_Fields->offset(fieldIndex)]);
    }

    template <typename T>
    T const &as(TFieldIndex const &fieldIndex) const
    {
        return *reinterpret_cast<T *>(&this->m_pEntityData[this->m_Fields->offset(fieldIndex)]);
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

    template <typename T>
    bool toCustomType(TFieldIndex const &fieldIndex, ICustomType<T> &ref)
    {
        if (ref.getTypeSize() == this->m_Fields->getField(fieldIndex)->size())
        {
            ref.setPtr(&this->m_pEntityData[this->m_Fields->offset(fieldIndex)]);
            return true;
        }
        else
            return false;
    }
    template <typename T>
    bool toCustomType(TFieldName const &fieldName, ICustomType<T> &ref)
    {
        return toCustomType(
            this->m_Fields->indexOf(fieldName),
            ref);
    }

protected:

    // Unique Entity & 
    CEntityAbs(TFieldsWrapper pFields,char *pData) : 
        m_Fields(pFields), m_pEntityData(pData)
    {
    }

    // Shared Entity
    CEntityAbs(CEntityAbs &ref) :
        CEntityAbs(ref.m_Fields,ref.m_pEntityData)
    {
    }

    char *getEntityPtr() const
    {
        return this->m_pEntityData;
    }

    bool setEntityPtr(char *pEntity)
    {
        this->m_pEntityData = pEntity;
        return true;
    }

private:
    TFieldsWrapper  m_Fields;
    char*           m_pEntityData;
};

};

#endif
