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
    public virtual IEntity<TFields, ewConstReference>
{

using TFieldName        = typename TFields::iface::type_field::type_name;
using TFieldSize        = typename TFields::iface::type_field::type_size;
using TFieldIndex       = typename TFields::type_count;

public:
    using iface         = IEntity<TFields, ewConstPointer>;
    using type_fields   = TFields;
    using TWFields      = typename ipgdlib::wrap<TFields, ewConstReference>::value;

    CEntityAbs() = delete;
    CEntityAbs(const CEntityAbs &ref) = delete;
    CEntityAbs &operator = (const CEntityAbs &ref) = delete;
    CEntityAbs(CEntityAbs &&ref) = delete;
    CEntityAbs &operator = (CEntityAbs &&ref) = delete;

    TWFields getFields() const noexcept override
    {
        return this->m_Fields;
    }

    bool copyAttrTo(TFieldIndex const &fieldIndex, void *pDst) const override
    {
        std::memcpy(
            pDst,
            &this->m_pEntityData[this->m_Fields.offset(fieldIndex)],
            this->m_Fields.getField(fieldIndex)->size());
        return true;
    }

    bool copyAttrTo(TFieldName const &fieldName, void *pDst) const override
    {
        return copyAttrTo(
            this->m_Fields.indexOf(fieldName),
            pDst);
    }

    bool copyAttrFrom(TFieldIndex const &fieldIndex, const void *pSrc) override
    {
        std::memcpy(
            &this->m_pEntityData[this->m_Fields.offset(fieldIndex)],
            pSrc,
            this->m_Fields.getField(fieldIndex)->size());
        return true;
    }

    bool copyAttrFrom(TFieldName const &fieldName, const void *pSrc) override
    {
        return copyAttrFrom(
            this->m_Fields.indexOf(fieldName),
            pSrc);
    }

    template <typename T>
    T &as(TFieldIndex const &fieldIndex)
    {
        return *reinterpret_cast<T *>(&this->m_pEntityData[this->m_Fields.offset(fieldIndex)]);
    }

    template <typename T>
    T const &as(TFieldIndex const &fieldIndex) const
    {
        return *reinterpret_cast<T *>(&this->m_pEntityData[this->m_Fields.offset(fieldIndex)]);
    }

    template <typename T>
    T &as(TFieldName const &fieldName)
    {
        return as<T>(this->m_Fields.indexOf(fieldName));
    }

    template <typename T>
    T const &as(TFieldName const &fieldName) const
    {
        return as<T>(this->m_Fields.indexOf(fieldName));
    }

    
    bool toCustomType(TFieldIndex const &fieldIndex, ICustomType<TFieldSize> &ref) override
    {
        if (ref.getTypeSize() == this->m_Fields.getField(fieldIndex)->size())
        {
            ref.setPtr(&this->m_pEntityData[this->m_Fields.offset(fieldIndex)]);
            return true;
        }
        else
            return false;
    }
    
    bool toCustomType(TFieldName const &fieldName, ICustomType<TFieldSize> &ref) override
    {
        return toCustomType(
            this->m_Fields.indexOf(fieldName),
            ref);
    }

protected:

    CEntityAbs(TWFields fields) :
        m_Fields(fields),m_pEntityData(nullptr)
    {
    }

    // Unique Entity & CShared Entity
    CEntityAbs(TWFields fields,char *pData) : 
        m_Fields(fields), m_pEntityData(pData)
    {
        if(m_pEntityData == nullptr)
            throw "pData cannot be null";
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

    void setEntityPtr(char *pData)
    {
        this->m_pEntityData = pData;
    }

private:
    TWFields  m_Fields;
    char*           m_pEntityData;
};

};

#endif
